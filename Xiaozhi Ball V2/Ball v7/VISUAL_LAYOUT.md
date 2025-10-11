# Ball V7 - Visual Layout Guide

## Media Screen Layout

### Overview

The media screen displays album art centered inside a progress arc, with song information and playback controls.

---

## Detailed Layout

```
┌────────────────────────────────────┐
│                                    │ Display: 240×240 circular
│  ┌─────────────────────────────┐   │
│  │                             │   │
│  │          ◐─────────┐        │   │
│  │         ╱   ┌─────┐ ╲       │   │ y:20 - Progress Arc (120×120)
│  │        │    │█████│  │      │   │        Green indicator (#1DB954)
│  │        │    │█████│  │      │   │        6px width
│  │        │    │█████│  │      │   │
│  │        │    │█████│  │      │   │ y:30 - Album Art (100×100)
│  │        │    └─────┘  │      │   │        RGB565 format
│  │         ╲           ╱        │   │        10px rounded corners
│  │          ─────────┘          │   │        2px gray border
│  │                             │   │
│  │                             │   │
│  │      Now Playing Song       │   │ y:140 - Song Title
│  │         Artist Name         │   │ y:158 - Artist Name
│  │                             │   │
│  │  ┌────┐  ┌────┐  ┌────┐    │   │
│  │  │ << │  │ ▶  │  │ >> │    │   │ y:176 - Media Controls
│  │  └────┘  └────┘  └────┘    │   │
│  │                             │   │
│  └─────────────────────────────┘   │
│                                    │
│  │← Volume slider (left edge)     │
│                                    │
└────────────────────────────────────┘
```

---

## Component Positions

### Progress Arc
- **ID**: `media_progress_arc`
- **Position**: TOP_MID, y: 20
- **Size**: 120×120 pixels
- **Arc Width**: 6 pixels
- **Background Color**: #2A2A2A (dark gray)
- **Indicator Color**: #1DB954 (Spotify green)
- **Value Range**: 0-100 (percentage)
- **Function**: Shows playback progress

### Album Art Image
- **ID**: `album_art_display`
- **Source**: `album_art_image` (online_image component)
- **Position**: TOP_MID, y: 30
- **Size**: 100×100 pixels
- **Radius**: 10 pixels (rounded corners)
- **Border**: 2px, #666666 (gray)
- **Format**: RGB565 (memory efficient)
- **Updates**: Automatic on track change

**Centering Calculation:**
```
Progress Arc: y=20, size=120×120
Album Art: y=30, size=100×100

Vertical centering:
Arc top = 20
Arc center = 20 + 120/2 = 80
Image top = 80 - 100/2 = 30 ✓
```

### Song Title Label
- **ID**: `media_title_label`
- **Position**: TOP_MID, y: 140
- **Width**: 220 pixels
- **Font**: montserrat_14
- **Color**: #FFFFFF (white)
- **Align**: CENTER
- **Long Mode**: SCROLL_CIRCULAR

### Artist Name Label
- **ID**: `media_artist_label`
- **Position**: TOP_MID, y: 158
- **Width**: 220 pixels
- **Font**: montserrat_12
- **Color**: #AAAAAA (light gray)
- **Align**: CENTER
- **Long Mode**: SCROLL_CIRCULAR

### Volume Slider
- **ID**: `media_volume_slider`
- **Position**: LEFT_MID, x: 41, y: -15
- **Size**: 15×180 pixels
- **Orientation**: Vertical
- **Background**: #2A2A2A
- **Indicator**: #FFB800 (orange)
- **Knob**: #FFFFFF, 10px radius
- **Range**: 0-100

### Control Buttons

#### Previous Button
- **Position**: TOP_MID, x: -52, y: 176
- **Size**: 45×45 pixels
- **Radius**: 23 pixels (circular)
- **Background**: #333333
- **Border**: 2px, #FFFFFF
- **Label**: "<<"

#### Play/Pause Button
- **Position**: TOP_MID, y: 176
- **Size**: 45×45 pixels
- **Radius**: 23 pixels (circular)
- **Background**: #4A4A4A
- **Border**: 2px, #FFFFFF
- **Label**: ">" (play) or "||" (pause)

#### Next Button
- **Position**: TOP_MID, x: 52, y: 176
- **Size**: 45×45 pixels
- **Radius**: 23 pixels (circular)
- **Background**: #333333
- **Border**: 2px, #FFFFFF
- **Label**: ">>"

---

## Size Optimization Strategy

### Why 100×100 for Album Art?

1. **Progress Arc Constraint**
   - Arc size: 120×120 pixels
   - Arc width: 6 pixels
   - Inner diameter: 120 - (2 × 6) = 108 pixels
   - Safe image size: 100×100 (4px margin)

2. **Visual Balance**
   - 10-pixel margin all around
   - Prevents arc overlap
   - Clean, professional appearance

3. **Memory Efficiency**
   - RGB565 format: 2 bytes per pixel
   - Total memory: 100 × 100 × 2 = 20KB
   - Cached efficiently by ESP32

4. **Display Quality**
   - High enough resolution for clarity
   - Fits perfectly on 240×240 display
   - No scaling artifacts

---

## Color Scheme

### Media Screen Colors

| Element | Color Code | RGB | Description |
|---------|-----------|-----|-------------|
| Background | #000000 | 0,0,0 | Black |
| Progress Arc (bg) | #2A2A2A | 42,42,42 | Dark gray |
| Progress Arc (indicator) | #1DB954 | 29,185,84 | Spotify green |
| Album Art Border | #666666 | 102,102,102 | Medium gray |
| Song Title | #FFFFFF | 255,255,255 | White |
| Artist Name | #AAAAAA | 170,170,170 | Light gray |
| Volume Slider (bg) | #2A2A2A | 42,42,42 | Dark gray |
| Volume Slider (indicator) | #FFB800 | 255,184,0 | Orange |
| Button (bg) | #333333 / #4A4A4A | Varies | Dark gray |
| Button (border) | #FFFFFF | 255,255,255 | White |
| Knob | #FFFFFF | 255,255,255 | White |

---

## Layout Measurements

### Vertical Spacing

```
Top of display:        0px
                       ↓ 20px
Progress Arc starts:   20px
                       ↓ 10px (margin)
Album Art starts:      30px
                       ↓ 100px (image height)
Album Art ends:        130px
                       ↓ 10px (to match spacing)
Progress Arc ends:     140px
Song Title:            140px
                       ↓ 18px
Artist Name:           158px
                       ↓ 18px
Control Buttons:       176px
                       ↓ 45px (button height)
                       221px
Bottom margin:         19px
Total height:          240px ✓
```

### Horizontal Layout

```
Left edge:             0px
Volume slider:         41px (from left)
                       ↓ 15px (slider width)
                       56px
Margin:                ~92px (center alignment)
Previous button:       -52px from center (120px from left)
Play button:           0px from center (120px from left)
Next button:           +52px from center (172px from left)
Right edge:            240px
```

---

## Album Art Update Flow

```
┌─────────────────────────────────────────────────┐
│ 1. Media Player Changes Track                   │
└────────────────────┬────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────┐
│ 2. HA Updates entity_picture Attribute          │
└────────────────────┬────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────┐
│ 3. HA Template Sensor Updates                   │
│    sensor.now_playing_album_art                 │
│    = http://homeassistant.local:8123/api/...    │
└────────────────────┬────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────┐
│ 4. ESPHome Receives New URL                     │
│    ha_album_art_url sensor triggers on_value    │
└────────────────────┬────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────┐
│ 5. Lambda Updates Image URL                     │
│    id(album_art_image).set_url(url)             │
│    id(album_art_image).update()                 │
└────────────────────┬────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────┐
│ 6. HTTP Request Downloads Image                 │
│    - Fetches from Home Assistant                │
│    - Decodes PNG format                         │
│    - Converts to RGB565                         │
│    - Resizes to 100×100                         │
│    - Caches in memory                           │
└────────────────────┬────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────┐
│ 7. Display Updates                              │
│    - LVGL renders new image                     │
│    - Shows inside progress arc                  │
│    - Rounded corners applied                    │
│    - Border drawn                               │
└─────────────────────────────────────────────────┘
```

---

## Performance Considerations

### Memory Usage
- **Image Buffer**: 20KB (100×100 RGB565)
- **HTTP Buffer**: ~10KB (download buffer)
- **Total Extra**: ~30KB

### Update Time
- **URL Change Detection**: <100ms
- **Image Download**: 500ms-2s (depends on network)
- **Image Processing**: <200ms
- **Display Update**: <50ms
- **Total**: Usually 1-3 seconds

### Optimization
- Image cached until new track
- No repeated downloads for same track
- Async download (doesn't block UI)
- Efficient RGB565 format

---

## Responsive Behavior

### When No Album Art Available
- Image component shows last cached image
- If no image ever loaded, shows blank/transparent
- Labels still update with song/artist info
- Progress arc continues to work

### When Track Changes
- Progress arc resets to 0%
- New album art downloads
- Title and artist update immediately
- Play/pause button updates state

### When Network Issues
- Timeout after 10 seconds
- Logs error message
- Keeps previous image displayed
- Doesn't crash or hang

---

## Comparison with Ball V6

### Ball V6 (Before)
```
     ◐─────┐
    ╱       ╲
   │         │  ← Empty progress arc
    ╲       ╱      No album art
     ─────┘
```

### Ball V7 (After)
```
     ◐─────┐
    ╱ ┌───┐ ╲
   │  │███│  │ ← Album art inside
    ╲ └───┘ ╱     progress arc
     ─────┘
```

---

## Tips for Best Results

1. **Image Quality**
   - Use high-quality album art sources
   - PNG format preferred
   - Square aspect ratio works best

2. **Network Stability**
   - Ensure strong WiFi signal
   - Stable connection to Home Assistant
   - Use local network (not remote)

3. **Media Player Selection**
   - Choose players with good album art support
   - Spotify, YouTube Music work well
   - Test with your specific service

4. **Display Settings**
   - Adjust brightness for visibility
   - Consider lighting conditions
   - Rounded corners enhance appearance

---

## Troubleshooting Visual Issues

### Album Art Too Small
- 100×100 is optimal size for arc
- Larger would overlap with arc
- Cannot increase without redesign

### Album Art Not Centered
- Check y: 30 position value
- Should be centered in 120×120 arc
- Verify arc position is y: 20

### Border Not Visible
- Check border_color: 0x666666
- Increase border_width if needed
- Ensure contrast with image

### Rounded Corners Not Smooth
- Radius: 10 is optimal
- Smaller radius = sharper corners
- Larger radius = more rounded

---

## Credits

Ball V7 Visual Layout by Fear2Die  
Album Art Integration Design  
Based on Ball V6 Architecture
