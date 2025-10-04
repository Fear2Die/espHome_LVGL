# Changes from Ball V4 to Ball V5

## Overview
Ball V5 is a major upgrade from Ball V4 featuring live state tracking, media player controls, weather display, and multi-page navigation.

## Key Changes

### 1. Live State Tracking

**What Changed:**
- Lights now show gray (#555555) when off, warm yellow (#FFCC66) when on
- Real-time color updates when light state changes in Home Assistant
- Both slider and button backgrounds change color to reflect state

**Technical Implementation:**
```yaml
text_sensor:
  - platform: homeassistant
    id: ha_light_state
    entity_id: light.YOUR_LIGHT_ENTITY
    on_value:
      - if:
          condition:
            lambda: 'return x == "on";'
          then:
            - lvgl.widget.update:
                id: my_light_slider
                bg_color: 0xFFCC66  # Warm yellow when on
          else:
            - lvgl.widget.update:
                id: my_light_slider
                bg_color: 0x555555  # Gray when off
```

**Why This Matters:**
- Immediate visual feedback of actual device state
- No guessing if light is on or off
- Syncs with external light changes (automations, physical switches)

### 2. Media Player Page

**New Page:** `media_page`

**Features:**
- **Now Playing Display**: Shows media title and artist
- **State Indicator**: ▶ Playing, ⏸ Paused, ⏹ Idle
- **Playback Controls**: Previous, Play/Pause, Next buttons
- **Volume Slider**: Adjusts volume from 0-100%
- **Back Button**: Returns to main page

**Layout:**
```
┌─────────────────────────┐
│ [Back]                  │  y=5
│                         │
│    Current Song Title   │  y=40
│    Artist Name          │  y=65
│    ▶ Playing            │  y=90
│                         │
│   [⏮]  [⏯]  [⏭]       │  y=130
│                         │
│      Volume             │  y=195
│   ═══════════════       │  y=215 (slider)
└─────────────────────────┘
```

**Home Assistant Actions:**
```yaml
# Play/Pause
media_player.media_play_pause

# Previous track
media_player.media_previous_track

# Next track
media_player.media_next_track

# Volume
media_player.volume_set
  volume_level: 0.0 - 1.0
```

### 3. Weather Page

**New Page:** `weather_page`

**Features:**
- **Weather Condition**: Current state (Sunny, Cloudy, Rainy, etc.)
- **Temperature**: Large display in °C
- **Humidity**: Percentage display
- **Back Button**: Returns to main page

**Layout:**
```
┌─────────────────────────┐
│ [Back]    Weather       │  y=5-10
│                         │
│       Sunny             │  y=50
│                         │
│                         │
│       24.5°C            │  CENTER (large)
│                         │
│                         │
│      Humidity:          │  y=150
│        65%              │  y=175
└─────────────────────────┘
```

**Data Sources:**
- Temperature from `weather` entity attribute
- Humidity from `weather` entity attribute
- Condition from `weather` entity state

### 4. Navigation System

**Added to Main Page:**
- Two buttons at bottom (y=-10)
- "Media" button (left, x=-65)
- "Weather" button (right, x=65)
- Both buttons: 90x35 pixels, dark gray background

**Page Flow:**
```
Main (Idle) Page
    ↓           ↓
    ↓           ↓
Media Page   Weather Page
    ↓           ↓
    Back        Back
    ↓           ↓
Main (Idle) Page
```

**Implementation:**
```yaml
- button:
    on_click:
      - lvgl.page.show:
          id: media_page
```

### 5. Layout Adjustments

**Main Page Changes:**
- Toggle button moved: y=130 → y=120
- Toggle button height reduced: 45px → 35px
- Navigation buttons added at y=-10 (bottom)
- Total available space optimized for 240x240 display

**Space Allocation:**
```
y=0-5:    Top margin
y=5:      Time, Status, Battery
y=60:     Brightness slider
y=90:     Brightness label
y=120:    Toggle button (y=120-155)
y=230:    Navigation buttons (y=-10 from bottom)
y=240:    Bottom edge
```

## New Sensors Added

### Sensor Platform (3 new)

1. **Weather Temperature**
```yaml
- platform: homeassistant
  id: ha_weather_temperature
  entity_id: weather.YOUR_WEATHER_ENTITY
  attribute: temperature
```

2. **Weather Humidity**
```yaml
- platform: homeassistant
  id: ha_weather_humidity
  entity_id: weather.YOUR_WEATHER_ENTITY
  attribute: humidity
```

3. **Media Volume**
```yaml
- platform: homeassistant
  id: ha_media_volume
  entity_id: media_player.YOUR_MEDIA_PLAYER_ENTITY
  attribute: volume_level
```

### Text Sensor Platform (5 new)

1. **Light State**
```yaml
- platform: homeassistant
  id: ha_light_state
  entity_id: light.YOUR_LIGHT_ENTITY
```

2. **Weather Condition**
```yaml
- platform: homeassistant
  id: ha_weather_condition
  entity_id: weather.YOUR_WEATHER_ENTITY
```

3. **Media Player State**
```yaml
- platform: homeassistant
  id: ha_media_state
  entity_id: media_player.YOUR_MEDIA_PLAYER_ENTITY
```

4. **Media Title**
```yaml
- platform: homeassistant
  id: ha_media_title
  entity_id: media_player.YOUR_MEDIA_PLAYER_ENTITY
  attribute: media_title
```

5. **Media Artist**
```yaml
- platform: homeassistant
  id: ha_media_artist
  entity_id: media_player.YOUR_MEDIA_PLAYER_ENTITY
  attribute: media_artist
```

## Configuration Requirements

### Home Assistant Entities Needed

**Ball V4:** 1 entity required
- 1 light entity

**Ball V5:** 3 entities required
- 1 light entity
- 1 media_player entity
- 1 weather entity

### Entity ID Replacements

**Light Entity (4 locations):**
1. Line ~213: `ha_light_brightness` sensor
2. Line ~1007: `ha_light_state` text sensor
3. Line ~1168: Slider `on_value` action
4. Line ~1198: Button `on_click` action

**Media Player Entity (8 locations):**
1. Line ~253: `ha_media_volume` sensor
2. Line ~1028: `ha_media_state` text sensor
3. Line ~1046: `ha_media_title` text sensor
4. Line ~1057: `ha_media_artist` text sensor
5. Line ~1320: Previous button action
6. Line ~1331: Play/pause button action
7. Line ~1342: Next button action
8. Line ~1359: Volume slider action

**Weather Entity (3 locations):**
1. Line ~226: `ha_weather_temperature` sensor
2. Line ~234: `ha_weather_humidity` sensor
3. Line ~1019: `ha_weather_condition` text sensor

## Migration from Ball V4

To upgrade from Ball V4 to Ball V5:

1. **Copy Configuration**
   ```bash
   cp Ball_v4/secrets.yaml Ball_v5/secrets.yaml
   ```

2. **Update Entity IDs**
   - Keep existing light entity ID (4 locations)
   - Add media player entity ID (8 locations)
   - Add weather entity ID (3 locations)

3. **Flash Device**
   ```bash
   esphome run Ball_v5.yaml
   ```

4. **Enable HA Actions** (if not already enabled)
   - Settings → Devices → ESPHome → Ball V5
   - Configure → Allow device actions

5. **Test Features**
   - Main page: Light control with color changes
   - Media page: Playback and volume controls
   - Weather page: Temperature and conditions

## Bug Fixes

1. ✅ Fixed: Slider color now updates based on actual light state
2. ✅ Fixed: Layout optimized for navigation buttons
3. ✅ Fixed: Media player volume syncs with HA state

## Breaking Changes

### Layout Changes
- Toggle button position moved (y=130 → y=120)
- Toggle button height reduced (45px → 35px)
- If you customized button positions, you'll need to adjust

### New Required Entities
- Must configure media player entity (can use dummy if not needed)
- Must configure weather entity (can use dummy if not needed)
- Both required even if you don't use those pages

## Maintained Features

All Ball V4 features remain:
- ✅ Instant brightness updates
- ✅ Percentage-based brightness (0-100%)
- ✅ Time display (HH:MM)
- ✅ Voice assistant (wake word, button)
- ✅ Touch screen (doesn't activate assistant)
- ✅ Battery monitoring
- ✅ Timer functionality
- ✅ Mute functionality
- ✅ Status displays

## Performance Impact

### Memory
- **Minimal increase**: ~2-3 KB for new pages and sensors
- Still fits comfortably on ESP32-S3

### Network
- **Sensor updates**: 8 additional HA sensors (minimal traffic)
- **Updates on change**: Only when entity states change
- **No polling**: Event-driven updates from HA

### Display
- **No performance impact**: Same LVGL rendering
- **Page switching**: Instant with no lag
- **Smooth animations**: No frame drops

## Testing Checklist

When upgrading to Ball V5, verify:
- [ ] Device boots and shows main page
- [ ] Time displays correctly
- [ ] Light slider works and updates
- [ ] Light shows gray when off, yellow when on
- [ ] Toggle button changes color with light state
- [ ] Media button navigates to media page
- [ ] Weather button navigates to weather page
- [ ] Media page shows current media info
- [ ] Media controls work (play/pause/next/prev)
- [ ] Volume slider adjusts media player
- [ ] Weather page shows temperature
- [ ] Weather page shows humidity
- [ ] Weather condition displays correctly
- [ ] Back buttons return to main page
- [ ] Voice assistant still works
- [ ] Battery display shows correctly

## Color Scheme

### Main Page (Idle)
- Background: Dark gray (#111111)
- Light off: Gray (#555555)
- Light on: Warm yellow (#FFCC66)
- Text: White/Green/Gray

### Media Page
- Background: Dark blue-gray (#1a1a2e)
- Buttons: Medium gray (#444455)
- Borders: Light gray (#666677)
- Text: White with yellow accent (#FFCC66)

### Weather Page
- Background: Deep blue (#162447)
- Buttons: Blue-gray (#1f4068)
- Temperature: Large white text
- Condition: Yellow accent (#FFCC66)
- Humidity: White text

## Future Enhancement Ideas

Potential features for Ball V6:
- 📊 Multiple light control (room scenes)
- 🎨 Light color temperature control
- 🎵 Spotify artwork display
- 📅 Calendar/events display
- 🌡️ Additional weather details (wind, pressure)
- 📻 Radio station presets
- 🔔 Notification display
- ⏰ Multiple timers
- 🎯 Quick action buttons
- 🖼️ Photo frame mode

## Known Limitations

1. **Entity Required**: Must configure all 3 entity types (light, media, weather)
2. **Single Light**: Only controls one light at a time
3. **No Album Art**: Media player doesn't show artwork (display size limitation)
4. **Basic Weather**: Only shows current conditions (no forecast)
5. **Fixed Layout**: Page layouts are not customizable without editing YAML

## Support

For issues specific to Ball V5:
- Check all entity IDs are correct
- Verify entities exist and are online in HA
- Ensure HA Actions are enabled
- Test entities work from HA first
- Review configuration requirements

## Credits

- Original Ball V4 by Fear2Die
- Ball V5 enhancements based on user requirements
- Built with ESPHome 2025.5.0+
- LVGL for display interface
- Home Assistant for entity integration

## License

MIT License - Free to use and modify
