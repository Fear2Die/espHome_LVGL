# Ball V5.2 - Quick Reference Card

## 🎯 One-Page Cheat Sheet

### Setup (30 seconds)
```yaml
# Edit Ball_v5.2.yaml line 20-31:
substitutions:
  light_entity: "light.YOUR_LIGHT"
  media_player_entity: "media_player.YOUR_PLAYER"
  weather_entity: "weather.YOUR_WEATHER"
  camera_entity: "camera.YOUR_CAMERA"
```

### Flash
```bash
esphome run Ball_v5.2.yaml
```

---

## 📱 Navigation Map

```
        MAIN PAGE
           ↓ ↓ ↓
    ┌──────┼──────┐
    ↓      ↓      ↓
 Media  Weather Camera
    ↓      ↓      ↓
  [Back] [Back] [Back]
    ↓      ↓      ↓
      MAIN PAGE
      
Voice: Press Button Anytime
```

---

## 🎛️ Controls

### Main Page
- **Slider**: Light brightness (0-100%)
- **Button**: Toggle light on/off
- **[Media]**: Go to media player
- **[Weather]**: Go to weather
- **[Camera]**: Go to camera

### Media Page
- **<<**: Previous track
- **>** or **||**: Play/pause (changes with state)
- **>>**: Next track
- **Slider**: Volume (0-100%)
- **[Back]**: Return to main

### Weather Page
- Shows temperature, condition, humidity
- **[Back]**: Return to main

### Camera Page
- Shows camera entity
- Instructions for HA app
- **[Back]**: Return to main

---

## 🔧 Common Commands

```bash
# Validate config
esphome config Ball_v5.2.yaml

# Compile
esphome compile Ball_v5.2.yaml

# Flash (USB first time)
esphome run Ball_v5.2.yaml

# OTA update (after first flash)
esphome run Ball_v5.2.yaml

# View logs
esphome logs Ball_v5.2.yaml

# Generate API key
esphome secrets generate
```

---

## 📋 Entity ID Format

```
light.NAME          # Lights
media_player.NAME   # Media players
weather.NAME        # Weather
camera.NAME         # Cameras
```

**Examples:**
- `light.living_room_lamp`
- `media_player.spotify`
- `weather.forecast_home`
- `camera.front_door`

---

## 🚨 Troubleshooting Quick Fixes

| Problem | Quick Fix |
|---------|-----------|
| Empty media buttons | Use Ball_v5.2.yaml (not v5) |
| "Can't convert None" | Use Ball_v5.2.yaml (filter added) |
| Light doesn't work | Check entity ID in substitutions |
| Media doesn't work | Check entity ID in substitutions |
| Won't compile | Check YAML indentation (spaces) |
| Won't connect WiFi | Check secrets.yaml credentials |
| Can't flash | Hold BOOT button while connecting |

---

## 📊 Status Indicators

### Main Page
- **Green "Ready"**: Voice assistant ready
- **Time**: Current time (HH:MM)
- **⚡XX%**: Battery percentage
- **Gray slider**: Light off
- **Yellow slider**: Light on

### Media Page
- **> Playing**: Media is playing
- **|| Paused**: Media is paused
- **[] Idle**: No media playing
- **♪**: Album art placeholder

---

## 🎨 Color Codes

```yaml
Dark gray:    0x111111  # Main bg
Medium gray:  0x444444  # Buttons
Light gray:   0x888888  # Text dim
White:        0xFFFFFF  # Text bright
Yellow:       0xFFCC66  # Accent/on state
Green:        0x00FF00  # Status good
Blue:         0x0000FF  # Listening
Orange:       0xFF8800  # Thinking
```

---

## 🔤 Button Symbols

```
<<   = Previous track
>    = Play (when paused)
||   = Pause (when playing)
>>   = Next track
[]   = Idle state
♪    = Album art placeholder
⚡   = Battery indicator
```

---

## 📁 File Structure

```
Ball_v5.2/
├── Ball_v5.2.yaml      ← Main config (edit this)
├── secrets.yaml        ← WiFi/API keys (create this)
├── README.md           ← Start here
├── QUICK_START.md      ← 3-min setup
├── INSTALLATION.md     ← Step-by-step
├── CHANGES.md          ← What's new
├── LAYOUT.md           ← Visual layouts
├── COMPARISON.md       ← vs V5.1
└── SUMMARY.md          ← Tech details
```

---

## ⚡ What's New in V5.2

1. ✅ **Easy config** (1 place, not 16)
2. ✅ **Fixed buttons** (<<, >, >> show correctly)
3. ✅ **Camera page** (security camera reference)
4. ✅ **Album art** (♪ placeholder)
5. ✅ **No errors** ('None' handled gracefully)

---

## 🎯 Quick Start Checklist

- [ ] Edit substitutions (4 entity IDs)
- [ ] Create secrets.yaml
- [ ] Compile: `esphome compile`
- [ ] Flash: `esphome run`
- [ ] Test light slider
- [ ] Test media buttons
- [ ] Test navigation
- [ ] Test voice button

---

## 🔗 Quick Links

**In HA:**
- Settings → Devices → Find "Ball V5.2"
- Settings → Integrations → ESPHome
- Developer Tools → States → Search entities

**Commands:**
```bash
# Find light entities
ha-cli state list | grep light.

# Find media players
ha-cli state list | grep media_player.

# Find weather
ha-cli state list | grep weather.

# Find cameras
ha-cli state list | grep camera.
```

---

## 💡 Pro Tips

1. **Use Tab completion** in HA for entity IDs
2. **Test entities in HA** before adding to Ball
3. **Keep backup** of working config
4. **Use OTA updates** after first USB flash
5. **Check logs** if something doesn't work
6. **Start simple** (just light first, then add others)

---

## 📞 Help Priority

1. Check this reference card
2. Read QUICK_START.md
3. Check INSTALLATION.md
4. Read README.md troubleshooting
5. Check ESPHome docs
6. Ask for help (include error logs)

---

## ⏱️ Expected Times

- Configuration: 30 seconds
- First compile: 2-5 minutes
- Flash: 2-3 minutes
- OTA update: 1-2 minutes
- **Total setup: ~10 minutes**

---

## 🎓 Key Concepts

**Substitutions**: Variables defined once, used everywhere
```yaml
${light_entity}  # Becomes "light.living_room"
```

**Sensors**: Get data from Home Assistant
```yaml
- platform: homeassistant
  entity_id: ${light_entity}
```

**Actions**: Control Home Assistant from device
```yaml
- homeassistant.action:
    action: light.toggle
    entity_id: ${light_entity}
```

**LVGL**: Graphics library for UI
- Pages: Different screens
- Widgets: Buttons, sliders, labels
- Events: on_click, on_value

---

## 🏆 Success Criteria

Device working if:
- ✅ Shows in Home Assistant
- ✅ Light slider works
- ✅ Media buttons work
- ✅ Weather displays
- ✅ Voice assistant responds
- ✅ No errors in logs

---

## 📝 Quick Notes Space

```
My Entity IDs:
Light:        _______________________
Media:        _______________________
Weather:      _______________________
Camera:       _______________________

WiFi SSID:    _______________________
Device IP:    _______________________
API Key:      _______________________

Installation: _____ / _____ / _____
```

---

**Print this page for quick reference!**

**Everything you need on one page.**
**For details, see README.md**
