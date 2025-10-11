# Quick Reference: "Can't convert 'None' to number!" Error

## 🚨 Seeing This Error?

```
[W][homeassistant.sensor:015]: 'light.living_room_lamp': Can't convert 'None' to number!
```

## ⚡ 30-Second Check

### Step 1: Identify the Entity
Look at the error message - which entity is mentioned?
- `light.*` → Light entity issue
- `weather.*` → Weather entity issue  
- `media_player.*` → Media player issue

### Step 2: Quick Fixes by Entity Type

#### 🔆 Light Entity Error

**Most Common Cause:** Light doesn't support brightness

**Quick Fix:**
1. Open Home Assistant → Developer Tools → States
2. Search for your light (e.g., `light.living_room_lamp`)
3. Click on it and look for `brightness` in attributes
4. **If no brightness:** Your light doesn't support dimming - this is normal for on/off lights

**Solutions:**
- ✅ Use a different dimmable light
- ✅ Keep current light but ignore the error (toggle still works)
- ✅ Update to Ball V6.0+ which has filters (reduces errors)

#### 🌤️ Weather Entity Error

**Most Common Cause:** Weather integration not set up or entity unavailable

**Quick Fix:**
1. Check if you have a weather integration in Home Assistant
2. Verify entity ID in `Ball_v6.yaml` substitutions (line 26):
   ```yaml
   weather_entity: "weather.home"  # Make sure this matches your entity
   ```
3. Update to Ball V6.0+ which includes weather filters

#### 🎵 Media Player Error

**Most Common Cause:** Media player not available or doesn't support attributes

**Quick Fix:**
1. Check entity exists in Home Assistant
2. Verify substitution at line 23:
   ```yaml
   media_player_entity: "media_player.your_speaker"
   ```
3. Update to Ball V6.0+ which includes media filters

## 🔍 Verify You Have Filters

Ball V6.0+ includes filters on **all** numeric sensors. Check your `Ball_v6.yaml`:

### Light Brightness (line ~219)
```yaml
- platform: homeassistant
  id: ha_light_brightness
  entity_id: ${light_entity}
  attribute: brightness
  filters:              # ← Should have this
    - lambda: |-
        if (std::isnan(x)) return 0.0;
        return x;
```

### Weather Temperature (line ~235)
```yaml
- platform: homeassistant
  id: ha_weather_temperature
  entity_id: ${weather_entity}
  attribute: temperature
  filters:              # ← Should have this
    - lambda: |-
        if (std::isnan(x)) return 0.0;
        return x;
```

### Weather Humidity (line ~255)
```yaml
- platform: homeassistant
  id: ha_weather_humidity
  entity_id: ${weather_entity}
  attribute: humidity
  filters:              # ← Should have this
    - lambda: |-
        if (std::isnan(x)) return 0.0;
        return x;
```

## ✅ When to Ignore the Error

**Safe to ignore if:**
- ✓ Only happens during first 30-60 seconds after boot (startup)
- ✓ Entity genuinely doesn't exist and you don't plan to use it
- ✓ Light doesn't support brightness but toggle works fine
- ✓ Errors stop after Home Assistant connection establishes

**Take action if:**
- ✗ Errors continue after 60 seconds
- ✗ Entity should exist but shows as unavailable
- ✗ You want clean logs for easier debugging

## 📋 Detailed Troubleshooting Guides

Choose based on your error:

| Error Entity Type | Guide to Read |
|------------------|---------------|
| `light.*` | **TROUBLESHOOTING_LIGHT_ERRORS.md** |
| `weather.*` | **QUICK_FIX_V6.9.md** |
| `media_player.*` | **QUICK_FIX_V6.9.md** |
| Any entity | **FIX_NONE_CONVERSION_ERROR.md** (technical) |
| Filter status | **FILTER_STATUS.md** |

## 🎯 Best Practices

### 1. Entity Configuration
```yaml
substitutions:
  # Use REAL entity IDs, not placeholders
  light_entity: "light.living_room_lamp"           # ✅ Actual entity
  # Not: light.YOUR_LIGHT_ENTITY                   # ❌ Placeholder
  
  media_player_entity: "media_player.spotify"       # ✅ Real entity
  weather_entity: "weather.home"                    # ✅ Real entity
```

### 2. Entity Verification
Before configuring Ball V6:
1. Open Home Assistant → Developer Tools → States
2. Search for each entity you plan to use
3. Verify entities exist and have the required attributes
4. Copy exact entity IDs (case-sensitive!)

### 3. Version Check
```bash
# Check your Ball_v6.yaml for version indicators
head -20 Ball_v6.yaml

# Look for:
# - "v6.0" or "Ball V6"
# - Recent commit date
# - Filter implementations on sensors
```

## 🔄 Update Process

If you're on an older version:

1. **Backup current config:**
   ```bash
   cp Ball_v6.yaml Ball_v6.yaml.backup
   ```

2. **Download latest Ball_v6.yaml** from repository

3. **Copy your entity IDs:**
   - From old file: lines 20-26 (substitutions)
   - To new file: same section

4. **Flash to device:**
   ```bash
   esphome run Ball_v6.yaml
   ```

5. **Monitor logs for 60 seconds** to verify errors are gone

## 📊 Success Criteria

After applying fixes:

| Metric | Target |
|--------|--------|
| None conversion errors | 0 (after 60s startup) |
| Light control | Works normally |
| Weather display | Shows data or `--°` |
| Media control | Works normally |
| Log cleanliness | No repeating warnings |

## 🆘 Still Need Help?

1. **Check which version you have:**
   ```bash
   grep -A 5 "# Home Assistant light brightness" Ball_v6.yaml
   ```
   Should show `filters:` section

2. **Verify entity exists:**
   - Home Assistant → Developer Tools → States
   - Search for the entity in the error message

3. **Check entity attributes:**
   - Click on entity in Developer Tools
   - Look for required attributes (brightness, temperature, etc.)

4. **Review full logs:**
   ```bash
   esphome logs Ball_v6.yaml
   ```

5. **Consult detailed guides:**
   - **TROUBLESHOOTING_LIGHT_ERRORS.md** - Most comprehensive
   - **FILTER_STATUS.md** - Current protection status
   - **QUICK_FIX_V6.9.md** - Quick fixes

---

**Quick Help:**
- Error with light? → **TROUBLESHOOTING_LIGHT_ERRORS.md**
- Need filter examples? → **FILTER_STATUS.md**
- Want technical details? → **FIX_NONE_CONVERSION_ERROR.md**
- General issues? → **README.md** (Troubleshooting section)

**Last Updated:** 2025-10-11  
**Ball Version:** V6.0+
