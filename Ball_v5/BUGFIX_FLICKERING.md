# Bug Fix: Light Flickering in Ball V5

## Issue Description
Users reported that when modifying light values in Ball V5, the light would start flickering and enter a weird cycle of turning on and off.

## Root Cause
The issue was caused by a **feedback loop** between the device and Home Assistant:

1. **User moves slider** → ESPHome calls `homeassistant.action: light.turn_on`
2. **Home Assistant updates light** → Light brightness changes
3. **HA sensor detects change** → `ha_light_brightness` sensor receives new value
4. **Sensor updates slider** → `lvgl.slider.update` is called
5. **Slider triggers on_value** → This triggers step 1 again (loop!)

This created a continuous cycle where:
- The slider kept updating itself
- Each update triggered a new Home Assistant call
- The light kept receiving commands
- The device and light flickered continuously

## Solution
Added a **flag-based protection mechanism** to prevent the feedback loop:

### 1. Added Global Flags
```yaml
globals:
  - id: updating_light_from_ha
    type: bool
    restore_value: no
    initial_value: 'false'
  - id: updating_media_from_ha
    type: bool
    restore_value: no
    initial_value: 'false'
```

### 2. Set Flag When HA Updates Slider
```yaml
sensor:
  - platform: homeassistant
    id: ha_light_brightness
    on_value:
      - lambda: 'id(updating_light_from_ha) = true;'  # Set flag
      - lvgl.slider.update:
          id: my_light_slider
          value: !lambda 'return (x / 255.0) * 100.0;'
      - lambda: 'id(updating_light_from_ha) = false;'  # Clear flag
```

### 3. Check Flag Before Calling HA
```yaml
on_value:
  - if:
      condition:
        lambda: 'return !id(updating_light_from_ha);'  # Only call HA if NOT from HA
      then:
        - homeassistant.action:
            action: light.turn_on
            data:
              entity_id: light.YOUR_LIGHT_ENTITY
              brightness_pct: !lambda 'return (int) x;'
```

## How It Works Now

### User Controls Device → HA Updates
```
User moves slider
  ↓
Flag = false (not from HA)
  ↓
Call homeassistant.action
  ↓
HA updates light
  ↓
Sensor receives update
  ↓
Flag = true (from HA)
  ↓
Update slider
  ↓
on_value triggered but sees flag = true
  ↓
Skip HA call (no loop!)
  ↓
Flag = false (ready for next user action)
```

### External Change (Automation, Voice, etc.) → Device Updates
```
HA automation changes light
  ↓
Sensor receives update
  ↓
Flag = true (from HA)
  ↓
Update slider
  ↓
on_value triggered but sees flag = true
  ↓
Skip HA call (no loop!)
  ↓
Flag = false
  ↓
Device display matches HA state (✓)
```

## Changes Made

### Files Modified
- `Ball_v5/Ball_v5.yaml`

### Lines Changed
1. **Globals section** (~line 977-990): Added two boolean flags
2. **ha_light_brightness sensor** (~line 198-216): Added flag protection
3. **my_light_slider on_value** (~line 1164-1186): Added condition check
4. **ha_media_volume sensor** (~line 241-255): Added flag protection
5. **media_volume_slider on_value** (~line 1404-1430): Added condition check

## Benefits

✅ **No more flickering** - Feedback loop eliminated  
✅ **HA values are priority** - External changes update display without triggering actions  
✅ **User control works** - Device changes still trigger HA updates  
✅ **Minimal changes** - Only 4 locations modified, no breaking changes  
✅ **Same for media** - Volume slider also protected from feedback loops  

## Testing Recommendations

1. **Test device control**:
   - Move brightness slider → Light should change smoothly
   - Move volume slider → Volume should change smoothly

2. **Test HA control**:
   - Change light from HA dashboard → Device slider should update without flickering
   - Change volume from HA → Device slider should update without flickering

3. **Test automation**:
   - Create automation that changes light → Device should reflect changes instantly
   - No flickering should occur

4. **Test rapid changes**:
   - Quickly move slider multiple times → Should work smoothly
   - Change light while moving slider → Should sync properly

## Backward Compatibility

✅ **Fully compatible** with existing configurations  
✅ **No entity changes** required  
✅ **No HA setup changes** needed  
✅ **Works with Ball V4** entity configurations  

## Migration Notes

If updating from buggy V5 version:
1. Replace Ball_v5.yaml with fixed version
2. No configuration changes needed
3. Flash device
4. Existing entity IDs remain the same
5. Test slider controls

## Credits

- Bug reported by user
- Fix implements standard feedback loop prevention pattern
- Applied to both light and media player controls

## Version

- **Fixed Version**: Ball V5.1
- **Date**: 2025
- **ESPHome Compatibility**: 2025.5.0+

---

**Note**: This pattern should be used whenever a sensor update triggers a UI element that can also trigger actions back to the same entity. It's a common issue in bidirectional control systems.
