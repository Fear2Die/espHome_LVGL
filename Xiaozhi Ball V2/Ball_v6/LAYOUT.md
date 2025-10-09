# Ball V6 Screen Layout - Enhanced Circular Display

## Display Specifications

- **Resolution**: 240x240 pixels
- **Shape**: Circular display (GC9A01A)
- **Color Depth**: 16-bit (RGB565)
- **Touch**: CST816 capacitive touch with swipe gesture support
- **Circular Display Radius**: 120 pixels (from center at 120,120)

---

## Circular Design Philosophy

Ball V6 embraces the circular form factor with:
- **Circular progress arcs** instead of linear sliders
- **Radial navigation menu** with buttons around center
- **Centered content** for optimal visibility
- **Swipe gestures** for natural navigation
- **Dynamic theming** for personalization

---

## Main Pages

### 1. Idle Page (Home)

**Purpose**: Light control, status display, and navigation hub

**Layout** (Circular Design):
```
         [Status: Ready]
    [Time]           [Battery]
         
    ╭─────────────╮
    │  Brightness │  ← Circular Arc (270°)
    │   Arc 50%   │     Around Center
    │             │
    │  [Toggle]   │  ← Small button near top
    │             │
    │   ♫    ☀   │  ← Radial Menu Buttons
    ╰─────────────╯
    
    Timer Arc (outer) when active
```

**Elements**:
- **Status Label**: "Ready", "Listening", etc. (TOP_MID, y=8)
- **Time**: HH:MM format (TOP_LEFT, x=25, y=35)
- **Battery**: Percentage (TOP_RIGHT, x=-25, y=35)
- **Brightness Arc**: 200x200px, 270° arc (135° to 45°), center aligned
- **Brightness Label**: Shows percentage in center (CENTER, y=0)
- **Toggle Button**: On/Off control (CENTER, y=-90, 120x30px)
- **Radial Navigation**:
  - Media button: Left side (x=-75, 60x60 circular)
  - Weather button: Right side (x=+75, 60x60 circular)
- **Timer Arc**: 220x220px outer ring when timer active (hidden by default)
- **Timer Label**: Shows countdown (CENTER, y=40, hidden by default)

**Colors** (Theme-Dependent):
- Background: Theme-specific (default 0x111111)
- Arc: Theme accent (default 0xFFCC66)
- Status: 0x00FF00 (green) for ready
- Timer: 0xFF6666 (red)

---

### 2. Media Player Page

**Purpose**: Media playback control

**Layout** (Circular Design):
```
      [< Back]
         
    ┌──────────┐
    │ Album    │  ← 60x60 image
    │ Art      │
    └──────────┘
    
    [Song Title]
    [Artist Name]
    [> Playing]
    
    [<<]  [▶]  [>>]
    
       Volume Arc
         (90°)
      [Vol: 50%]
```

**Elements**:
- **Back Button**: Return to idle (TOP_MID, y=8, 70x32px)
- **Album Art**: 60x60 image (TOP_MID, y=45)
- **Media Title**: Song/track name (TOP_MID, y=112, 200px wide)
- **Artist**: Artist name (TOP_MID, y=128, 200px wide)
- **State**: Playing/Paused/Idle (TOP_MID, y=144)
- **Control Buttons**: 
  - Previous: x=-60, y=162 (44x40px)
  - Play/Pause: x=0, y=162 (44x40px)
  - Next: x=60, y=162 (44x40px)
- **Volume Arc**: 160x160px, 90° arc (225° to 315°), bottom aligned
- **Volume Label**: Shows percentage (BOTTOM_MID, y=-10)

**Colors**:
- Background: 0x1a1a2e (dark blue-gray)
- Buttons: 0x444455 (medium gray)
- Borders: 0x666677 (light gray)
- Volume Arc: Theme accent (default 0x4fc3f7)
- Text: White

---

### 3. Weather Page

**Purpose**: Weather information display

**Layout** (Circular Design):
```
      [< Back]
         
    [Condition]
    (e.g., Sunny)
    
       20.5°C
         
    Humidity: 65%
```

**Elements**:
- **Back Button**: Return to idle (TOP_MID, y=8, 70x32px)
- **Weather Condition**: Text description (TOP_MID, y=55, 190px wide)
- **Temperature**: Large display (CENTER, y=-15)
- **Humidity**: Percentage (CENTER, y=25)

**Colors**:
- Background: 0x162447 (dark blue)
- Back button: 0x1f4068 (medium blue)
- Condition text: 0xFFCC66 (yellow)
- Text: White

---

## Special Pages

### Voice Assistant Pages

Temporary pages during voice assistant use:
- **Listening Page**: Blue background, mic icon
- **Thinking Page**: Orange background, processing icon
- **Replying Page**: Green background, speaker icon

### Status Pages

- **Timer Finished**: Alert when timer completes
- **Error Page**: Shows error messages
- **No HA Connection**: Offline indicator
- **No WiFi**: Connection lost
- **Initializing**: Boot sequence

---

## Swipe Gesture System

### Navigation Flow

```
Idle Page ←→ Media Page ←→ Weather Page
   (0)           (1)            (2)
```

**Swipe Gestures**:
- **Swipe Left** → Next page (0→1, 1→2)
- **Swipe Right** → Previous page (2→1, 1→0)
- **Minimum Distance**: 50 pixels
- **Detection**: Horizontal swipes only (vertical ignored)
- **Threshold**: dx > dy * 1.5 (must be predominantly horizontal)

**Touch Events**:
1. `on_touch`: Store start position (x, y)
2. `on_release`: Calculate swipe distance
3. If valid swipe: Navigate to page
4. Update `current_page_index`

---

## Circular Progress Arcs

### Brightness Arc (Idle Page)

**Specifications**:
- Size: 200x200 pixels
- Position: Center aligned
- Angle: 270° (135° to 45°)
- Range: 0-100%
- Thickness: 8 pixels
- Color: Theme accent
- Adjustable: Yes (touch to change)

**Behavior**:
- Drag around arc to adjust brightness
- Updates Home Assistant in real-time
- Shows current value in center
- Changes color when light is on/off

### Volume Arc (Media Page)

**Specifications**:
- Size: 160x160 pixels
- Position: Bottom middle aligned
- Angle: 90° (225° to 315°)
- Range: 0-100%
- Thickness: 10 pixels
- Color: Theme accent
- Adjustable: Yes (touch to change)

**Behavior**:
- Drag to adjust volume
- Updates media player in real-time
- Shows percentage below arc
- Synchronized with HA

### Timer Arc (Idle Page)

**Specifications**:
- Size: 220x220 pixels
- Position: Center aligned (outer ring)
- Angle: 360° (90° to 90°)
- Range: 0-100% (countdown)
- Thickness: 6 pixels
- Color: Red (0xFF6666)
- Adjustable: No (display only)
- Hidden: When no timer active

**Behavior**:
- Shows remaining time as arc fills
- Label displays time in center
- Auto-hides when timer completes
- Visual countdown indicator

---

## Radial Menu System

### Navigation Button Layout

**Geometry** (Circular Design):
- **Center Point**: (120, 120)
- **Button Radius**: 30px (60x60 buttons)
- **Distance from Center**: 75px

**Positions**:
```
        Center (0, 0)
   ♫                ☀
 Media           Weather
(-75, 0)         (+75, 0)
  Left            Right
```

**Button Design**:
- Size: 60x60 pixels
- Shape: Circular (radius: 30)
- Border: 3px colored
- Icons: Unicode symbols
- Spacing: Optimized for thumb reach

**Colors**:
- Media button:
  - Background: 0x1a1a2e
  - Border: 0x4fc3f7 (blue)
  - Icon: 0x4fc3f7
- Weather button:
  - Background: 0x162447
  - Border: 0xFFCC66 (yellow)
  - Icon: 0xFFCC66

---

## Color Theme System

### Theme Structure

Each theme defines:
- Background color
- Accent color for arcs
- Applied to: Pages, arcs, buttons

### Available Themes

| Theme | Background | Accent | Description |
|-------|-----------|--------|-------------|
| **Dark** | #111111 | #FFCC66 | Default, warm yellow |
| **Blue** | #0a1929 | #4fc3f7 | Cool cyan |
| **Purple** | #1a0a29 | #ce93d8 | Royal violet |
| **Green** | #0a291a | #81c784 | Natural green |
| **Orange** | #291a0a | #ffb74d | Warm orange |

### Theme Application

**Controlled by**: Native ESPHome select entity (appears in Configuration tab)
**Updates**: Real-time when changed
**Persists**: Saved to flash memory

**Affected Elements**:
- Page backgrounds
- Brightness arc color
- Volume arc color
- Button accent colors

---

## Touch Response

### Gesture Detection

**Swipe Gestures**:
- Horizontal swipes for navigation
- Minimum distance: 50px
- Directional threshold: 1.5x ratio
- Response time: <100ms

**Arc Controls**:
- Touch and drag to adjust
- Real-time feedback
- Updates Home Assistant instantly
- Smooth value changes

**Button Taps**:
- Standard tap detection
- Visual feedback on press
- Debounced (no double-taps)
- Reliable activation

### Touch Areas

**Full Screen**: 240x240 pixels
**Safe Zone**: ~200px diameter (100px radius)
**All elements**: Within circular safe zone
**Optimized zones**: Easy thumb reach

---

## Responsive Behavior

### State Updates

- **Instant**: Touch input, arc changes
- **Fast (<500ms)**: Button presses, page navigation
- **Normal (1-2s)**: HA state updates, sensor data
- **Slow (15-30min)**: Weather updates

### Page Transitions

- **Smooth**: Swipe triggers immediate transition
- **No flicker**: Clean page changes
- **Consistent**: Same behavior for buttons and swipes
- **Tracked**: `current_page_index` always accurate

### Dynamic Updates

- **Theme Changes**: Instant color updates
- **Arc Values**: Real-time synchronization
- **Timer Display**: Auto-show/hide based on state
- **Battery**: Updates on change

---

## Implementation Notes

### LVGL Configuration

```yaml
lvgl:
  log_level: WARN
  color_depth: 16
  bg_color: 0x000000
  text_color: 0xFFFFFF
  default_font: montserrat_20
```

### Touch Configuration

```yaml
touchscreen:
  - platform: cst816
    on_touch:
      # Store touch position
    on_release:
      # Detect swipe, navigate
```

### Arc Widget Configuration

```yaml
- arc:
    id: brightness_arc
    width: 200
    height: 200
    start_angle: 135
    end_angle: 45
    arc_width: 8
    adjustable: true
```

### Performance

- **Target FPS**: 60
- **Updates**: On state change only
- **Protection**: Flag-based loop prevention
- **Memory**: Efficient arc rendering
- **Touch**: <100ms response time

---

## Circular Geometry

### Safe Zone Calculation

- **Display Radius**: 120px
- **Safe Radius**: ~100-110px
- **Corner Loss**: ~40px in each corner
- **Element Positioning**: Consider distance from center

### Distance from Center

```
Element Distance = √(x² + y²)

Must be ≤ 110px for full visibility
```

### Optimal Positions

- **Top area**: y = -110 to -80
- **Center area**: y = -40 to +40
- **Bottom area**: y = +80 to +110
- **Side areas**: x = ±80 to ±100

---

## Future Enhancements

Possible improvements for V6.1+:
- Multi-touch support for pinch/zoom
- Rotation gestures for arc controls
- Animated page transitions
- Custom theme editor in UI
- More arc-based controls
- Gesture shortcuts

---

**For implementation details, see Ball_v6.yaml**
**For changes from V5.4, see CHANGES.md**
**For setup instructions, see README.md**
