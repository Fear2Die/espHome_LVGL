# Ball V5 - Quick Start Guide

## 5-Minute Setup

### Step 1: Get the Files (30 sec)

```bash
git clone https://github.com/Fear2Die/espHome_LVGL.git
cd espHome_LVGL/Ball_v5
```

### Step 2: Configure WiFi (1 min)

```bash
cp secrets.yaml.example secrets.yaml
```

Edit `secrets.yaml`:
```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
ap_password: "FallbackPassword123"
```

### Step 3: Configure Entities (2 min)

Open `Ball_v5.yaml` and replace **ALL** occurrences of:

**Light Entity (4 locations):**
```yaml
light.YOUR_LIGHT_ENTITY
```
Replace with your light entity, example: `light.living_room_lamp`

**Media Player Entity (8 locations):**
```yaml
media_player.YOUR_MEDIA_PLAYER_ENTITY
```
Replace with your media player, example: `media_player.living_room_speaker`

**Weather Entity (3 locations):**
```yaml
weather.YOUR_WEATHER_ENTITY
```
Replace with your weather entity, example: `weather.home`

**Quick Find & Replace:**
```bash
# In your editor, find and replace:
YOUR_LIGHT_ENTITY → your_actual_light
YOUR_MEDIA_PLAYER_ENTITY → your_actual_media_player
YOUR_WEATHER_ENTITY → your_actual_weather
```

### Step 4: Flash the Device (1 min)

```bash
esphome run Ball_v5.yaml
```

Select your connection method:
- **USB**: Connect device via USB cable
- **OTA**: Enter device IP if already running ESPHome

### Step 5: Enable HA Actions (30 sec)

**CRITICAL STEP** - Controls won't work without this!

1. In Home Assistant: **Settings → Devices & Services → ESPHome**
2. Find **Ball V5** device
3. Click **Configure**
4. ✅ Check: **"Allow the device to perform Home Assistant actions"**
5. Click **Submit**

### Step 6: Test It! (30 sec)

1. **Main Page**: 
   - Move brightness slider → light should change
   - Watch slider turn yellow when light is on, gray when off
   - Press "Toggle Light" button

2. **Media Page**:
   - Press "Media" button
   - Try play/pause controls
   - Adjust volume slider

3. **Weather Page**:
   - Press "Weather" button
   - Check temperature displays
   - Verify humidity shows

---

**Done!** 🎉 Your Ball V5 is ready!

## What's Different from Ball V4?

### New Pages
- **Media Player**: Full playback controls and volume
- **Weather**: Live weather conditions and temperature

### Live States
- **Light Colors**: Gray when off, warm yellow when on
- **Real-time Sync**: Display matches actual device states

### Navigation
- **Bottom Buttons**: Access Media and Weather pages
- **Back Buttons**: Easy return to main screen

## Entity Requirements

Ball V5 requires 3 Home Assistant entities:

| Entity Type | Purpose | Example |
|------------|---------|---------|
| Light | Brightness and on/off control | `light.living_room_lamp` |
| Media Player | Playback and volume control | `media_player.spotify` |
| Weather | Temperature and conditions | `weather.home` |

## Finding Your Entity IDs

### Light Entity
1. Home Assistant → Settings → Devices & Services
2. Find your light device
3. Click on it → Copy entity ID
4. Example: `light.bedroom_ceiling`

### Media Player Entity
1. Media browser → More info on any player
2. Settings (gear icon) → Entity ID
3. Example: `media_player.living_room_speaker`

### Weather Entity
1. Settings → Integrations → Weather integration
2. Click on weather entity
3. Copy entity ID from settings
4. Example: `weather.forecast_home`

**Don't have one?**
- **No media player**: Use any HA media player (phone app works)
- **No weather**: Install Met.no integration (Settings → Add Integration → Met.no)

## Troubleshooting

### Light doesn't change when I move slider
1. ✅ Check HA Actions enabled (Step 5)
2. ✅ Verify light entity ID is correct (all 4 locations)
3. ✅ Check device is online in ESPHome
4. ✅ Test light works from HA first
5. ✅ Reboot device

### Light color doesn't change with state
1. ✅ Check light entity ID in text_sensor section
2. ✅ Verify Home Assistant connection
3. ✅ Turn light on/off from HA to trigger update
4. ✅ Wait a few seconds for sync

### Media controls don't work
1. ✅ Check HA Actions enabled
2. ✅ Verify media player entity ID (all 8 locations)
3. ✅ Test media player works from HA
4. ✅ Check media player is online
5. ✅ Try different media player entity

### Weather not displaying
1. ✅ Check weather entity ID (all 3 locations)
2. ✅ Verify weather integration configured
3. ✅ Wait up to 1 minute for initial data
4. ✅ Check entity has valid data in HA
5. ✅ Try different weather entity

### Navigation buttons don't work
1. ✅ Confirm you flashed Ball_v5.yaml (not v4)
2. ✅ Check for compilation errors
3. ✅ Reboot device
4. ✅ Reflash if needed

### "Page not found" error
1. ✅ Verify all pages are defined (idle, media, weather)
2. ✅ Check YAML syntax is correct
3. ✅ Look for compilation errors in ESPHome
4. ✅ Reflash the device

## Accessing Different Pages

### Main Page (Idle)
- Default page on boot
- Shows time, battery, light controls
- Navigation buttons at bottom

### Media Player Page
- Press "Media" button from main page
- Shows current playing media
- Control playback and volume
- Press "Back" to return

### Weather Page
- Press "Weather" button from main page
- Shows current weather conditions
- Temperature and humidity display
- Press "Back" to return

## Voice Assistant Usage

Same as Ball V4:
- **Wake Word**: Say your configured wake word
- **Physical Button**: Press the button on device
- **Touch Screen**: Does NOT activate assistant (by design)

## Pin Reference

Same as Ball V4 (no hardware changes):
- Display: GC9A01A on SPI
- Touch: CST816 on I2C Bus B
- Microphone: I2S on GPIO 10
- Speaker: I2S on GPIO 8
- Button: GPIO 0
- LED: GPIO 48

## Default Values

### Light Control
- Slider range: 0-100%
- Default brightness: 50%
- Color when on: Warm yellow (#FFCC66)
- Color when off: Gray (#555555)

### Media Player
- Volume range: 0-100%
- Default volume: 50%
- Controls: Prev, Play/Pause, Next
- Title length: Max 25 chars (truncated)

### Weather
- Temperature unit: °C
- Humidity: Percentage
- Update frequency: On change from HA

## Advanced Tips

### Customizing Colors

Edit Ball_v5.yaml to change colors:

```yaml
# Light on color (warm yellow)
bg_color: 0xFFCC66

# Light off color (gray)
bg_color: 0x555555

# Media page background
bg_color: 0x1a1a2e

# Weather page background
bg_color: 0x162447
```

### Adding More Lights

To control multiple lights, you'll need to:
1. Add more slider widgets
2. Add more text sensors for each light
3. Adjust layout to fit multiple controls

### Changing Temperature Unit

To display Fahrenheit instead of °C:

```yaml
text: !lambda |-
  char buf[20];
  float temp_f = (x * 9.0/5.0) + 32.0;
  snprintf(buf, sizeof(buf), "%.1f°F", temp_f);
  return buf;
```

### Custom Weather Icons

Weather icons would require image resources:
1. Add image files to ESPHome
2. Map conditions to icons
3. Update weather page layout

## Battery Display

- **Short press**: Shows battery percentage
- **Long press**: Toggles battery display
- **Position**: Top right corner
- **Update**: Real-time monitoring

## Need Help?

### Common Issues
1. **Entities not found**: Check entity IDs match exactly
2. **No connection**: Verify WiFi credentials
3. **Actions don't work**: Enable HA Actions permission
4. **Display issues**: Check display cable connections

### Getting Support
1. Check README.md for detailed info
2. Review CHANGES.md for technical details
3. Verify all configuration requirements
4. Test entities work from HA first

### Debug Mode

Enable debug logging in Ball_v5.yaml:

```yaml
logger:
  level: DEBUG
```

Then check logs in ESPHome for detailed error messages.

## Next Steps

After successful setup:
- ✅ Customize entity IDs for your setup
- ✅ Adjust colors to your preference
- ✅ Set up automations in HA
- ✅ Configure wake word settings
- ✅ Explore media player features
- ✅ Monitor weather updates

---

**Enjoy your enhanced Ball V5!** 🎵🌤️💡
