# Changes from Ball V5.1 to Ball V5.2

## Overview

Ball V5.2 focuses on **easy configuration** and **enhanced features**:
- Centralized entity configuration (set once, use everywhere)
- Fixed media player button glyphs
- Added camera page for security camera
- Fixed 'None' error handling for lights
- Support for multiple devices

## Key Changes

### 1. Easy Entity Configuration

**Problem**: In V5/V5.1, you had to update entity IDs in 16 different locations throughout the YAML file.

**Solution**: Added substitutions section at the top:

```yaml
substitutions:
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
  camera_entity: "camera.YOUR_CAMERA_ENTITY"
```

**Benefits**:
- ✅ Configure once at the top
- ✅ Automatically applied everywhere
- ✅ Easy to add multiple lights
- ✅ No more searching through 16 locations
- ✅ Less error-prone setup

**Locations Updated**: All 16 entity references now use `${light_entity}`, `${media_player_entity}`, etc.

### 2. Fixed Media Player Button Glyphs

**Problem**: Media control buttons used Unicode characters (⏮ ⏯ ⏭ ⏹) that weren't in the font, causing warnings:
```
[W][lvgl:000]: lv_draw_letter: glyph dsc. not found for U+23F9
[W][lvgl:000]: lv_draw_letter: glyph dsc. not found for U+23EE
[W][lvgl:000]: lv_draw_letter: glyph dsc. not found for U+23EF
[W][lvgl:000]: lv_draw_letter: glyph dsc. not found for U+23ED
```

**Solution**: Replaced with standard text symbols:
- ⏮ → `<<` (Previous)
- ⏯ → `>` (Play) / `||` (Pause) - changes based on state
- ⏭ → `>>` (Next)
- ⏹ → `[]` (Idle state indicator)
- ▶ → `>` (Playing state)
- ⏸ → `||` (Paused state)

**Benefits**:
- ✅ No more font glyph warnings
- ✅ Buttons actually show symbols (not empty boxes)
- ✅ Play button updates based on state (> when paused, || when playing)
- ✅ Works with existing montserrat fonts

### 3. Album Art Display

**Added**: Visual placeholder for currently playing media on media player page.

**Implementation**:
```yaml
- obj:
    id: album_art_container
    x: 0
    y: 40
    width: 60
    height: 60
    widgets:
      - label:
          text: "♪"  # Music note symbol
```

**Layout Changes**:
- Album art: y=40 (60x60 box)
- Title: y=110 (moved down from y=40)
- Artist: y=135 (moved down from y=65)
- State: y=160 (moved down from y=90)
- Buttons: y=185 (moved down from y=130)

**Benefits**:
- ✅ Visual representation of media playing
- ✅ Makes page more engaging
- ✅ Clear area for future album art integration

### 4. Camera Page

**New Page**: `camera_page` for security camera quick access.

**Features**:
- Camera entity display
- Information placeholder
- Instructions for HA app viewing
- Back button navigation

**Layout**:
```
┌─────────────────────────┐
│ [Back]                  │  y=5
│                         │
│   Security Camera       │  y=10
│                         │
│   ┌───────────────┐     │
│   │               │     │  y=60
│   │  Camera Feed  │     │
│   │               │     │
│   │ View in HA    │     │
│   │     app       │     │
│   │               │     │
│   └───────────────┘     │
│                         │
│   camera.front_door     │  y=-10
└─────────────────────────┘
```

**Note**: ESP32 LVGL doesn't support live video streaming. Page shows camera entity info and instructs user to view in Home Assistant app.

**Navigation**: Added "Camera" button to main page alongside "Media" and "Weather".

### 5. Fixed 'None' Error for Light Brightness

**Problem**: Error in logs when light returned `None` brightness:
```
[W][homeassistant.sensor:015]: 'light.YOUR_LIGHT_ENTITY': Can't convert 'None' to number!
```

**Solution**: Added filter to handle None/NaN values:

```yaml
sensor:
  - platform: homeassistant
    id: ha_light_brightness
    entity_id: ${light_entity}
    attribute: brightness
    filters:
      - lambda: |-
          if (std::isnan(x)) return 0.0;
          return x;
```

**Benefits**:
- ✅ No more 'None' conversion errors
- ✅ Gracefully handles unavailable lights
- ✅ Sets brightness to 0 when None

### 6. Improved Navigation Layout

**Changed**: Main page navigation buttons layout.

**From** (V5.1):
```
┌─────────────────────────┐
│                         │
│  [Media]    [Weather]   │  y=-10
│                         │
└─────────────────────────┘
```

**To** (V5.2):
```
┌─────────────────────────┐
│                         │
│ [Media][Weather][Camera]│  y=-45
│                         │
└─────────────────────────┘
```

**Changes**:
- 3 buttons instead of 2
- Smaller buttons (70x30 instead of 90x35)
- Moved up to y=-45 to avoid overlap
- Added Camera button

### 7. Updated Device Name

**Changed**: Device name from `ball_v5` to `ball_v52`

**Reason**: Prevents conflicts when running V5.1 and V5.2 devices on same network.

## Technical Changes

### Substitutions Added
```yaml
light_entity: "light.YOUR_LIGHT_ENTITY"
media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"  
weather_entity: "weather.YOUR_WEATHER_ENTITY"
camera_entity: "camera.YOUR_CAMERA_ENTITY"
```

### Entity References Updated (16 locations)
All hardcoded entity IDs replaced with substitutions:
- `light.YOUR_LIGHT_ENTITY` → `${light_entity}`
- `media_player.YOUR_MEDIA_PLAYER_ENTITY` → `${media_player_entity}`
- `weather.YOUR_WEATHER_ENTITY` → `${weather_entity}`

### LVGL Pages Modified
- **idle_page**: Added camera button, adjusted navigation layout
- **media_page**: Added album art, adjusted positions, fixed button labels
- **camera_page**: New page added

### Text Sensor Updated
- **ha_media_state**: Play button label now updates based on state

### Sensor Filter Added
- **ha_light_brightness**: Filter for None/NaN values

## Benefits Summary

### For Users
- ✅ Much easier setup (configure in one place)
- ✅ No more empty boxes on media buttons
- ✅ No more confusing error messages
- ✅ New camera page for security monitoring
- ✅ Visual album art placeholder

### For Developers
- ✅ Easier to maintain (substitutions)
- ✅ Easier to add multiple devices
- ✅ Better error handling
- ✅ Cleaner code structure

## Breaking Changes

### Configuration Changes
If upgrading from V5/V5.1:
1. ⚠️ Must add substitutions section at top
2. ⚠️ Device name changes from `ball_v5` to `ball_v52`
3. ⚠️ Navigation buttons use smaller font (montserrat_16 instead of montserrat_14)

### Layout Changes
- Media page elements moved down to accommodate album art
- Main page navigation buttons repositioned
- 3 navigation buttons instead of 2

### Behavior Changes
- Play/pause button now shows different symbol based on state
- Light brightness defaults to 0 when entity returns None

## Migration Guide

### From V5.1 to V5.2

1. **Copy Ball_v5.2.yaml**
2. **Add substitutions** at the top (lines 20-30)
3. **Set your entity IDs** in substitutions
4. **Copy your secrets.yaml** (no changes needed)
5. **Flash device**
6. **Test all features**

**Note**: No data loss, all settings preserved. Voice assistant configuration unchanged.

## Compatibility

- ✅ ESPHome 2025.5.0 or newer
- ✅ Home Assistant 2024.1.0 or newer
- ✅ All Ball V2 hardware
- ✅ All V5.1 features retained

## Known Limitations

1. **Camera Page**: No live streaming (ESP32 LVGL limitation)
   - Shows camera entity info only
   - User must use HA app for live view
   
2. **Album Art**: Placeholder only (no actual artwork)
   - Shows music note symbol
   - Future enhancement could load artwork via HA

3. **Multiple Lights**: Manual YAML duplication required
   - Add more substitutions
   - Duplicate sensor/control sections
   - Or use HA scripts/scenes

## Future Enhancements

Possible for V5.3+:
- 🔮 Actual album art loading
- 🔮 Camera snapshot display
- 🔮 Swipe navigation between pages
- 🔮 Scene/script buttons
- 🔮 Multiple light controls on one page
- 🔮 Thermostat page

## Testing

Tested features:
- ✅ Light brightness control
- ✅ Light toggle
- ✅ Media player controls
- ✅ Volume slider (no lag)
- ✅ Weather display
- ✅ Camera page navigation
- ✅ Voice assistant (all states)
- ✅ Page navigation
- ✅ None value handling
- ✅ Button glyphs display

## Credits

Based on:
- Ball V5.1 (flickering/lag fix)
- Ball V5.0 (multi-page interface)
- Community feedback and bug reports

## Version

- **Version**: Ball V5.2
- **Date**: January 2025
- **ESPHome**: 2025.5.0+
- **Compatibility**: Ball V2 hardware

---

**For detailed setup instructions, see README.md**
