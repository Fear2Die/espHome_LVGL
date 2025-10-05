# ESPHome Xiaozhi Ball V5.2 - Enhanced Configuration

## What's New in V5.2?

### 🎯 Easy Entity Configuration
- **Set once, use everywhere**: Configure all your Home Assistant entities at the top of the YAML file
- No more searching through 16 different locations to update entity IDs
- Support for multiple lights and devices (just add more substitutions)

### 🎵 Media Player Improvements
- **Fixed button glyphs**: Replaced missing Unicode characters with standard text symbols
- **Album art display**: Added visual placeholder for currently playing media
- **Better volume control**: Existing lag fix from V5.1 maintained

### 📷 Camera Page
- **New security camera page**: Quick access to your camera entity
- **Easy navigation**: Added camera button to main page navigation

### 🐛 Bug Fixes
- **Fixed 'None' error**: Light brightness sensor now handles None/null values gracefully
- **No more glyph warnings**: Removed Unicode characters not available in font

## Quick Setup

### 1. Configure Your Entities (Top of Ball_v5.2.yaml)

At the very top of the YAML file (around line 20), you'll find:

```yaml
## ENTITY CONFIGURATION - SET YOUR HOME ASSISTANT ENTITIES HERE
substitutions:
  # Light entity - the light you want to control
  light_entity: "light.YOUR_LIGHT_ENTITY"  # Example: light.living_room_lamp
  
  # Media player entity - your media player device
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"  # Example: media_player.living_room_speaker
  
  # Weather entity - your weather integration
  weather_entity: "weather.YOUR_WEATHER_ENTITY"  # Example: weather.home
  
  # Camera entity - your security camera
  camera_entity: "camera.YOUR_CAMERA_ENTITY"  # Example: camera.front_door
```

**Replace these values with your actual entity IDs from Home Assistant.**

### 2. Copy secrets.yaml.example

```bash
cp secrets.yaml.example secrets.yaml
```

Edit `secrets.yaml` with your WiFi and Home Assistant credentials.

### 3. Flash to Device

```bash
esphome run Ball_v5.2.yaml
```

## Entity Requirements

### Required Entities
- ✅ **Light entity**: Any Home Assistant light with brightness control
- ✅ **Media player entity**: Any media player (Spotify, phone app, etc.)
- ✅ **Weather entity**: Any weather integration (Met.no works great)

### Optional Entities
- 🔲 **Camera entity**: Security camera (page will show entity info even if camera doesn't stream)

## Finding Your Entity IDs

### Light Entity
1. Home Assistant → Settings → Devices & Services
2. Find your light device → Click it
3. Copy entity ID (e.g., `light.bedroom_ceiling`)

### Media Player Entity
1. Media browser → More info on any player
2. Settings (gear icon) → Copy entity ID
3. Example: `media_player.living_room_speaker`

### Weather Entity
1. Settings → Integrations → Weather integration
2. Click on weather entity → Copy ID
3. Example: `weather.forecast_home` or `weather.home`

**Don't have one?**
- Install Met.no integration: Settings → Add Integration → Met.no (free, no API key needed)

### Camera Entity
1. Settings → Integrations → Camera integration
2. Click on camera entity → Copy ID
3. Example: `camera.front_door`

## Features

### Main Page (Idle)
- ⏰ Current time display
- 🔆 Light brightness control slider (0-100%)
- 💡 Light toggle button
- 🔋 Battery percentage
- 🎙️ Voice assistant status
- 🧭 Navigation to Media, Weather, and Camera pages

### Media Player Page
- 🎵 Album art placeholder
- 🎼 Song title and artist display
- ▶️ Playback state (Playing/Paused/Idle)
- ⏮ ⏯ ⏭ Control buttons (previous, play/pause, next)
- 🔊 Volume slider (fixed lag issue)
- 🔙 Back button

### Weather Page
- 🌡️ Temperature display
- ☁️ Weather condition
- 💧 Humidity percentage
- 🔙 Back button

### Camera Page
- 📷 Security camera info
- ℹ️ Camera entity display
- 💡 Instructions to view in HA app
- 🔙 Back button

*Note: ESP32 LVGL doesn't support live video streaming. The camera page provides camera entity information and quick reference. Use Home Assistant app for live camera view.*

### Voice Assistant Pages
- 👂 Listening (blue screen)
- 🧠 Thinking (orange screen)
- 💬 Replying (green screen)
- ❌ Error states
- 🔇 Muted indicator

## Multiple Lights Support

Want to control more than one light? Just add more substitutions:

```yaml
substitutions:
  light_entity: "light.living_room"
  light_entity_2: "light.bedroom"
  light_entity_3: "light.kitchen"
```

Then duplicate the sensor and control sections in the YAML for each additional light. Or use Home Assistant scripts to control multiple lights with one button.

## Troubleshooting

### Light doesn't change
1. ✅ Check `light_entity` value in substitutions
2. ✅ Verify Home Assistant connection
3. ✅ Enable HA Actions in device settings
4. ✅ Check light has `brightness` attribute

### Media player controls don't work
1. ✅ Verify `media_player_entity` in substitutions
2. ✅ Check media player is online in HA
3. ✅ Test media player from HA first

### Weather not displaying
1. ✅ Verify `weather_entity` in substitutions
2. ✅ Check weather integration configured
3. ✅ Wait up to 1 minute for initial sync

### Camera page shows wrong entity
1. ✅ Update `camera_entity` in substitutions
2. ✅ Reflash device

### "Can't convert 'None' to number" error
This is fixed in V5.2! The light brightness sensor now handles None values. If you still see this:
1. ✅ Make sure you're using Ball_v5.2.yaml (not Ball_v5.yaml)
2. ✅ Check the light entity exists and is available in HA

### Glyph/font warnings in logs
Fixed in V5.2! Media buttons now use standard text (<<, >, >>) instead of Unicode characters.

## Navigation

**From Main Page:**
- Tap "Media" → Media player controls
- Tap "Weather" → Weather information
- Tap "Camera" → Camera info

**From any sub-page:**
- Tap "Back" → Return to main page

**Voice Assistant:**
- Press physical button → Start listening
- Works from any page

## Changes from Ball V5.1

- ✅ Centralized entity configuration (substitutions)
- ✅ Fixed media player button glyphs (no more Unicode warnings)
- ✅ Added album art display area
- ✅ Added camera page for security camera
- ✅ Fixed 'None' error for light brightness
- ✅ Improved documentation
- ✅ 3-button navigation on main page

All V5.1 features retained:
- ✅ Light brightness feedback loop fix
- ✅ Media volume feedback loop fix
- ✅ Live state tracking
- ✅ Multi-page navigation

## Hardware Requirements

- ESP32-S3 (Ball V2 hardware)
- 240x240 GC9A01A display
- CST816 touch screen
- I2S audio (microphone + speaker)

## Software Requirements

- ESPHome 2025.5.0 or newer
- Home Assistant with:
  - At least one light entity with brightness
  - At least one media player entity
  - Weather integration (Met.no recommended)
  - (Optional) Camera entity

## Next Steps

After flashing:
1. ✅ Test light controls
2. ✅ Test media player controls
3. ✅ Check weather display
4. ✅ Test voice assistant
5. ✅ Navigate between pages
6. ✅ Check camera page (if configured)

## Credits

Based on Ball V5.1 (flickering fix) and Ball V5 (multi-page interface).

## Version History

- **V5.2** (Current): Easy configuration, camera page, fixed glyphs
- **V5.1**: Flickering fix for sliders
- **V5.0**: Multi-page interface with media and weather
- **V4.0**: Instant brightness updates
- **V3.0**: Light controls
- **V2.0**: Voice assistant base

---

**Need help?** Check the existing documentation in `Ball_v5/` folder for more details on hardware setup and advanced configuration.
