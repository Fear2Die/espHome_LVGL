# Ball V6 Screen Layout Documentation

## Display Specifications

- **Resolution**: 240x240 pixels
- **Shape**: Circular display
- **Model**: GC9A01A
- **Color Depth**: 16-bit (RGB565)
- **Touch**: CST816 capacitive touch with gesture support
- **Navigation**: Swipe-based (left/right)

## Navigation System

### Gesture Controls

```
┌─────────────────────────────────────────┐
│                                         │
│   Swipe Left  →  Next Screen            │
│   Swipe Right →  Previous Screen        │
│                                         │
│   Screen Flow (Circular):               │
│   Main → Media → Weather → Main         │
│   Main ← Media ← Weather ← Main         │
│                                         │
└─────────────────────────────────────────┘
```

### Technical Implementation
- **Event Type**: LV_EVENT_GESTURE
- **Directions**: LV_DIR_LEFT, LV_DIR_RIGHT
- **Animation**: LV_SCR_LOAD_ANIM_MOVE_LEFT/RIGHT
- **Duration**: 250ms smooth slide
- **Navigation**: Circular array with modulo arithmetic

---

## Screen 1: Main Screen (Light Control)

### Layout Diagram
```
┌─────────────────────────┐ 240x240
│ 10:10           100%    │  y=48  (Status bar)
│                         │
│                         │
│     Brightness          │  y=90  (Label)
│                         │
│   ══════●═══════        │  y=115 (Slider 188x30)
│                         │
│                         │
│   Light Control         │  y=155 (Label)
│                         │
│     ╭───○───╮           │  y=175 (Switch 90x40)
│     ╰───────╯           │
│                         │
│                         │
└─────────────────────────┘
```

### Widget Specifications

#### Status Bar (y=48)
| Widget | Position | Size | Font | Color | Content |
|--------|----------|------|------|-------|---------|
| Date/Time | (51, 48) | Auto | montserrat_14 | White | "10:10" |
| Battery | (153, 48) | Auto | montserrat_14 | White | "100%" |

#### Brightness Section
| Widget | Position | Size | Font | Color | Style |
|--------|----------|------|------|-------|-------|
| Label | (0, 90) | 240x auto | montserrat_12 | Gray #AAA | Centered |
| Slider | (26, 115) | 188x30 | - | Track: #2A2A2A<br>Indicator: #FFB800 | Rounded (r=15)<br>Shadow on knob |

**Slider Details**:
- Range: 0-100
- Default: 50
- Border: 1px #444444
- Knob: White circular, radius 12px, shadow
- Indicator: Warm orange/yellow gradient

#### Light Control Section
| Widget | Position | Size | Font | Color | Style |
|--------|----------|------|------|-------|-------|
| Label | (0, 155) | 240x auto | montserrat_14 | White | Centered |
| Switch | (75, 175) | 90x40 | - | Off: #3A3A3A<br>On: #34C759 | iOS-style<br>Border: 2px |

**Switch Details**:
- Radius: 20px (main), 18px (knob)
- Border: #666666 (off), #34C759 (on)
- Knob: White circular
- Smooth toggle animation

### Color Palette
- **Background**: #000000 (Black)
- **Primary**: #FFB800 (Warm Orange/Yellow)
- **Success**: #34C759 (Green - iOS style)
- **Surface**: #2A2A2A (Dark Gray)
- **Border**: #444444 (Medium Gray)
- **Text Primary**: #FFFFFF (White)
- **Text Secondary**: #AAAAAA (Light Gray)

---

## Screen 2: Media Screen

### Layout Diagram
```
┌─────────────────────────┐ 240x240
│                         │
│      ┌─────────┐        │  y=30-130 (Album art)
│      │  Album  │        │  100x100, rounded
│      │   Art   │        │  with progress arc
│      └─────────┘        │
│                         │
│     Song Title          │  y=140 (Scrolling)
│     Artist Name         │  y=158 (Scrolling)
│                         │
│                         │
│   ┌──┐  ┌──┐  ┌──┐     │  y=176 (Controls)
│   │<<│  │> │  │>>│     │  45x45 each
│   └──┘  └──┘  └──┘     │
│                         │
└─────────────────────────┘
```

### Widget Specifications

#### Album Art Section
| Widget | Position | Size | Style |
|--------|----------|------|-------|
| Album Image | (70, 30) | 100x100 | Rounded (r=10)<br>Border: 2px #666666 |
| Progress Arc | (60, 20) | 120x120 | 4px width<br>Track: #2A2A2A<br>Indicator: #1DB954 (Spotify green) |

**Arc Details**:
- Range: 0-360 degrees
- No knob (display only)
- Smooth animation
- Surrounds album art

#### Text Information
| Widget | Position | Size | Font | Color | Behavior |
|--------|----------|------|------|-------|----------|
| Title | (0, 140) | 240x auto | montserrat_14 | White | Scroll circular |
| Artist | (0, 158) | 240x auto | montserrat_12 | Gray #AAA | Scroll circular |

#### Control Buttons
| Button | Position | Size | Symbol | Font | Color |
|--------|----------|------|--------|------|-------|
| Previous | (52, 176) | 45x45 | "<<" | montserrat_18 | BG: #333333 |
| Play/Pause | (98, 176) | 45x45 | ">" | montserrat_20 | BG: #4A4A4A |
| Next | (143, 176) | 45x45 | ">>" | montserrat_18 | BG: #333333 |

**Button Styling**:
- Circular (radius = 23px for 45x45 buttons)
- Border: 2px white
- Center-aligned labels
- Slightly larger center button

### Color Palette
- **Background**: #000000 (Black)
- **Primary**: #1DB954 (Spotify Green)
- **Button Default**: #333333 (Dark Gray)
- **Button Active**: #4A4A4A (Medium Gray)
- **Border**: #666666 (Light Gray)
- **Text Primary**: #FFFFFF (White)
- **Text Secondary**: #AAAAAA (Light Gray)

---

## Screen 3: Weather Screen

### Layout Diagram
```
┌─────────────────────────┐ 240x240
│                         │
│       Weather           │  y=30  (Title)
│                         │
│    Partly Cloudy        │  y=60  (Condition)
│                         │
│                         │
│         20°             │  y=95  (Temperature)
│                         │  48pt font
│                         │
│                         │
│   ┌─────────────────┐   │  y=165 (Info card)
│   │    Humidity     │   │
│   │      65%        │   │
│   └─────────────────┘   │
└─────────────────────────┘
```

### Widget Specifications

#### Header Section
| Widget | Position | Size | Font | Color |
|--------|----------|------|------|-------|
| Title | (0, 30) | 240x auto | montserrat_18 | Gray #AAA |
| Condition | (0, 60) | 240x auto | montserrat_16 | Sky Blue #87CEEB |

#### Temperature Display
| Widget | Position | Size | Font | Color | Style |
|--------|----------|------|------|-------|-------|
| Temperature | (0, 95) | 240x auto | montserrat_48 | White | Center-aligned<br>Extra large |

#### Humidity Card
| Component | Position | Size | Font | Color | Style |
|-----------|----------|------|------|-------|-------|
| Container | (30, 165) | 180x50 | - | BG: #1A1A1A | Rounded (r=15)<br>Border: 1px #333333<br>Padding: 8px |
| Label | (0, 2) | 164x auto | montserrat_12 | Gray #888 | "Humidity" |
| Value | (0, 18) | 164x auto | montserrat_20 | Sky Blue #87CEEB | "65%" |

### Color Palette
- **Background**: #000000 (Black)
- **Primary**: #87CEEB (Sky Blue)
- **Surface**: #1A1A1A (Very Dark Gray)
- **Border**: #333333 (Dark Gray)
- **Text Primary**: #FFFFFF (White)
- **Text Secondary**: #888888 (Medium Gray)
- **Text Tertiary**: #AAAAAA (Light Gray)

---

## Typography System

### Font Hierarchy

| Usage | Font | Size | Weight | Purpose |
|-------|------|------|--------|---------|
| Hero | montserrat_48 | 48pt | Regular | Temperature, key numbers |
| H1 | montserrat_22 | 22pt | Regular | Screen titles (weather base) |
| H2 | montserrat_20 | 20pt | Regular | Button text, important values |
| H3 | montserrat_18 | 18pt | Regular | Subtitles, section headers |
| Body | montserrat_16 | 16pt | Regular | Standard text |
| Body Small | montserrat_14 | 14pt | Regular | Labels, status text |
| Caption | montserrat_12 | 12pt | Regular | Secondary info, hints |

### Text Colors

| Purpose | Color | Hex | Usage |
|---------|-------|-----|-------|
| Primary | White | #FFFFFF | Main text, important info |
| Secondary | Light Gray | #AAAAAA | Supporting text |
| Tertiary | Medium Gray | #888888 | Hints, disabled text |
| Accent | Sky Blue | #87CEEB | Weather info, highlights |
| Success | Green | #34C759 | Active states |
| Warning | Orange | #FFB800 | Brightness, attention |

---

## Design Principles

### 1. Gesture-First Navigation
- No visible navigation buttons
- Swipe gestures for screen changes
- Visual feedback through animations
- Intuitive left/right flow

### 2. Circular Display Optimization
- Elements centered and sized for circular viewing
- Important content in central 180px circle
- Status bar fits within top safe area
- Bottom elements above circular cutoff

### 3. Modern Styling
- **Rounded Corners**: All interactive elements
- **Shadows**: Depth and hierarchy
- **Borders**: Visual separation and polish
- **Animations**: Smooth transitions (250ms)

### 4. Professional Color Palette
- Dark background for OLED efficiency
- High contrast for readability
- Accent colors for visual interest
- Consistent across all screens

### 5. Touch Optimization
- Minimum 40px touch targets
- Circular buttons for better ergonomics
- Adequate spacing between elements
- Visual feedback on interaction

---

## Layout Best Practices

### Spacing Guidelines
- **Top margin**: 30px minimum
- **Side margins**: 20-30px for content
- **Bottom margin**: 20px minimum
- **Element spacing**: 10-20px between sections
- **Button spacing**: 5-7px between buttons

### Safe Zones for Circular Display
```
┌─────────────────────────┐
│   ╱───────────────╲     │  Top safe: y > 20
│  │                 │    │  
│  │  Content Area   │    │  Center safe: 30 < x,y < 210
│  │   (Safe Zone)   │    │  
│   ╲───────────────╱     │  Bottom safe: y < 220
└─────────────────────────┘
```

### Animation Specifications
- **Screen transitions**: 250ms slide
- **Button press**: 100ms scale
- **Slider drag**: Real-time (0ms)
- **Toggle switch**: 200ms smooth
- **Text scroll**: 1000ms per cycle

---

## Responsive Behavior

### Dynamic Content
- **Long text**: Circular scrolling
- **Missing data**: Placeholder text
- **State changes**: Smooth updates
- **Touch feedback**: Visual indication

### State Management
- **Light off**: Gray tones
- **Light on**: Warm colors
- **Playing**: Different icon
- **Paused**: Different icon
- **No data**: Dim/placeholder

---

## Accessibility Considerations

### Visual
- High contrast ratios (4.5:1 minimum)
- Large text for primary information
- Clear visual hierarchy
- Color not sole indicator

### Touch
- Large touch targets (minimum 40px)
- Adequate spacing (7px minimum)
- Gesture deadzone for accidental touches
- Smooth, predictable animations

### Feedback
- Visual state changes
- Animation feedback
- Clear active states
- Consistent behavior

---

## Implementation Notes

### LVGL Configuration Required
```c
#define LV_USE_ANIMATION 1
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_22 1
#define LV_FONT_MONTSERRAT_48 1
```

### Gesture Configuration
```c
#define LV_INDEV_DEF_GESTURE_LIMIT 50
#define LV_INDEV_DEF_GESTURE_MIN_VELOCITY 3
```

### Memory Considerations
- Pre-create all screens
- Reuse screen objects
- Efficient screen switching
- No memory leaks on navigation

---

## Future Enhancement Ideas

1. **Vertical Swipes**: Quick actions or settings
2. **Long Press**: Context menus
3. **Multi-finger Gestures**: Advanced controls
4. **Dynamic Themes**: Day/night modes
5. **More Screens**: Calendar, notifications, settings
6. **Animated Icons**: Weather, media states
7. **Live Data**: Real-time updates
8. **Custom Widgets**: Specialized displays

---

**Document Version**: 1.0
**Last Updated**: 2025-10-10
**Status**: Complete
