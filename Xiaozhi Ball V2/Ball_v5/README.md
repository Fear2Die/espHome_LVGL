# ESPHome Xiaozhi Ball V5 - LVGL with Multi-Page Interface

Ball V5 is a major upgrade from Ball V4 with live state tracking, media player controls, and weather display.

> **📢 Important**: If upgrading from an older V5 version and experiencing light flickering, see [QUICK_FIX_GUIDE.md](QUICK_FIX_GUIDE.md) for the fix.

## What's New in Ball V5.1

### 🐛 Bug Fix: Flickering Issue Resolved
- **Fixed**: Light flickering and cycling on/off when adjusting brightness
- **Cause**: Feedback loop between device slider and Home Assistant sensor
- **Solution**: Added protection flags to prevent infinite loops
- **Details**: See [BUGFIX_FLICKERING.md](BUGFIX_FLICKERING.md)

## What's New in Ball V5

### 🌟 Live State Tracking
- **Smart Light Colors**: Lights show gray when off, warm yellow (#FFCC66) when on
- **Real-time Updates**: Display reflects actual device states from Home Assistant
- **Instant Feedback**: Changes in HA immediately update the display

### 🎵 Media Player Page
- **Now Playing Display**: Shows current media title and artist
- **Playback Controls**: Previous, Play/Pause, Next buttons
- **Volume Control**: Slider to adjust media player volume (0-100%)
- **Live State**: Shows ▶ Playing, ⏸ Paused, or ⏹ Idle status
- **Home Assistant Integration**: Controls any HA media player entity

### 🌤️ Weather Page
- **Current Conditions**: Displays weather condition (Sunny, Cloudy, etc.)
- **Temperature**: Large temperature display in °C
- **Humidity**: Current humidity percentage
- **Live Updates**: Syncs with Home Assistant weather entity

### 🔘 Page Navigation
- **Two Navigation Buttons**: Access Media and Weather pages from main screen
- **Back Buttons**: Easy return to main page from any screen
- **Smooth Transitions**: Quick page switching with LVGL

## Features (Inherited from Ball V4)

- ✅ **Instant brightness updates** (on_value vs on_release)
- ✅ **Percentage-based brightness** (0-100% vs 0-255)
- ✅ **Touch doesn't activate assistant** (button only)
- ✅ **Time display** (HH:MM format)
- ✅ **Voice Assistant** with wake word
- ✅ **Battery monitoring**
- ✅ **Timer functionality**

## Hardware

Same as Ball V4:
- ESP32-S3 based device (Xiaozhi Ball)
- 240x240 circular display (GC9A01A)
- Touch screen (CST816)
- Microphone and speaker
- Physical button
- RGB LED
- Battery powered

## Configuration

### 1. Clone and Setup

```bash
git clone https://github.com/Fear2Die/espHome_LVGL.git
cd espHome_LVGL/Ball_v5
```

### 2. Configure WiFi Credentials

Copy the secrets example file and edit it:

```bash
cp secrets.yaml.example secrets.yaml
# Edit secrets.yaml with your WiFi credentials
```

### 3. Configure Your Entities

Replace the following placeholders in `Ball_v5.yaml` with your actual Home Assistant entity IDs:

**Light Entity** (4 locations):
- Line ~213: Brightness sensor
- Line ~1007: State sensor
- Line ~1168: Slider action
- Line ~1198: Button action

Example: `light.living_room_lamp`

**Media Player Entity** (6 locations):
- Line ~253: Volume sensor
- Line ~1028: State sensor
- Line ~1046: Title sensor
- Line ~1057: Artist sensor
- Line ~1320: Previous track action
- Line ~1331: Play/pause action
- Line ~1342: Next track action
- Line ~1359: Volume action

Example: `media_player.living_room_speaker`

**Weather Entity** (3 locations):
- Line ~226: Temperature sensor
- Line ~234: Humidity sensor
- Line ~1019: Condition sensor

Example: `weather.home` or `weather.forecast_home`

### 4. Flash the Device

```bash
esphome run Ball_v5.yaml
```

Select your connection method:
- **USB**: Connect device via USB cable
- **OTA**: Enter device IP if already running ESPHome

### 5. Enable Home Assistant Actions (REQUIRED)

**CRITICAL STEP** - Device actions won't work without this!

1. In Home Assistant: **Settings → Devices & Services → ESPHome**
2. Find **Ball V5** device
3. Click **Configure**
4. ✅ Check: **"Allow the device to perform Home Assistant actions"**
5. Click **Submit**

### 6. Reboot the Device

After configuration, reboot the device to ensure all settings are applied.

## Usage

### Main Page (Idle Page)
- **Top Row**: Time, Status, Battery
- **Brightness Slider**: Control light brightness (0-100%)
- **Brightness Label**: Current brightness percentage
- **Toggle Button**: Turn light on/off
- **Media Button**: Navigate to media player page
- **Weather Button**: Navigate to weather page

### Media Player Page
- **Current Media**: Title and artist display
- **Status**: Playing/Paused/Idle indicator
- **Controls**: Previous, Play/Pause, Next
- **Volume Slider**: Adjust volume (0-100%)
- **Back Button**: Return to main page

### Weather Page
- **Weather Condition**: Current weather state
- **Temperature**: Large temperature display
- **Humidity**: Current humidity level
- **Back Button**: Return to main page

### Voice Assistant
- **Wake Word**: Say configured wake word or press physical button
- **Touch Screen**: Does NOT activate voice assistant (by design)
- **States**: Idle (green) → Listening (blue) → Thinking (orange) → Replying (green)

## Troubleshooting

### Light doesn't change color based on state

1. ✅ Check light entity ID is correct in all 4 locations
2. ✅ Verify Home Assistant connection
3. ✅ Check HA Actions are enabled
4. ✅ Reboot device

### Media player controls don't work

1. ✅ Verify media player entity ID in all 6 locations
2. ✅ Check media player is online in HA
3. ✅ Ensure HA Actions are enabled
4. ✅ Test media player from HA first

### Weather not displaying

1. ✅ Verify weather entity ID in all 3 locations
2. ✅ Check weather integration is configured in HA
3. ✅ Wait up to 1 minute for initial sync
4. ✅ Verify entity has valid data in HA

### Navigation buttons don't work

1. ✅ Confirm you flashed Ball_v5.yaml (not v4)
2. ✅ Check all pages are defined correctly
3. ✅ Reboot device

### Colors not updating

1. ✅ Check text_sensor section for light state
2. ✅ Verify entity_id matches exactly
3. ✅ Test light on/off from HA to trigger update

## Differences from Ball V4

### New Features
1. ✅ **Live state colors** (gray off, warm yellow on)
2. ✅ **Media player page** with full controls
3. ✅ **Weather page** with live data
4. ✅ **Navigation system** with bottom buttons
5. ✅ **Multi-page interface** (3 main pages)

### Layout Changes
- **Toggle button** moved up (y=120 vs y=130)
- **Navigation buttons** added at bottom
- **Reduced toggle button height** (35px vs 45px) to fit nav buttons

### What's the Same
- ✅ All Ball V4 features maintained
- ✅ Voice assistant functionality
- ✅ Time display and battery monitoring
- ✅ Touch screen behavior
- ✅ Same hardware compatibility

## Files

- `Ball_v5.yaml` - Main configuration file (~1450 lines)
- `secrets.yaml.example` - Template for WiFi credentials
- `README.md` - This file
- `CHANGES.md` - Detailed changelog from V4 to V5
- `QUICK_START.md` - 5-minute setup guide

## Entity Configuration Quick Reference

Replace these in Ball_v5.yaml:

```yaml
# Light entity (4 locations)
light.YOUR_LIGHT_ENTITY

# Media player entity (8 locations)
media_player.YOUR_MEDIA_PLAYER_ENTITY

# Weather entity (3 locations)
weather.YOUR_WEATHER_ENTITY
```

## Credits

- Based on Ball V4 by Fear2Die
- Built with ESPHome and LVGL
- Home Assistant integration

## Support

For issues:
- Check entity IDs are correct
- Verify Home Assistant connection
- Ensure HA Actions are enabled
- Review troubleshooting section

## License

MIT License - Free to use and modify
