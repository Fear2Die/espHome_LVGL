# Ball V6.1 Changes

## Summary of Changes

This update addresses several UI/UX improvements based on user feedback for Ball V6.

## Changes Made

### 1. Main Screen - Title Removal
**Change**: Removed the "Light Control" title from the top of the main screen.
- **Before**: Had "Light Control" label at y: 30
- **After**: Title removed to provide more screen space
- **Note**: The label above the switch still says "Light Switch" to indicate its purpose

**Files Changed**:
- `Ball_v6.yaml`: Removed title label from main_screen widgets
- `screens.c`: Label text changed from "Light Control" to "Light Switch"

### 2. Weather Screen - Data Initialization
**Change**: Updated default weather display values to show placeholders instead of hardcoded data.
- **Before**: Temperature showed "20°", humidity showed "65%"
- **After**: Temperature shows "--°", humidity shows "--%"
- **Reason**: These placeholders will be updated by Home Assistant once the entity data is received, making it clear when data hasn't loaded yet

**Files Changed**:
- `Ball_v6.yaml`: Updated default text for weather_temp_label and weather_humidity_value
- `screens.c`: Updated default text for temperature and humidity labels

### 3. Weather Screen - Humidity Container Position
**Change**: Adjusted humidity container vertical position to prevent bottom clipping.
- **Before**: y: 165 (was causing clipping at bottom edge)
- **After**: y: 155 (provides 10px more clearance from bottom)

**Files Changed**:
- `Ball_v6.yaml`: Changed humidity container y position
- `screens.c`: Changed humidity container y position

### 4. Slider Interaction - Prevent Swipe Navigation
**Change**: Added logic to prevent screen switching while using sliders.
- **Before**: Sliding on brightness slider could trigger screen swipe navigation
- **After**: Screen swipe is disabled during slider interaction

**Implementation**:
- Added new global variable `slider_interaction` to track when sliders are being used
- Added `on_press` and `on_release` handlers to brightness slider
- Added `on_press` and `on_release` handlers to volume arc
- Modified swipe detection logic to check `!id(slider_interaction)` before processing swipe

**Files Changed**:
- `Ball_v6.yaml`: 
  - Added slider_interaction global
  - Added press/release handlers to brightness_slider
  - Added press/release handlers to media_volume_arc
  - Modified touchscreen on_release swipe detection logic

### 5. Media Screen - Volume Control
**Change**: Added a half-circle arc volume slider on the right edge of the media screen.

**Implementation**:
- Arc positioned at RIGHT_MID with x: 0, y: 0
- Width: 80, Height: 240 (spans full screen height)
- Arc angles: 135° to 45° (creates right-side half-circle)
- Arc width: 12px with orange indicator (matches brightness slider color)
- Range: 0-100 (converted to 0.0-1.0 for volume_level)
- Transparent background to blend with screen
- Calls `media_player.volume_set` action on value change

**Files Changed**:
- `Ball_v6.yaml`: Added media_volume_arc widget to media_screen

### 6. Media Screen - Album Art (Verified)
**Status**: Album art functionality is already correctly implemented.
- Image widget uses `album_art_image` online_image component
- Positioned at TOP_MID with y: 30 (centered horizontally)
- Size: 100x100 with rounded corners (radius: 10)
- Border: 2px with gray color
- HA integration fetches entity_picture attribute and updates the image

**No changes needed** - This was already working as expected.

## Testing Recommendations

1. **Main Screen**: Verify the screen looks clean without the title
2. **Weather Screen**: 
   - Verify placeholders show "--°" and "--%" on boot
   - Verify actual weather data updates correctly from Home Assistant
   - Verify humidity container doesn't clip at bottom
3. **Slider Interaction**: 
   - Test that brightness slider works normally
   - Test that dragging on slider doesn't switch screens
   - Test that swipes still work outside slider area
4. **Media Screen**:
   - Test volume arc on right edge controls media player volume
   - Test that volume arc interaction doesn't switch screens
   - Verify album art displays when media is playing
   - Test that all media controls still work

## Configuration Requirements

Users must configure these entity IDs in the YAML substitutions section:
```yaml
substitutions:
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
```

## Breaking Changes

None - All changes are backward compatible.

## Visual Changes

### Main Screen
```
Before:                      After:
┌─────────────────────────┐  ┌─────────────────────────┐
│   Light Control    [30] │  │                         │
│                         │  │                         │
│ 10:15           100%    │  │ 10:15           100%    │
│                         │  │                         │
│     Brightness          │  │     Brightness          │
│  [=================>]   │  │  [=================>]   │
│                         │  │                         │
│    Light Switch         │  │    Light Switch         │
│      [  ○ ═══ ]         │  │      [  ○ ═══ ]         │
│                         │  │                         │
└─────────────────────────┘  └─────────────────────────┘
```

### Weather Screen
```
Before:                      After:
┌─────────────────────────┐  ┌─────────────────────────┐
│       Weather           │  │       Weather           │
│   Partly Cloudy         │  │   Partly Cloudy         │
│                         │  │                         │
│        20°              │  │        --°              │
│                         │  │                         │
│   ┌───────────────┐     │  │   ┌───────────────┐     │
│   │   Humidity    │     │  │   │   Humidity    │     │
│   │     65%       │     │  │   │     --%       │     │
│   └───────────────┘     │  │   └───────────────┘     │
│                    [165]│  │                    [155]│
└─────────────────────────┘  └─────────────────────────┘
          ↑ Clipping              ↑ No clipping
```

### Media Screen
```
New Volume Control:
┌─────────────────────────┐
│      Album Art    ╱     │
│     [  ♪   ]    ╱       │← Volume arc
│                │        │
│   Song Title    ╲       │
│   Artist         ╲      │
│                         │
│ [<<]  [>]  [>>]         │
└─────────────────────────┘
```

## Version

- Version: 6.1
- Date: 2025-10-10
- Based on: Ball V6.0
