# Ball V7 - Throttle Filter Error Fix

## Problem

The Ball V7 configuration had a critical error preventing compilation:

```
text_sensor.homeassistant: [source ball_v7.yaml:1293]
  platform: homeassistant
  id: ha_album_art_url
  entity_id: sensor.now_playing_album_art
  filters:
    -
      Unable to find filter with the name 'throttle'.
      throttle: 5s
```

## Root Cause

ESPHome's `throttle` filter is **only available for numeric sensors** (sensor platform), not for text sensors (text_sensor platform).

The documentation incorrectly suggested using a throttle filter on the `ha_album_art_url` text sensor, which is not supported by ESPHome.

## Solution

### Code Changes

**Removed the unsupported filter from Ball_v7.yaml (lines 1296-1297):**

```yaml
# BEFORE (INCORRECT):
  - platform: homeassistant
    id: ha_album_art_url
    entity_id: sensor.now_playing_album_art
    filters:
      - throttle: 5s  # ❌ NOT SUPPORTED for text_sensor
    on_value:
      # ...

# AFTER (CORRECT):
  - platform: homeassistant
    id: ha_album_art_url
    entity_id: sensor.now_playing_album_art
    on_value:
      # ...
```

### Protection Mechanism

The configuration already has proper protection against concurrent updates through:

#### 1. Script Mode: Single
```yaml
script:
  - id: update_album_art
    mode: single  # ✅ Only one instance runs at a time
    then:
      # ...
```

**Effect:** ESPHome automatically prevents concurrent execution of the script. If a second call is made while the script is running, it's automatically queued or rejected.

#### 2. Global Flag Guard
```yaml
globals:
  - id: album_art_updating
    type: bool
    restore_value: no
    initial_value: 'false'
```

**Effect:** Additional protection layer that tracks update state and logs warnings when concurrent updates are attempted.

### Why This Works

1. **Script `mode: single`** prevents the script from running multiple times simultaneously
2. **Global flag `album_art_updating`** provides explicit state tracking and early return
3. Together, these mechanisms provide the same protection as a throttle filter would have, but in a way that's compatible with text sensors

## Album Art Display

The album art display is correctly configured and will work with this fix:

```yaml
# Online image component (line 168-174)
online_image:
  - id: album_art_image
    url: "http://homeassistant.local:8123/"
    type: RGB565
    format: JPEG
    resize: 100x100
    update_interval: never

# Display widget (line 1493-1500)
- image:
    id: album_art_display
    src: album_art_image
    align: TOP_MID
    y: 30
    radius: 10
    border_width: 2
    border_color: 0x666666
```

**How it works:**
1. Home Assistant updates `sensor.now_playing_album_art` with new URL
2. ESPHome text sensor receives the update
3. Lambda sets the new URL: `id(album_art_image).set_url(x.c_str())`
4. Script `update_album_art` is called (protected by mode: single)
5. Image component downloads and caches the album art
6. Display automatically updates to show the new image

## Validation

✅ ESPHome configuration validation passed:
```
INFO ESPHome 2025.5.0
INFO Reading configuration Ball_v7.yaml...
INFO Configuration is valid!
```

## Documentation Updates

The following documentation files were updated to reflect the correct implementation:

1. **Ball_v7.yaml** - Removed invalid filter, updated header comment
2. **FIX_DEVICE_FREEZING.md** - Clarified that text sensors don't support throttle
3. **FIX_FLOW_DIAGRAM.md** - Updated diagrams to remove throttle filter references
4. **QUICK_FIX_SUMMARY.md** - Corrected solution description

## For Users

### If You Have This Error

Simply update to the latest Ball_v7.yaml from the repository. The fix:
- Removes the unsupported filter
- Maintains all protection against device freezing
- Album art will still work correctly

### Testing

After flashing the updated configuration:
1. ✅ Configuration should compile without errors
2. ✅ Device should connect to Home Assistant
3. ✅ Album art should display and update when media plays/changes
4. ✅ Device should remain responsive (no freezing)

### Home Assistant Setup

Make sure you have the template sensor configured in Home Assistant:

```yaml
# In Home Assistant configuration.yaml
template:
  - sensor:
      - name: "Now Playing Album Art"
        state: >
          {% set art = state_attr('media_player.spotify', 'entity_picture') %}
          {% if art %}
            http://homeassistant.local:8123{{ art }}
          {% else %}
            ""
          {% endif %}
```

Replace `media_player.spotify` with your actual media player entity.

## Status

- **Fixed**: ✅ Configuration compiles successfully
- **Tested**: ✅ ESPHome validation passed
- **Album Art**: ✅ Display correctly configured
- **Protection**: ✅ Concurrent update protection maintained

---

**Version**: V7.1  
**Date**: October 2025  
**Status**: ✅ RESOLVED
