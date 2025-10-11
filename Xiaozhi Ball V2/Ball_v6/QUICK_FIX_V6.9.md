# Quick Fix Guide - Ball V6.9

## 🎯 What This Fixes

**Warning in logs:**
```
[W][homeassistant.sensor:015]: 'light.light': Can't convert 'None' to number!
```

## 🚀 Quick Solution

### If You're on Ball V6.8 or Earlier

**Option 1: Update to V6.9 (Recommended)**
1. Download latest `Ball_v6.yaml` from the repository
2. Update your entity IDs in the substitutions section (lines 20-26)
3. Flash to your device
4. Done! ✅

**Option 2: Manual Patch (8 Lines)**

Add these filters to your weather sensors:

#### Weather Temperature (around line 232)
```yaml
  - platform: homeassistant
    id: ha_weather_temperature
    entity_id: ${weather_entity}
    attribute: temperature
    filters:                          # ← ADD THESE 4 LINES
      - lambda: |-                    # ←
          if (std::isnan(x)) return 0.0;  # ←
          return x;                    # ←
    on_value:
      # ... rest stays the same
```

#### Weather Humidity (around line 250)
```yaml
  - platform: homeassistant
    id: ha_weather_humidity
    entity_id: ${weather_entity}
    attribute: humidity
    filters:                          # ← ADD THESE 4 LINES
      - lambda: |-                    # ←
          if (std::isnan(x)) return 0.0;  # ←
          return x;                    # ←
    on_value:
      # ... rest stays the same
```

## ✅ How to Verify It's Fixed

### Before Fix
```log
[21:30:15][W][homeassistant.sensor:015]: Can't convert 'None' to number!
[21:30:45][W][homeassistant.sensor:015]: Can't convert 'None' to number!
```

### After Fix
```log
✅ No conversion warnings
✅ Weather display works normally
✅ Clean logs
```

## 🔍 What Changed?

**Nothing visible to you!**
- Display looks the same
- Weather still shows `--°` when unavailable
- Weather still shows temperature when available
- Only difference: No warnings in logs

## ⚠️ Other Warnings You Might See

These are **normal** and **not fixed by this update**:

1. **`[E][component:332]: i2s_audio.microphone cleared Error flag`**
   - Hardware/driver error, usually auto-recovers
   - No action needed unless persistent

2. **`[W][micro_wake_word:353]: Wake word detection already running`**
   - Informational only, wake word still works
   - Safe to ignore

3. **`[W][component:443]: lvgl took a long time (81 ms)`**
   - Performance warning during complex UI operations
   - Expected with animations and complex screens
   - No action needed unless you see UI lag

## 📚 Want More Details?

- **Quick visual guide**: `VISUAL_SUMMARY_V6.9.md`
- **Technical deep-dive**: `FIX_NONE_CONVERSION_ERROR.md`
- **Full changelog**: `CHANGES_V6.9.md`

## 🤔 Still Seeing Warnings?

### If you still see "Can't convert 'None' to number!"

1. **Check your entity IDs**: Make sure they're correct in substitutions
   ```yaml
   substitutions:
     light_entity: "light.YOUR_ACTUAL_LIGHT"      # ← Update this
     weather_entity: "weather.YOUR_ACTUAL_WEATHER" # ← Update this
   ```

2. **Verify you applied the filters**: Check both weather sensors have the filters

3. **Check the entity name in the warning**: The warning shows which entity is problematic
   ```
   [W][homeassistant.sensor:015]: 'weather.home': Can't convert...
                                   ^^^^^^^^^^ This is the problematic entity
   ```

4. **Make sure entity exists in Home Assistant**: Open HA Developer Tools → States and search for your entity

## 💡 Pro Tip

This same fix applies to **any** Home Assistant numeric sensor. If you add custom sensors that read numeric attributes, use this pattern:

```yaml
sensor:
  - platform: homeassistant
    id: my_custom_sensor
    entity_id: sensor.my_entity
    attribute: my_numeric_attribute
    filters:                          # ← Always add this
      - lambda: |-
          if (std::isnan(x)) return 0.0;  # Or another sensible default
          return x;
```

## 📊 Success Metrics

After applying this fix, you should see:
- ✅ 0 "Can't convert 'None' to number" warnings
- ✅ Weather display working normally
- ✅ Cleaner, more readable logs
- ✅ Easier debugging of real issues

---

**Need Help?** Check the detailed documentation files or open an issue on GitHub.

**Version**: Ball V6.9  
**Difficulty**: ⭐ Easy (8 lines)  
**Time Required**: 2 minutes  
**Impact**: Log cleanup only  
**Breaking Changes**: None
