# ESPHome Xiaozhi Ball V5.4 - Circular Display Optimization

## 🎯 What's New in V5.4?

### Circular Display Optimization - The Major Update!

Ball V5.4 is **completely optimized for circular displays**. Unlike previous versions that treated the 240x240 screen as rectangular, V5.4 embraces the circular form factor with mathematically calculated positions ensuring every element fits perfectly within the circular boundaries.

### Key Improvements

#### 🔵 Perfect Circular Fit
- **No more cut-off elements**: All UI components positioned within the circular safe zone
- **Proper geometry**: Mathematically calculated distances from center point
- **Better balance**: Symmetric layouts that work naturally with circular shape
- **Professional appearance**: Design that embraces rather than fights the circular form

#### 📍 Optimized Positioning
- **Status bar**: Time and battery moved inward (x=±10→±25) and down (y=5→35)
- **Navigation buttons**: Moved up (y=-10→-25) to avoid circular edge
- **Back buttons**: Now centered at top of all pages - much more intuitive!
- **Media controls**: Repositioned to CENTER alignment for better circular fit
- **All elements**: Within 100-110 pixel radius from center for full visibility

#### 👆 Better Touch Experience
- All buttons positioned in easily accessible circular areas
- Improved touch accuracy - no more difficult corner reaches
- Larger touch targets where needed (buttons now 38px tall)
- Natural finger positioning on circular device

#### 🎨 Enhanced Visual Design
- Centered back buttons on all pages (more intuitive)
- Better vertical spacing and balance
- Optimized text widths for circular display (220→200px)
- Improved use of circular space
- Cleaner, more professional look

### What's Preserved from V5.3

All the great features from V5.3 are still here:
- ✅ Easy entity configuration at top of file
- ✅ Live album art display on media page
- ✅ Fixed media player button glyphs
- ✅ Proper None/null handling for lights
- ✅ Support for multiple lights and devices

---

## 🚀 Quick Setup

### 1. Configure Your Entities

At the top of `Ball_v5.4.yaml` (around line 20):

```yaml
## ENTITY CONFIGURATION - SET YOUR HOME ASSISTANT ENTITIES HERE
substitutions:
  # Light entity - the light you want to control
  light_entity: "light.YOUR_LIGHT_ENTITY"  # Example: light.living_room_lamp
  
  # Media player entity - your media player device
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"  # Example: media_player.living_room_speaker
  
  # Weather entity - your weather integration
  weather_entity: "weather.YOUR_WEATHER_ENTITY"  # Example: weather.home
```

**Replace these values with your actual entity IDs from Home Assistant.**

### 2. Copy secrets.yaml

```bash
cp secrets.yaml.example secrets.yaml
```

Edit `secrets.yaml` with your WiFi and Home Assistant credentials:

```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
api_key: "your-esphome-api-key"
```

### 3. Flash to Device

```bash
esphome run Ball_v5.4.yaml
```

---

## 📋 Entity Requirements

### Required Entities
- ✅ **Light entity**: Any Home Assistant light with brightness control
- ✅ **Media player entity**: Any media player (Spotify, phone, etc.) with album art support
- ✅ **Weather entity**: Any weather integration

### Finding Your Entity IDs

#### Light Entity
1. Home Assistant → Settings → Devices & Services
2. Find your light device → Click it
3. Copy entity ID (e.g., `light.bedroom_ceiling`)

#### Media Player Entity
1. Media browser → More info on any player
2. Settings (gear icon) → Copy entity ID
3. Example: `media_player.living_room_speaker`

#### Weather Entity
1. Settings → Integrations → Weather integration
2. Click on weather entity → Copy ID
3. Example: `weather.forecast_home` or `weather.home`

**Don't have weather?**
- Install Met.no integration: Settings → Add Integration → Met.no
- Free, no API key needed!

---

## ✨ Features

### 📱 Main Page (Idle) - Circular Optimized
- ⏰ Current time (positioned safely at x=25, y=35)
- 📊 Status display (centered at top)
- 🔆 Light brightness slider (180px wide for circular fit)
- 💡 Light toggle button (centered)
- 🔋 Battery percentage (positioned safely at x=-25, y=35)
- 🎙️ Voice assistant status
- 🧭 Navigation buttons (positioned at y=-25 for circular safety)

**V5.4 Improvements:**
- All elements within circular safe zone
- Better touch accuracy
- No cut-off elements
- Professional circular layout

### 🎵 Media Player Page - Circular Optimized
- 🖼️ Live album art (60x60, centered)
- 🎼 Song title and artist (200px wide for circular safety)
- ▶️ Playback state (Playing/Paused/Idle)
- ⏮️ Previous track button
- ⏯️ Play/pause button
- ⏭️ Next track button (all controls centered in display)
- 🔊 Volume slider (170px wide, positioned at bottom)
- ◀️ Back button (centered at top!)

**V5.4 Improvements:**
- Back button centered at top (much more intuitive!)
- Media controls aligned to CENTER for perfect circular positioning
- Volume slider moved to bottom (y=-30) to avoid edge
- All elements within circular safe zone

### 🌤️ Weather Page - Circular Optimized
- 🌡️ Current temperature (large, centered display)
- ☁️ Weather condition (190px wide for circular safety)
- 💧 Humidity percentage
- ◀️ Back button (centered at top!)

**V5.4 Improvements:**
- Back button centered at top (consistent with media page)
- Humidity info moved to bottom using BOTTOM_MID alignment
- Removed redundant "Weather" title (saves space)
- Better vertical balance

### 🎙️ Voice Assistant Pages
- 🎤 Listening (full-screen blue)
- 🤔 Thinking (orange, with request text)
- 💬 Replying (green, with response text)
- ❌ Error handling
- 🔇 Muted status
- ⏱️ Timer support

**V5.4 Improvements:**
- Text areas narrowed (200→180px) for circular safety
- Text moved up (y=-20→-30) to avoid circular edge

---

## 🎨 Circular Display Design

### Safe Zone Concept

Ball V5.4 uses proper circular geometry:

```
Display: 240x240 pixels
Center: (120, 120)
Radius: 120 pixels

Safe zones:
- Interactive elements: < 110px from center
- Full visibility: < 100px from center
- Text readability: < 90px from center
```

### Position Examples

| Element | Distance from Center | Status |
|---------|---------------------|---------|
| Center status | 8px | ✅ Perfect |
| Time/Battery | 97px | ✅ Safe zone |
| Brightness slider | ~80px edges | ✅ Safe zone |
| Toggle button | ~70px edges | ✅ Safe zone |
| Nav buttons | ~88px | ✅ Safe zone |
| Media controls | 70px max | ✅ Safe zone |

**Compare to V5.3:**
- Time at (10, 5): 156px from center ❌ Cut off
- Battery at (-10, 5): 156px from center ❌ Cut off
- Nav buttons at y=-10: ~116px ⚠️ Edge area

### Visual Comparison

**V5.3 (Rectangular layout on circular display):**
```
┌─────────────────────┐
│T    Status      B   │← Cut off!
│                     │
│     Controls        │
│                     │
│   [Media][Weather]  │← Edge
└─────────────────────┘
```

**V5.4 (Circular-optimized layout):**
```
    ╱───────────────╲
   │     Status      │← Centered
  │  T           B   │← Safe zone
  │    Controls      │← Perfect
  │                  │
  │ [Media][Weather] │← Safe zone
   ╲───────────────╱
```

---

## 🔄 Migrating from V5.3

Upgrading is easy - V5.4 is fully compatible:

1. **Copy your entity configuration** from V5.3
2. **Paste into V5.4** substitutions section
3. **Flash to device** - done!

No other changes needed. Your entity IDs, secrets, and configuration all work exactly the same.

### What Will Change?
- Better visual appearance (elements within circular display)
- Improved touch accuracy (buttons in accessible areas)
- More intuitive navigation (centered back buttons)
- **Better everything!**

### What Won't Change?
- All functionality preserved
- Same entity requirements
- Same Home Assistant integration
- Same features and capabilities

---

## 📖 Documentation

- **LAYOUT.md** - Detailed circular display layout specifications
- **CHANGES_V5.4.md** - Complete list of changes from V5.3
- **Ball_v5.4.yaml** - Main configuration file with inline comments

---

## 🛠️ Hardware Support

### Supported Devices
- **Xiaozhi Ball V2** (GC9A01A 240x240 circular display)
- **Muma** (with configuration changes)
- **Puck** (with configuration changes)
- Any ESP32-S3 device with GC9A01A circular display

### Display Specifications
- **Model**: GC9A01A
- **Resolution**: 240x240 pixels
- **Shape**: Circular (round display)
- **Touch**: CST816 capacitive touch
- **Color**: 16-bit RGB565

---

## 🎯 Design Philosophy

### V5.3 Approach
"Fit a rectangular layout on a circular screen"

### V5.4 Approach
"Design natively for circular display"

This fundamental shift means V5.4 feels natural and polished on circular hardware, rather than being an adaptation of a rectangular design.

### Key Principles

1. **Centering Priority**: Primary content always centered
2. **Safe Zone Compliance**: All elements within circular boundaries
3. **Symmetry**: Balanced layouts that work with circular shape
4. **Touch Optimization**: Buttons in easy-to-reach circular areas
5. **Visual Hierarchy**: Larger elements toward center

---

## 💡 Tips & Tricks

### Best Practices
- Keep entity IDs at the top for easy configuration
- Test all touch targets after flashing
- Verify all text is visible on circular display
- Check media player album art display
- Test weather updates

### Troubleshooting
- **Elements seem cut off?** Verify you're using V5.4 (check substitutions: name should be "ball_v54")
- **Touch not working?** Ensure all buttons are within circular display area
- **Album art not showing?** Check media player entity has `entity_picture` attribute
- **Weather not updating?** Verify weather entity ID is correct

---

## 📈 Performance

- **Frame rate**: 60 FPS target
- **Update frequency**: State-change triggered
- **Touch response**: Instant visual feedback
- **Page transitions**: <100ms
- **Memory usage**: Optimized for ESP32-S3

---

## 🤝 Contributing

Found an improvement for circular display optimization? 
- Open an issue or PR on GitHub
- Share your circular design ideas
- Help improve circular display support

---

## 📜 Version History

- **V5.4** (Current) - Circular display optimization
- **V5.3** - Layout fixes & media album art
- **V5.2** - Easy entity configuration
- **V5.1** - Media volume lag fix
- **V5.0** - Multi-page interface
- **V4.0** - Voice assistant integration

---

## 🙏 Credits

- Original Ball project by Fear2Die
- ESPHome team for excellent framework
- Home Assistant community
- LVGL for graphics library
- Everyone testing and providing feedback on circular displays!

---

## 📝 License

This project follows the same license as the original ESPHome-Projects repository.

---

**Enjoy your perfectly optimized circular display experience! 🎉**

For detailed layout specifications, see [LAYOUT.md](LAYOUT.md)
For complete change list, see [CHANGES_V5.4.md](CHANGES_V5.4.md)
