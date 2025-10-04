# Quick Fix Guide: Ball V5 Flickering Issue

## Problem
When you adjust the light brightness slider, the light flickers and enters a cycle of turning on and off.

## Is This You?

✅ **YES, this is my problem if:**
- Light flickers when I move the brightness slider
- Light keeps turning on/off repeatedly
- Device seems to be fighting with Home Assistant
- Changes on device keep triggering more changes

❌ **NO, this is not my problem if:**
- Light doesn't respond at all (check HA Actions permission)
- Slider doesn't move (check entity IDs)
- Display is frozen (different issue)

## Quick Fix

### Option 1: Use Fixed Version (Recommended)
1. Download the latest `Ball_v5.yaml` from this repository
2. Replace your current file
3. Flash your device
4. Done! No configuration changes needed

### Option 2: Manual Patch
If you want to keep your customizations, apply these changes:

#### Step 1: Add Flags (around line 977)
```yaml
globals:
  # ... existing globals ...
  - id: updating_light_from_ha
    type: bool
    restore_value: no
    initial_value: 'false'
  - id: updating_media_from_ha
    type: bool
    restore_value: no
    initial_value: 'false'
```

#### Step 2: Update Light Brightness Sensor (around line 198)
Find:
```yaml
sensor:
  - platform: homeassistant
    id: ha_light_brightness
    on_value:
      - lvgl.slider.update:
```

Change to:
```yaml
sensor:
  - platform: homeassistant
    id: ha_light_brightness
    on_value:
      - lambda: 'id(updating_light_from_ha) = true;'
      - lvgl.slider.update:
          id: my_light_slider
          value: !lambda 'return (x / 255.0) * 100.0;'
      - lvgl.label.update:
          id: brightness_value_label
          text: !lambda |-
            char buf[20];
            snprintf(buf, sizeof(buf), "%.0f%%", (x / 255.0) * 100.0);
            return buf;
      - lambda: 'id(updating_light_from_ha) = false;'
```

#### Step 3: Update Slider On_Value (around line 1164)
Find:
```yaml
- slider:
    id: my_light_slider
    on_value:
      - homeassistant.action:
          action: light.turn_on
```

Change to:
```yaml
- slider:
    id: my_light_slider
    on_value:
      - if:
          condition:
            lambda: 'return !id(updating_light_from_ha);'
          then:
            - homeassistant.action:
                action: light.turn_on
                data:
                  entity_id: light.YOUR_LIGHT_ENTITY
                  brightness_pct: !lambda 'return (int) x;'
      - lvgl.label.update:
          id: brightness_value_label
          text: !lambda |-
            char buf[20];
            snprintf(buf, sizeof(buf), "%.0f%%", x);
            return buf;
```

#### Step 4: (Optional) Fix Media Volume Too
Repeat the same pattern for media volume:

1. Around line 241 (media volume sensor): Add flag set/clear
2. Around line 1404 (media volume slider): Add condition check

See the full file for exact implementation.

### Option 3: Use Ball V4
If you don't need the new V5 features (media player, weather, live state colors), you can use Ball V4 which doesn't have this issue:
1. Switch to `Ball_v4/Ball_v4.yaml`
2. Flash your device
3. Simpler, but no new features

## Verification

After applying the fix:

1. **Test slider**: Move brightness slider - should be smooth, no flickering
2. **Test HA control**: Change light from HA dashboard - slider should update
3. **Test rapid changes**: Quickly move slider back and forth - should be smooth
4. **Test automation**: If you have automation, it should update display without flickering

## What Was Fixed

**Before (Buggy V5):**
```
You move slider → Call HA → HA updates → Sensor sees it → Updates slider → Loop!
```

**After (V5.1 Fixed):**
```
You move slider → Call HA → HA updates → Sensor sees it → Updates slider
                                                             ↑
                                                        Flag blocks loop ✅
```

## Still Having Issues?

### Flickering Still Happening?
1. ✅ Verify you applied ALL changes (flags + sensor + slider)
2. ✅ Flash the device again (full flash, not quick upload)
3. ✅ Restart Home Assistant
4. ✅ Check ESPHome logs for errors

### Other Problems?
- **Slider not working at all**: Check entity IDs and HA Actions permission
- **Colors not changing**: Check `ha_light_state` text sensor
- **Display frozen**: Reboot device
- **Compilation errors**: Check YAML indentation

## Need More Info?

- **Technical details**: See [BUGFIX_FLICKERING.md](BUGFIX_FLICKERING.md)
- **Comparison with V4**: See [V4_VS_V5_FIXED.md](V4_VS_V5_FIXED.md)
- **Complete changelog**: See [CHANGES.md](CHANGES.md)

## Version Info

- **Bug introduced**: Ball V5.0
- **Fixed in**: Ball V5.1
- **Fix date**: 2025
- **Applies to**: Both light and media player sliders

---

**TL;DR**: The flickering is caused by a feedback loop. The fix adds a flag to prevent the loop. Use the fixed `Ball_v5.yaml` file or manually apply the 4 changes above.
