# Changes from Ball V3 to Ball V4

## Overview
Ball V4 is an enhanced version of Ball V3 with improved light control, better user experience, and optimized screen layout.

## Key Changes

### 1. Instant Brightness Updates

**Changed:**
- Slider now uses `on_value` instead of `on_release`
- Brightness changes **instantly** as you move the slider
- No need to release the slider to apply changes

**Before (V3):**
```yaml
- slider:
    id: my_light_slider
    on_release:
      - homeassistant.action:
          action: light.turn_on
```

**After (V4):**
```yaml
- slider:
    id: my_light_slider
    on_value:
      - homeassistant.action:
          action: light.turn_on
```

### 2. Percentage-Based Brightness

**Changed:**
- Slider range changed from 0-255 to 0-100%
- Uses `brightness_pct` instead of `brightness` in HA action
- More intuitive for users
- Better alignment with Home Assistant standard

**Before (V3):**
```yaml
- slider:
    min_value: 0
    max_value: 255
    value: 128
    on_release:
      - homeassistant.action:
          data:
            brightness: !lambda 'return (int) x;'
```

**After (V4):**
```yaml
- slider:
    min_value: 0
    max_value: 100
    value: 50
    on_value:
      - homeassistant.action:
          data:
            brightness_pct: !lambda 'return (int) x;'
```

### 3. Voice Assistant Activation Fixed

**Changed:**
- Touch screen no longer activates voice assistant
- Only physical button activates voice assistant
- Prevents accidental activation when using controls
- Single tap still dismisses timer alerts

**Before (V3):**
```yaml
binary_sensor:
  - platform: template
    id: touch_input
    on_multi_click:
      - timing:
          - ON for 40ms to 400ms
        then:
          - if:
              condition:
                lambda: return id(wake_word_engine_location).state == "On device";
              then:
                - voice_assistant.start:  # ← Triggered on touch
```

**After (V4):**
```yaml
binary_sensor:
  - platform: template
    id: touch_input
    on_multi_click:
      - timing:
          - ON for 40ms to 400ms
        then:
          - if:
              condition:
                switch.is_on: timer_ringing
              then:
                - switch.turn_off: timer_ringing
              # Voice assistant activation removed from touch
```

### 4. Optimized Screen Layout

**Changed:**
- Widget positions adjusted to fit 240x240 screen without scrolling
- Slider position: y=60 (was y=70)
- Label position: y=90 (was y=105)
- Button position: y=130 (was y=150)
- Button height: 45px (was 50px)
- Button alignment: TOP_MID (was CENTER)
- All controls visible without scrolling

### 5. Time Display Added

**Added:**
- Time sensor from Home Assistant
- Time label in top-left corner of Ready page
- Shows current time in HH:MM format
- Updates every minute automatically

**New Code:**
```yaml
time:
  - platform: homeassistant
    id: ha_time
    on_time:
      - seconds: 0
        minutes: '*'
        then:
          - lvgl.label.update:
              id: time_label
              text: !lambda |-
                char buf[10];
                auto time = id(ha_time).now();
                snprintf(buf, sizeof(buf), "%02d:%02d", time.hour, time.minute);
                return buf;

# In idle_page:
- label:
    id: time_label
    text: "--:--"
    align: TOP_LEFT
    x: 10
    y: 5
```

### 6. Live Brightness Feedback

**Added:**
- Brightness label updates in real-time as you move the slider
- Shows percentage with "%" symbol
- Updates both from slider and from external changes (HA)

**New Code:**
```yaml
- slider:
    on_value:
      - lvgl.label.update:
          id: brightness_value_label
          text: !lambda |-
            char buf[20];
            snprintf(buf, sizeof(buf), "%.0f%%", x);
            return buf;
```

### 7. External Brightness Sync Enhanced

**Changed:**
- Sensor converts HA brightness (0-255) to percentage (0-100)
- Updates both slider and label
- Better synchronization with external changes

**New Code:**
```yaml
sensor:
  - platform: homeassistant
    id: ha_light_brightness
    entity_id: light.YOUR_LIGHT_ENTITY
    attribute: brightness
    on_value:
      # Convert 0-255 from HA to 0-100 percentage
      - lvgl.slider.update:
          id: my_light_slider
          value: !lambda 'return (x / 255.0) * 100.0;'
      - lvgl.label.update:
          id: brightness_value_label
          text: !lambda |-
            char buf[20];
            snprintf(buf, sizeof(buf), "%.0f%%", (x / 255.0) * 100.0);
            return buf;
```

## Configuration Requirements

### Home Assistant Setup (REQUIRED)
To use the light control features:

1. Go to **Settings → Devices & Services → ESPHome**
2. Find **Ball V4** device and click **Configure**
3. Enable: **"Allow the device to perform Home Assistant actions"**
4. Click **Submit**

Without this permission, the light control will not work!

### Entity ID Configuration
Replace `light.YOUR_LIGHT_ENTITY` in four locations:
1. Home Assistant sensor (line ~213)
2. Slider on_value action (line ~1070)
3. Button on_click action (line ~1108)
4. Number entity set_action (line ~873)

Example: `light.living_room_lamp`

## Technical Details

### New Time Sensor
```yaml
time:
  - platform: homeassistant
    id: ha_time
    on_time:
      - seconds: 0
        minutes: '*'
        then:
          - lvgl.label.update:
              id: time_label
              text: !lambda |-
                char buf[10];
                auto time = id(ha_time).now();
                snprintf(buf, sizeof(buf), "%02d:%02d", time.hour, time.minute);
                return buf;
```

### Updated Slider Widget
```yaml
- slider:
    id: my_light_slider
    x: 0
    y: 60
    width: 200
    height: 20
    min_value: 0
    max_value: 100
    value: 50
    align: TOP_MID
    pad_all: 8
    on_value:  # Changed from on_release
      - homeassistant.action:
          action: light.turn_on
          data:
            entity_id: light.YOUR_LIGHT_ENTITY
            brightness_pct: !lambda 'return (int) x;'  # Changed from brightness
      - lvgl.label.update:
          id: brightness_value_label
          text: !lambda |-
            char buf[20];
            snprintf(buf, sizeof(buf), "%.0f%%", x);
            return buf;
```

## Maintained Features

✅ Full voice assistant functionality
✅ Wake word detection (Alexa, Hey Jarvis, Okay Nabu)
✅ Battery monitoring and display
✅ Touch screen support
✅ Timer functionality
✅ Media player integration
✅ All switches and configuration options
✅ Startup sound
✅ Mute functionality

## Breaking Changes

⚠️ **None** - Ball V4 is fully compatible with Ball V3 hardware

However, note these behavior changes:
- Touch screen no longer activates voice assistant (use button instead)
- Brightness values in automations should use percentage (0-100) instead of 0-255
- Slider updates immediately instead of on release

## Migration from Ball V3

To upgrade from Ball V3 to Ball V4:

1. Copy your `secrets.yaml` from Ball_v3 to Ball_v4
2. Update the four `light.YOUR_LIGHT_ENTITY` references in Ball_v4.yaml
3. Flash Ball_v4.yaml to your device
4. Reboot the device

No other changes needed!

## Bug Fixes

1. ✅ Fixed: Touch screen no longer accidentally activates voice assistant
2. ✅ Fixed: Layout issues on 240x240 screen (no scrolling needed)
3. ✅ Fixed: Brightness updates are now instant
4. ✅ Fixed: Brightness display updates in real-time

## New Features Summary

| Feature | Ball V3 | Ball V4 |
|---------|---------|---------|
| Brightness Range | 0-255 | 0-100% |
| Slider Update | on_release | on_value (instant) |
| Touch Activates VA | Yes | No |
| Time Display | No | Yes (HH:MM) |
| Live Brightness Feedback | No | Yes |
| Screen Layout | May need scrolling | Fits perfectly |
| Brightness Label | "Brightness: 128" | "50%" |

## Performance Impact

- **Minimal** - Instant updates add negligible processing overhead
- **Network**: Slightly more HA API calls during slider movement (acceptable)
- **Memory**: No significant change
- **Response Time**: Better user experience with instant feedback

## Testing Checklist

When upgrading to Ball V4, verify:
- [ ] Device boots and shows "Ready" page with time display
- [ ] Time displays correctly in HH:MM format
- [ ] Brightness slider responds instantly when moved
- [ ] Brightness percentage label updates as slider moves
- [ ] Light brightness changes in real-time
- [ ] Touching screen does NOT activate voice assistant
- [ ] Physical button DOES activate voice assistant
- [ ] Toggle button works for on/off
- [ ] External brightness changes update slider
- [ ] All controls fit on screen without scrolling
- [ ] Battery display toggles with long press
- [ ] Voice assistant works with wake word

## Support

For issues specific to Ball V4:
- Check the README.md for troubleshooting steps
- Verify all configuration requirements are met
- Ensure Home Assistant actions are enabled for the device

## Future Enhancements

Potential future improvements:
- Color temperature control
- Light effect selection
- Multiple light control
- Preset brightness buttons
- Schedules/automation triggers

## Credits

- Based on Ball V3 by Fear2Die
- Enhanced based on user feedback
- Built on Spotpear V2 LVGL conversion

## License

Same as parent repository
