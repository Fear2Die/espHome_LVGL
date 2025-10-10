# Media Screen Layout - Ball V6.1

## Overview
The media screen now includes a half-circle volume control arc on the right edge of the screen.

## Layout Diagram

```
┌─────────────────────────┐ 240x240
│                        ╱│ ← Volume Arc
│      ┌────────┐      ╱ │   (right edge)
│      │        │     │  │   start: 135°
│      │ Album  │     │  │   end: 45°
│      │  Art   │      ╲ │   width: 12px
│      │ 100x100│       ╲│   color: orange
│      └────────┘        │
│                        │
│    Song Title Here     │ y: 140
│    Artist Name         │ y: 158
│                        │
│  [<<]   [>]   [>>]     │ y: 176
│                        │
│                        │
└─────────────────────────┘

Legend:
┌────────┐  Album art (100x100, rounded corners)
[<<][>]    Media control buttons (45x45, circular)
╱│╲        Volume arc (curves along right edge)
```

## Widget Specifications

### Volume Control Arc
| Property | Value | Description |
|----------|-------|-------------|
| **ID** | `media_volume_arc` | ESPHome component ID |
| **Position** | CENTER_RIGHT | Aligned to right edge, vertically centered |
| **Offset** | x: 0, y: 0 | No offset from edge |
| **Size** | 80 x 240 | Width: 80px, Height: full screen |
| **Range** | 0 - 100 | Internal value (converted to 0.0-1.0 for HA) |
| **Start Angle** | 135° | Top of right edge |
| **End Angle** | 45° | Bottom of right edge |
| **Arc Width** | 12px | Track and indicator width |
| **Track Color** | 0x2A2A2A | Dark gray (same as other sliders) |
| **Indicator Color** | 0xFFB800 | Orange (matches brightness slider) |
| **Knob Color** | 0xFFFFFF | White |
| **Knob Radius** | 8px | Circular knob |
| **Background** | TRANSP | Transparent (no background fill) |
| **Adjustable** | Yes | Touch to adjust |
| **Gesture Block** | Yes | Prevents screen swipe during use |

### Arc Angle Configuration

The arc uses LVGL angle system where:
- 0° = Right (3 o'clock)
- 90° = Bottom (6 o'clock)
- 180° = Left (9 o'clock)
- 270° = Top (12 o'clock)

Our configuration:
- **135°** = Between left and bottom (7:30 position)
- **45°** = Between right and bottom (4:30 position)
- **Result**: A semi-circle on the right side of the screen

### Visual Representation

```
        0° →
        
270°    +    90°
    ╱   │   ╲
   │    │    │
    ╲   │   ╱
       180°

Volume Arc Angles:
       
  135°  ╱     45°
       │       
       │       
       │       
       │       
```

### Integration with Home Assistant

```yaml
on_value:
  - homeassistant.action:
      action: media_player.volume_set
      data:
        entity_id: ${media_player_entity}
        volume_level: !lambda 'return x / 100.0;'
```

**Behavior**:
1. User touches/drags arc knob
2. Value changes from 0-100 internally
3. Lambda converts to 0.0-1.0 (HA volume_level format)
4. Sends volume_set action to media player
5. Media player volume updates in real-time

### Gesture Prevention

When the volume arc is being adjusted:
1. `on_press` sets `slider_interaction = true`
2. Touchscreen swipe detection checks this flag
3. If flag is true, swipe gestures are ignored
4. `on_release` sets `slider_interaction = false`
5. Swipe gestures work normally again

This prevents accidental screen switching while adjusting volume.

## Other Media Screen Elements

### Album Art
- **Position**: TOP_MID, y: 30
- **Size**: 100 x 100
- **Style**: Rounded corners (radius: 10), gray border (2px)
- **Source**: `album_art_image` (online_image component)
- **Updates**: Automatically from HA entity_picture attribute

### Progress Arc
- **Position**: TOP_MID, y: 20 (wraps around album art)
- **Size**: 120 x 120
- **Color**: Green indicator (0x1DB954 - Spotify green)
- **Width**: 4px
- **Purpose**: Visual progress indicator for currently playing media

### Song Title
- **Position**: TOP_MID, y: 140
- **Width**: 220px
- **Font**: montserrat_14
- **Color**: White (0xFFFFFF)
- **Long Mode**: SCROLL_CIRCULAR (scrolls if too long)

### Artist Name
- **Position**: TOP_MID, y: 158
- **Width**: 220px
- **Font**: montserrat_12
- **Color**: Light gray (0xAAAAAA)
- **Long Mode**: SCROLL_CIRCULAR

### Control Buttons

#### Previous Track
- **Position**: TOP_MID, x: -52, y: 176
- **Size**: 45 x 45
- **Label**: "<<"
- **Action**: media_player.media_previous_track

#### Play/Pause
- **Position**: TOP_MID, y: 176
- **Size**: 45 x 45
- **Label**: ">" (paused) or "||" (playing)
- **Action**: media_player.media_play_pause

#### Next Track
- **Position**: TOP_MID, x: 52, y: 176
- **Size**: 45 x 45
- **Label**: ">>"
- **Action**: media_player.media_next_track

## Color Palette

| Element | Color Code | RGB | Description |
|---------|-----------|-----|-------------|
| Background | 0x000000 | (0,0,0) | Pure black |
| Arc Track | 0x2A2A2A | (42,42,42) | Dark gray |
| Arc Indicator | 0xFFB800 | (255,184,0) | Orange/amber |
| Knob | 0xFFFFFF | (255,255,255) | White |
| Progress | 0x1DB954 | (29,185,84) | Spotify green |
| Text Primary | 0xFFFFFF | (255,255,255) | White |
| Text Secondary | 0xAAAAAA | (170,170,170) | Light gray |
| Button BG | 0x333333 | (51,51,51) | Medium gray |
| Button BG Active | 0x4A4A4A | (74,74,74) | Lighter gray |

## Usage Tips

1. **Volume Adjustment**:
   - Touch anywhere on the arc and drag up/down
   - No need to touch the knob specifically
   - Release to stop adjusting

2. **Swipe Navigation**:
   - Swipe from center or left area to navigate
   - Don't start swipe on the volume arc
   - Arc blocks swipes while adjusting

3. **Visual Feedback**:
   - Arc indicator shows current volume level
   - White knob moves along arc
   - Changes reflect in Home Assistant immediately

## Technical Notes

### LVGL Arc Component
The arc widget in LVGL is highly customizable:
- Can be full circle or partial (our case: 135° to 45°)
- Supports touch interaction with adjustable mode
- Knob can be hidden or styled
- Background can be colored or transparent
- Works well for circular/semi-circular controls

### Why Right Edge?
- Natural position for volume control (away from main controls)
- Thumb-friendly for right-handed use
- Doesn't interfere with album art or buttons
- Visually balanced with centered content
- Similar to iOS Control Center volume slider

### Performance Considerations
- Arc rendering is efficient in LVGL
- Touch events are processed smoothly
- No lag when adjusting volume
- Updates to Home Assistant are throttled by ESPHome

## Troubleshooting

### Volume arc not visible
- Check `bg_opa: TRANSP` is set (background should be transparent)
- Verify arc_color and indicator colors are different from black
- Check start_angle and end_angle values

### Volume not changing in HA
- Verify media_player_entity is correct in substitutions
- Check Home Assistant logs for volume_set actions
- Ensure media player supports volume_set service

### Screen switches while adjusting volume
- Verify slider_interaction flag is being set
- Check on_press and on_release handlers are present
- Ensure touchscreen on_release checks slider_interaction flag

### Arc knob hard to grab
- Consider increasing knob radius (currently 8px)
- Adjust arc_width if needed (currently 12px)
- Ensure adjustable: true is set

## Future Enhancements

Possible improvements for future versions:
- Add volume percentage label near arc
- Animate arc indicator smoothly
- Add haptic feedback on volume change
- Sync arc value with HA volume attribute
- Add mute button/gesture
- Color-code volume level (red at high volume)
