# Ball V6.8 - README

## Overview

Ball V6.8 is a refined version of the Ball V6 smart display firmware, focusing on reliability and accuracy. This release removes non-functional album art display and implements real-time progress arc updates for accurate media playback visualization.

**Release Date:** 2025-10-11  
**Based on:** Ball V6.7  
**Status:** ✅ Stable Release

## Key Features

### Media Player Screen
- ✅ **Real-time Progress Arc** - Updates every second during playback
- ✅ **Accurate Position Tracking** - Shows actual playback position, not stale data
- ✅ **Play/Pause/Skip Controls** - Full media control
- ✅ **Volume Slider** - Vertical slider for volume adjustment
- ✅ **Track Information** - Song title and artist with scrolling support

### Light Control Screen
- ✅ **Brightness Slider** - Smooth brightness control (0-100%)
- ✅ **Toggle Switch** - iOS-style light on/off switch
- ✅ **Real-time Sync** - Stays in sync with Home Assistant

### Weather Screen
- ✅ **Current Temperature** - Large, readable display
- ✅ **Weather Condition** - Current weather status
- ✅ **Humidity Level** - Current humidity percentage

### Voice Assistant (Unchanged)
- ✅ **Wake Word Detection** - "Okay Nabu", "Hey Jarvis", "Alexa"
- ✅ **Visual Feedback** - Color-coded screens for different states
- ✅ **Timer Support** - Set and dismiss timers

## What's New in V6.8

### Removed
- ❌ **Album Art Display** - Was not working properly, saved ~20KB memory
- ❌ **HTTP Request Component** - No longer needed
- ❌ **Token Authentication** - Simplified configuration

### Added
- ✅ **Real-Time Progress Arc** - Updates every second
- ✅ **Position Timestamp Tracking** - `media_position_updated_at` sensor
- ✅ **Smooth Animation** - Arc animates during playback

### Changed
- 🔧 **Progress Arc Width** - Increased from 4px to 6px
- 🔧 **Arc Positioning** - Centered without album art

## Quick Start

### 1. Download Configuration
```bash
git clone https://github.com/Fear2Die/ESPHome-Projects.git
cd ESPHome-Projects/Xiaozhi\ Ball\ V2/Ball_v6/
```

### 2. Configure Entities
Edit `Ball_v6.yaml` and set your Home Assistant entities:
```yaml
substitutions:
  light_entity: "light.YOUR_LIGHT"
  media_player_entity: "media_player.YOUR_PLAYER"
  weather_entity: "weather.YOUR_WEATHER"
```

### 3. Configure WiFi
Create or edit `secrets.yaml`:
```yaml
wifi_ssid: "YourWiFiSSID"
wifi_password: "YourWiFiPassword"
```

### 4. Flash Firmware
```bash
esphome run Ball_v6.yaml
```

## Configuration Requirements

### Minimum Requirements
- ESPHome 2025.5.0 or later
- Home Assistant with API enabled
- ESP32-S3 with 16MB flash and PSRAM

### Required Home Assistant Entities
- **Light Entity** - Any light with brightness control
- **Media Player Entity** - Media player with these attributes:
  - `state` (playing/paused)
  - `media_position` (current position in seconds)
  - `media_duration` (total duration in seconds)
  - `media_position_updated_at` (optional, improves accuracy)
  - `media_title` (song title)
  - `media_artist` (artist name)
  - `volume_level` (volume 0.0-1.0)
- **Weather Entity** - Weather integration with temperature and humidity

### Compatible Media Players
✅ **Tested and Working:**
- Spotify
- YouTube Music
- Plex Media Server
- VLC Media Player

⚠️ **May Have Issues:**
- Custom integrations without `media_position_updated_at`
- Media players without duration information

## Hardware

### Supported Devices
- Xiaozhi Ball V2 (ESP32-S3 based)
- Other ESP32-S3 devices with:
  - 240x240 circular display (GC9A01A)
  - Touch controller (CST816)
  - I2S audio (ES8311)
  - Gesture support

### Display
- **Resolution:** 240x240 pixels
- **Type:** GC9A01A circular LCD
- **Colors:** 16-bit (65,536 colors)
- **Touch:** CST816 capacitive touch

## Documentation

### For Users
- **[UPGRADE_V6.7_TO_V6.8.md](UPGRADE_V6.7_TO_V6.8.md)** - Migration guide
- **[QUICK_REFERENCE_V6.8.md](QUICK_REFERENCE_V6.8.md)** - Quick reference

### For Developers
- **[CHANGES_V6.8.md](CHANGES_V6.8.md)** - Technical details
- **[Ball_v6.yaml](Ball_v6.yaml)** - Main configuration
- **[screens.c](screens.c)** - UI layout (C implementation)

## Swipe Navigation

The Ball V6 uses gesture-based navigation:

```
┌─────────────────────────────────────┐
│                                     │
│  Main Screen                        │
│  (Light Control)                    │
│                                     │
│  ← Swipe Left: Media Screen         │
│  → Swipe Right: Weather Screen      │
│                                     │
└─────────────────────────────────────┘
        ↓                       ↑
        ↓                       ↑
┌─────────────────────────────────────┐
│                                     │
│  Media Screen                       │
│  (Music Player)                     │
│                                     │
│  ← Swipe Left: Weather Screen       │
│  → Swipe Right: Main Screen         │
│                                     │
└─────────────────────────────────────┘
        ↓                       ↑
        ↓                       ↑
┌─────────────────────────────────────┐
│                                     │
│  Weather Screen                     │
│  (Weather Display)                  │
│                                     │
│  ← Swipe Left: Main Screen          │
│  → Swipe Right: Media Screen        │
│                                     │
└─────────────────────────────────────┘
```

**Tip:** Swipe at least 60 pixels horizontally to trigger navigation.

## Troubleshooting

### Progress Arc Not Updating
1. Check Home Assistant connection: `esphome logs Ball_v6.yaml`
2. Verify media player entity is playing
3. Wait 30 seconds for time sync
4. Check `media_position` and `media_duration` attributes exist

### Arc Shows Wrong Percentage
1. This is usually due to media player clock skew
2. Will self-correct on next Home Assistant update
3. Not a Ball V6.8 issue - media player reporting issue

### Out of Memory Errors
V6.8 should have **~23KB more free memory** than V6.7. If you still see OOM errors:
1. Reduce log level to `WARN` or `ERROR`
2. Disable unused features
3. Consider upgrading to ESP32-S3 with more RAM

### Display Not Responsive
1. Check touch controller connection
2. Verify I2C bus configuration
3. Try factory reset (hold button for 10 seconds)

## Performance

### Memory Usage (Approximate)
| Component | Size | Status |
|-----------|------|--------|
| LVGL Graphics | ~200KB | Required |
| Display Buffer | ~100KB | Required |
| Audio Buffer | ~50KB | Required |
| Code + Data | ~400KB | Required |
| **Free Heap** | **~250KB** | **Available** |

**Improvement over V6.7:** +23KB more free memory

### Update Frequency
| Component | Frequency | Purpose |
|-----------|-----------|---------|
| Clock Display | Every minute | Show time |
| Progress Arc | Every second | Real-time progress |
| Battery Status | Every minute | Battery level |
| Media Controls | On event | Button presses |
| HA Sensors | On change | State sync |

## API Integration

### Home Assistant Actions

Ball V6.8 calls these Home Assistant actions:

```yaml
# Light control
action: light.turn_on
data:
  entity_id: light.YOUR_LIGHT
  brightness_pct: 50

action: light.toggle
data:
  entity_id: light.YOUR_LIGHT

# Media control
action: media_player.media_play_pause
data:
  entity_id: media_player.YOUR_PLAYER

action: media_player.media_previous_track
data:
  entity_id: media_player.YOUR_PLAYER

action: media_player.media_next_track
data:
  entity_id: media_player.YOUR_PLAYER

action: media_player.volume_set
data:
  entity_id: media_player.YOUR_PLAYER
  volume_level: 0.5
```

### Sensors Monitored

Ball V6.8 monitors these Home Assistant sensors:

```yaml
# Light sensors
- entity: light.YOUR_LIGHT
  attributes:
    - brightness (0-255)
    - state (on/off)

# Media player sensors  
- entity: media_player.YOUR_PLAYER
  attributes:
    - state (playing/paused/idle)
    - media_position (seconds)
    - media_duration (seconds)
    - media_position_updated_at (timestamp)
    - media_title (string)
    - media_artist (string)
    - volume_level (0.0-1.0)

# Weather sensors
- entity: weather.YOUR_WEATHER
  attributes:
    - temperature (°C or °F)
    - humidity (%)
    - condition (string)
```

## Contributing

Found a bug? Have a suggestion? 

1. Check existing issues: https://github.com/Fear2Die/ESPHome-Projects/issues
2. Create a new issue with:
   - Ball version (V6.8)
   - ESPHome version
   - Problem description
   - Logs (if applicable)

## Version History

| Version | Date | Key Changes |
|---------|------|-------------|
| V6.8 | 2025-10-11 | Removed album art, real-time progress arc |
| V6.7 | - | Token authentication, album art attempt |
| V6.6 | - | Volume slider improvements |
| V6.5 | - | Real-time arc attempt (incomplete) |
| V6.4 | - | Continuous arc updates |
| V6.3 | - | Progress arc improvements |
| V6.2 | - | Volume slider fixes |
| V6.1 | - | Media page layout updates |
| V6.0 | - | Initial swipe navigation release |

## License

This project follows the repository's license. See main repository for details.

## Credits

- **Original Hardware:** Xiaozhi Ball V2
- **Firmware:** ESPHome
- **UI Framework:** LVGL (Light and Versatile Graphics Library)
- **Integration:** Home Assistant

## Support

### Official Channels
- Repository: https://github.com/Fear2Die/ESPHome-Projects
- Issues: https://github.com/Fear2Die/ESPHome-Projects/issues

### Community
- ESPHome Discord: https://discord.gg/KhAMKrd
- Home Assistant Community: https://community.home-assistant.io/

---

**Ball V6.8** - Simpler, Faster, More Accurate 🎯
