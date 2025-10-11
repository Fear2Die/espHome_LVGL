# Ball V6 - Swipe Navigation Edition

## Overview

Ball V6 is a modern, gesture-based interface for the Xiaozhi Ball smart display, featuring intuitive swipe navigation and a professionally designed UI using LVGL (Light and Versatile Graphics Library).

## Key Features

### 🎯 Gesture-Based Navigation
- **Swipe Left**: Navigate to next screen (Main → Media → Weather → Main)
- **Swipe Right**: Navigate to previous screen (Main → Weather → Media → Main)
- **Circular Navigation**: Seamlessly loop through all screens
- **Smooth Animations**: 250ms slide transitions for premium feel

### 🎨 Modern UI Design
- **Professional styling** with rounded corners and shadows
- **Consistent color scheme** across all screens
- **High-quality typography** with Montserrat font family
- **Touch-optimized** button sizes and spacing

### 📱 Three Main Screens

#### 1. Main Screen (Light Control)
- Modern iOS-style toggle switch for light control
- Smooth brightness slider with sun icon
- Time and battery status display
- Clean, minimalist design

#### 2. Media Screen
- Album art display with rounded corners and token authentication support
- Real-time circular progress indicator showing playback position
- Song title and artist with scrolling text
- Three control buttons: Previous, Play/Pause, Next
- Professional media player look

#### 3. Weather Screen
- Large temperature display (48pt font)
- Weather condition indicator
- Humidity display in styled container
- Color-coded information hierarchy

## Technical Specifications

### Display
- **Resolution**: 240x240 pixels
- **Shape**: Circular display (GC9A01A)
- **Touch**: CST816 capacitive touch with gesture support

### Navigation System
- **Gesture Detection**: LVGL LV_EVENT_GESTURE events
- **Screen Management**: Circular array with modulo arithmetic
- **Animation**: LV_SCR_LOAD_ANIM_MOVE_LEFT/RIGHT
- **Transition Speed**: 250ms

### Code Structure
```
Ball_v6/
├── screens.c          # Main UI implementation with gesture handling
├── screens.h          # Screen object declarations (external)
├── ui.h              # UI helper functions (external)
├── vars.h            # Variable definitions (external)
├── README.md         # This file
└── LAYOUT.md         # Detailed layout documentation
```

## Improvements Over Previous Versions

### From V5.x
1. **Removed button-based navigation** - No more "Back" or navigation buttons
2. **Added swipe gestures** - Natural, intuitive navigation
3. **Circular navigation** - Continuous loop through screens
4. **Improved layouts** - Better use of circular display space
5. **Professional styling** - Modern design language throughout

### Enhanced LVGL Usage
1. **Proper event handling** - Clean gesture callback system
2. **Efficient screen management** - Centralized navigation function
3. **Better animations** - Smooth directional transitions
4. **Optimized styling** - Consistent use of LVGL style system
5. **Professional effects** - Shadows, rounded corners, borders

## Installation

This is a UI component file (screens.c) that should be integrated into an ESPHome project for the Xiaozhi Ball hardware.

### Requirements
- LVGL 8.x or higher
- Touch input device with gesture support
- GC9A01A circular display (240x240)
- ESPHome environment
- Home Assistant instance with media player entities

### Configuration

Edit the entity configuration section at the top of `Ball_v6.yaml`:

```yaml
substitutions:
  # Required: Your Home Assistant entities
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
  
  # Album Art Configuration
  ha_base_url: "http://homeassistant.local:8123"  # Your HA URL
  ha_token: ""  # Optional: Long-lived access token for authenticated access
```

For detailed album art setup with token authentication, see: **ALBUM_ART_TOKEN_AUTH.md**

### Integration Steps
1. Copy `screens.c` to your project
2. Ensure all header files are available (screens.h, ui.h, etc.)
3. Configure your Home Assistant entities in `Ball_v6.yaml`
4. (Optional) Generate and add long-lived access token for album art
5. Call `create_screens()` during initialization
6. Enable touch gesture detection in your LVGL configuration

## Usage

### Navigation
- **Swipe left**: Move to next screen
- **Swipe right**: Move to previous screen
- **Screen order**: Main → Media → Weather → Main (circular)

### Screen Interactions
- **Main Screen**: 
  - Toggle switch: Turn light on/off
  - Slider: Adjust brightness
  
- **Media Screen**:
  - Left button: Previous track
  - Center button: Play/Pause
  - Right button: Next track
  
- **Weather Screen**:
  - Display only (no interactive elements)

## Customization

### Color Schemes
Edit the hex color values in screens.c:
```c
// Example: Change background color
lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), ...);
```

### Animation Speed
Adjust in navigate_to_screen() function:
```c
lv_scr_load_anim(target_screen, anim_type, 250, 0, false);
//                                          ^^^ Change this value (ms)
```

### Gesture Sensitivity
Configure in LVGL settings:
```c
#define LV_INDEV_DEF_GESTURE_LIMIT 50        // Pixels
#define LV_INDEV_DEF_GESTURE_MIN_VELOCITY 3  // Pixels per frame
```

## Design Philosophy

Ball V6 follows modern UI/UX principles:

1. **Intuitive Navigation**: Swipe gestures are natural on touchscreens
2. **Consistent Visual Language**: All screens follow the same design system
3. **Professional Appearance**: Ready-to-ship product quality
4. **Optimized for Circular Display**: Elements positioned to avoid edge cutoff
5. **Smooth Interactions**: Animations provide feedback and continuity

## Troubleshooting

### Common Issues

#### "Can't convert 'None' to number!" Error

If you see warnings like:
```
[W][homeassistant.sensor:015]: 'light.living_room_lamp': Can't convert 'None' to number!
```

**Quick Fixes:**
1. **Check entity exists in Home Assistant** (Developer Tools → States)
2. **Verify your entity IDs** in the substitutions section
3. **For light entities**: Ensure your light supports brightness (not all lights do)
4. **Update to latest version**: Ball V6 includes filters for all sensors

**Detailed Help:**
- **TROUBLESHOOTING_LIGHT_ERRORS.md**: Comprehensive guide for light-related errors
- **QUICK_FIX_V6.9.md**: Quick fixes for all None conversion errors
- **FIX_NONE_CONVERSION_ERROR.md**: Technical details about the fix

#### Other Common Warnings

These are **normal** and can be safely ignored:
- `[E][component:332]: i2s_audio.microphone cleared Error flag` - Hardware/driver message
- `[W][micro_wake_word:353]: Wake word detection already running` - Informational only
- `[W][component:443]: lvgl took a long time` - Performance info during animations

### Documentation Index

- **README.md**: Overview and features (this file)
- **QUICK_START_V6.md**: Getting started guide
- **QUICK_FIX_V6.9.md**: Quick fixes for common errors
- **TROUBLESHOOTING_LIGHT_ERRORS.md**: Light entity error troubleshooting
- **MIGRATION_GUIDE_V5_TO_V6.md**: Upgrading from V5.x
- **LAYOUT.md**: UI layout details
- **CHANGES_V6.9.md**: Latest changes and improvements
- **FIX_NONE_CONVERSION_ERROR.md**: Technical details on None handling

## Future Enhancements

Potential improvements for future versions:
- [ ] Vertical swipe for additional actions
- [ ] Long-press gestures for settings
- [ ] Multi-page media control with swipe
- [ ] Animated weather icons
- [ ] Dynamic color themes
- [ ] Custom font integration
- [ ] More screen types (calendar, notifications, etc.)

## Credits

- **LVGL**: https://lvgl.io/
- **Base Design**: Inspired by Ball V5.x series
- **Enhanced by**: AI-assisted development with focus on UX

## License

This project is part of the ESPHome-Projects repository. Please refer to the main repository for licensing information.

## Support

For issues, questions, or contributions, please visit:
https://github.com/Fear2Die/ESPHome-Projects

---

**Version**: 6.0
**Last Updated**: 2025-10-10
**Status**: Production Ready
