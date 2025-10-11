# Ball V6 Filter Status - None Conversion Error Prevention

## Current Status: ✅ ALL FILTERS IN PLACE

As of Ball V6.0 (latest commit), **all numeric Home Assistant sensors have filters** to prevent "Can't convert 'None' to number!" errors.

## Protected Sensors

All the following sensors have `filters` with NaN checking:

### Light Control
| Sensor ID | Entity | Attribute | Filter Default | Line |
|-----------|--------|-----------|----------------|------|
| `ha_light_brightness` | `${light_entity}` | `brightness` | `0.0` | 219-222 |

**Protection:** Returns `0.0` when light is unavailable or doesn't support brightness.

### Weather Display
| Sensor ID | Entity | Attribute | Filter Default | Line |
|-----------|--------|-----------|----------------|------|
| `ha_weather_temperature` | `${weather_entity}` | `temperature` | `0.0` | 235-238 |
| `ha_weather_humidity` | `${weather_entity}` | `humidity` | `0.0` | 255-258 |

**Protection:** Returns `0.0` when weather data is unavailable. Display shows `--°` or `--%` via `on_value` lambda.

### Media Control
| Sensor ID | Entity | Attribute | Filter Default | Line |
|-----------|--------|-----------|----------------|------|
| `ha_media_volume` | `${media_player_entity}` | `volume_level` | `0.5` | 277-279 |
| `ha_media_position` | `${media_player_entity}` | `media_position` | `0.0` | 297-300 |
| `ha_media_duration` | `${media_player_entity}` | `media_duration` | `100.0` | 318-320 |

**Protection:** Returns sensible defaults when media player is unavailable or not playing.

## Filter Pattern

All numeric sensors use this consistent pattern:

```yaml
sensor:
  - platform: homeassistant
    id: sensor_id
    entity_id: ${entity}
    attribute: attribute_name
    filters:
      - lambda: |-
          if (std::isnan(x)) return [default_value];
          return x;
    on_value:
      # Update UI with value
```

## Why Filters Are Necessary

### The Problem
When Home Assistant entities are:
- **Unavailable** (device offline)
- **Not initialized** (during startup)
- **Missing attributes** (entity doesn't support the attribute)
- **Returning None/null** (various reasons)

ESPHome receives `None` and tries to convert it to a number, logging:
```
[W][homeassistant.sensor:015]: 'entity.name': Can't convert 'None' to number!
```

### The Solution
Filters intercept the value **before** ESPHome logs the warning:
1. Home Assistant returns `None`
2. ESPHome converts to `NaN` internally
3. **Filter catches `NaN`** and returns a safe default
4. No warning is logged
5. Value proceeds to `on_value` handler

## Text Sensors (No Filters Needed)

These sensors handle string values and don't cause numeric conversion errors:

| Sensor ID | Entity | Type | Line |
|-----------|--------|------|------|
| `ha_light_state` | `${light_entity}` | State (on/off) | 1148 |
| `ha_weather_condition` | `${weather_entity}` | State (text) | 1167 |
| `ha_media_state` | `${media_player_entity}` | State (playing/paused) | 1176 |
| `ha_media_title` | `${media_player_entity}` | Attribute (text) | 1187 |
| `ha_media_artist` | `${media_player_entity}` | Attribute (text) | 1197 |

## If You Still See Errors

If you're using Ball V6 (latest) and still see "Can't convert 'None' to number!" errors:

### 1. Verify You Have the Latest Version

Check your `Ball_v6.yaml` file:
- **Line 219-222**: Should have filters for `ha_light_brightness`
- **Line 235-238**: Should have filters for `ha_weather_temperature`
- **Line 255-258**: Should have filters for `ha_weather_humidity`
- **Line 277-279**: Should have filters for `ha_media_volume`
- **Line 297-300**: Should have filters for `ha_media_position`
- **Line 318-320**: Should have filters for `ha_media_duration`

### 2. Check Which Entity Is Causing the Error

Look at the warning message:
```
[W][homeassistant.sensor:015]: 'light.living_room_lamp': Can't convert...
                                ^^^^^^^^^^^^^^^^^^^^^ This entity
```

### 3. Verify Entity Configuration

**For light entities:**
- Check the entity exists in Home Assistant (Developer Tools → States)
- Verify it has a `brightness` attribute (not all lights support brightness)
- See **TROUBLESHOOTING_LIGHT_ERRORS.md** for detailed guidance

**For weather entities:**
- Check the entity exists and is updating
- Verify it's a weather integration (not a sensor)
- Weather entities should have `temperature` and `humidity` attributes

**For media player entities:**
- Check the entity exists and is available
- Verify it's a media player (not a sensor)
- Should have `volume_level`, `media_position`, `media_duration` attributes

### 4. Understand Startup Behavior

You might see a few warnings **only during the first 30-60 seconds** after boot:
- This is normal as Home Assistant connection is establishing
- Filters will catch subsequent updates
- Warnings should stop once connection is stable

## Version History

### Ball V6.0 (Current)
- ✅ All 6 numeric sensors have filters
- ✅ Light brightness filter included
- ✅ Weather filters included
- ✅ Media player filters included

### Ball V5.2 - V5.4
- ✅ Light brightness filter added
- ⚠️ Weather filters missing (added in V6.0)
- ⚠️ Some media filters missing

### Ball V5.1 and Earlier
- ❌ No filters on weather sensors
- ⚠️ Limited filter coverage

## Recommendations

1. **Use Ball V6.0 or later**: Includes all necessary filters
2. **Verify entity IDs**: Make sure substitutions point to real entities
3. **Check entity attributes**: Ensure entities support the attributes being read
4. **Monitor logs at startup**: A few warnings during boot are normal
5. **See troubleshooting docs**: If errors persist after 60 seconds

## Related Documentation

- **TROUBLESHOOTING_LIGHT_ERRORS.md**: Detailed light entity troubleshooting
- **QUICK_FIX_V6.9.md**: Quick reference for all fixes
- **FIX_NONE_CONVERSION_ERROR.md**: Technical explanation of the fix
- **CHANGES_V6.9.md**: Full changelog for V6.9

---

**Last Updated**: 2025-10-11  
**Ball Version**: V6.0+  
**Status**: All filters implemented and verified ✅
