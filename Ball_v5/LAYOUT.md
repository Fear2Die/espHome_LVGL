# Ball V5 Screen Layout

## Display Specifications

- **Resolution**: 240x240 pixels
- **Shape**: Circular display
- **Model**: GC9A01A
- **Color Depth**: 16-bit (RGB565)
- **Touch**: CST816 capacitive touch

## Page Overview

Ball V5 has 3 main pages plus voice assistant status pages:

1. **Idle Page** (Main) - Light controls and navigation
2. **Media Page** - Media player controls
3. **Weather Page** - Weather information
4. Voice Assistant Pages (Listening, Thinking, Replying, etc.)

---

## Idle Page Layout (Main Page)

```
┌─────────────────────────┐
│ 12:45  Ready      85%   │  y=5 (Time, Status, Battery)
│                         │
│   ████████████          │  y=60 (Brightness Slider)
│                         │
│        50%              │  y=90 (Brightness Label)
│                         │
│   ┌───────────────┐    │  y=120 (Toggle Button)
│   │ Toggle Light  │    │
│   └───────────────┘    │  y=155
│                         │
│                         │
│ [Media]    [Weather]   │  y=230 (Navigation Buttons)
└─────────────────────────┘  y=240
```

### Widget Positions

#### Top Row (y=5)
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------|
| Time Label | x=10, y=5 | TOP_LEFT | auto | "12:45" |
| Status Label | x=0, y=5 | TOP_MID | auto | "Ready" (green) |
| Battery Label | x=-10, y=5 | TOP_RIGHT | auto | "85%" |

#### Middle Section
| Widget | Position | Alignment | Size | Purpose |
|--------|----------|-----------|------|---------|
| Brightness Slider | x=0, y=60 | TOP_MID | 200x20 | 0-100% control |
| Brightness Label | x=0, y=90 | TOP_MID | auto | "50%" display |
| Toggle Button | x=0, y=120 | TOP_MID | 140x35 | On/Off control |

#### Bottom Section (Navigation)
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------|
| Media Button | x=-65, y=-10 | BOTTOM_MID | 90x35 | "Media" |
| Weather Button | x=65, y=-10 | BOTTOM_MID | 90x35 | "Weather" |

### Color States

**Light Off:**
- Slider background: Gray (#555555)
- Button background: Gray (#555555)

**Light On:**
- Slider background: Warm yellow (#FFCC66)
- Button background: Warm yellow (#FFCC66)

### Vertical Spacing

```
y=0   ┌─────────────────────────┐
      │                         │
y=5   │  Time  Ready  Battery   │ (Top labels)
      │                         │
      ├─────────────────────────┤ (55px gap)
y=60  │   ████████████          │ (Slider)
      │                         │
y=80  ├─────────────────────────┤
      │                         │
y=90  │        50%              │ (Label)
      │                         │
y=110 ├─────────────────────────┤ (30px gap)
      │                         │
y=120 │  ┌───────────────┐     │ (Button start)
      │  │ Toggle Light  │     │
y=155 │  └───────────────┘     │ (Button end)
      │                         │
      │                         │ (75px gap)
y=230 │ [Media]  [Weather]     │ (Nav buttons)
y=240 └─────────────────────────┘
```

---

## Media Player Page Layout

```
┌─────────────────────────┐
│ [Back]                  │  y=5 (Back button)
│                         │
│  Song Title Here        │  y=40 (Title)
│  Artist Name            │  y=65 (Artist)
│  ▶ Playing              │  y=90 (State)
│                         │
│                         │
│   [⏮]  [⏯]  [⏭]       │  y=130 (Control buttons)
│                         │
│                         │
│      Volume             │  y=195 (Label)
│   ═══════════════       │  y=215 (Volume slider)
└─────────────────────────┘
```

### Widget Positions

#### Top Section
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------|
| Back Button | x=10, y=5 | TOP_LEFT | 60x30 | "Back" |
| Title Label | x=0, y=40 | TOP_MID | 220 width | Song title |
| Artist Label | x=0, y=65 | TOP_MID | 220 width | Artist name |
| State Label | x=0, y=90 | TOP_MID | auto | "▶ Playing" |

#### Control Section
| Widget | Position | Alignment | Size | Symbol |
|--------|----------|-----------|------|--------|
| Previous Button | x=-80, y=130 | TOP_MID | 50x50 | "⏮" |
| Play/Pause Button | x=0, y=130 | TOP_MID | 50x50 | "⏯" |
| Next Button | x=80, y=130 | TOP_MID | 50x50 | "⏭" |

#### Volume Section
| Widget | Position | Alignment | Size | Purpose |
|--------|----------|-----------|------|---------|
| Volume Label | x=0, y=195 | TOP_MID | auto | "Volume" |
| Volume Slider | x=0, y=215 | TOP_MID | 200x15 | 0-100% |

### Colors
- Background: Dark blue-gray (#1a1a2e)
- Buttons: Medium gray (#444455)
- Borders: Light gray (#666677)
- Text: White
- Accent: Yellow (#FFCC66)

### Button Layout
```
   ┌────┐    ┌────┐    ┌────┐
   │ ⏮  │    │ ⏯  │    │ ⏭  │
   └────┘    └────┘    └────┘
   x=-80     x=0        x=80
```

---

## Weather Page Layout

```
┌─────────────────────────┐
│ [Back]    Weather       │  y=5-10 (Title)
│                         │
│       Sunny             │  y=50 (Condition)
│                         │
│                         │
│       24.5°C            │  CENTER (Temperature)
│                         │
│                         │
│      Humidity:          │  y=150 (Label)
│        65%              │  y=175 (Value)
└─────────────────────────┘
```

### Widget Positions

#### Top Section
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------|
| Back Button | x=10, y=5 | TOP_LEFT | 60x30 | "Back" |
| Title Label | x=0, y=10 | TOP_MID | auto | "Weather" |

#### Middle Section
| Widget | Position | Alignment | Size | Purpose |
|--------|----------|-----------|------|---------|
| Condition Label | x=0, y=50 | TOP_MID | 200 width | Weather state |
| Temperature Label | x=0, y=-10 | CENTER | auto | Large temp display |

#### Bottom Section
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------|
| Humidity Label | x=0, y=150 | TOP_MID | auto | "Humidity:" |
| Humidity Value | x=0, y=175 | TOP_MID | auto | "65%" |

### Colors
- Background: Deep blue (#162447)
- Buttons: Blue-gray (#1f4068)
- Borders: Light blue-gray (#4a5a7a)
- Temperature: White (large)
- Condition: Yellow accent (#FFCC66)

### Vertical Layout
```
y=0-10:   Back button and title
y=50:     Weather condition
y=120:    Temperature (centered)
y=150:    Humidity label
y=175:    Humidity value
y=240:    Bottom
```

---

## Voice Assistant Pages

### Listening Page
```
┌─────────────────────────┐
│                         │
│                         │
│                         │
│     Listening...        │  CENTER
│                         │
│                         │
│                         │
└─────────────────────────┘
```
- Background: Blue (#0000FF)
- Text: White, centered

### Thinking Page
```
┌─────────────────────────┐
│                         │
│                         │
│                         │
│     Thinking...         │  CENTER
│                         │
│   "Turn on lights"      │  BOTTOM (request)
│                         │
└─────────────────────────┘
```
- Background: Orange (#FF8800)
- Request text at bottom (y=-20)

### Replying Page
```
┌─────────────────────────┐
│                         │
│                         │
│                         │
│     Replying...         │  CENTER
│                         │
│   "Okay, turning on"    │  BOTTOM (response)
│                         │
└─────────────────────────┘
```
- Background: Green (#00AA00)
- Response text at bottom (y=-20)

---

## Comparison: V4 vs V5

### Ball V4 Layout
```
┌─────────────────────────┐
│   Ready          85%    │  y=5
│                         │
│   ████████████          │  y=60
│                         │
│        50%              │  y=90
│                         │
│   ┌───────────────┐    │  y=130
│   │ Toggle Light  │    │
│   └───────────────┘    │  y=175
│                         │
└─────────────────────────┘
```
- Single page
- No time display initially
- Larger toggle button (45px height)
- No navigation

### Ball V5 Layout
```
┌─────────────────────────┐
│ 12:45  Ready      85%   │  y=5 ✅ Added time
│                         │
│   ████████████          │  y=60
│                         │
│        50%              │  y=90
│                         │
│   ┌───────────────┐    │  y=120 ✅ Moved up
│   │ Toggle Light  │    │
│   └───────────────┘    │  y=155 ✅ Reduced height
│                         │
│ [Media]    [Weather]   │  y=230 ✅ New buttons
└─────────────────────────┘
```
- Multi-page interface
- Time display
- Smaller toggle button (35px height)
- Navigation buttons

---

## Layout Optimization

### Space Utilization

**Ball V4:**
- Top section: 175px
- Unused bottom: 65px
- Efficiency: 73%

**Ball V5:**
- Top section: 155px
- Navigation: 35px
- Gap: 50px
- Efficiency: 79%

### Touch Zones

**Main Page:**
```
┌─────────────────────────┐
│ ① Time  ② Status  ③ Bat │  Info zone (no touch)
│                         │
│   ④ Brightness Slider   │  Active touch zone
│                         │
│        ⑤ Label          │  Info zone (no touch)
│                         │
│   ⑥ Toggle Button       │  Active touch zone
│                         │
│                         │
│ ⑦ Media    ⑧ Weather   │  Active touch zones
└─────────────────────────┘
```

**Touch Targets:**
- Slider: 200x20 (easy to grab)
- Toggle: 140x35 (comfortable tap)
- Navigation: 90x35 each (adequate size)
- Back buttons: 60x30 (sufficient)

### Font Sizes

| Element | Font | Size | Usage |
|---------|------|------|-------|
| Status | montserrat_20 | 20pt | Main status |
| Time | montserrat_16 | 16pt | Time display |
| Battery | montserrat_16 | 16pt | Battery % |
| Brightness | montserrat_16 | 16pt | Percentage |
| Buttons | montserrat_16 | 16pt | Button text |
| Temperature | montserrat_32 | 32pt | Large display |
| Symbols | montserrat_20 | 20pt | Media controls |

---

## Design Principles

### Circular Display Optimization
- Center-aligned main content
- Important info within inner circle
- Corners used for back buttons
- Navigation at natural thumb reach

### Color Psychology
- **Gray (#555555)**: Inactive/off state
- **Warm Yellow (#FFCC66)**: Active/on state
- **Blue shades**: Information pages
- **Green**: Positive/ready states
- **Orange**: Processing states
- **Red**: Alerts/errors

### Touch Ergonomics
- Large touch targets (minimum 35px)
- Bottom buttons for easy thumb reach
- Centered sliders for two-hand use
- Back buttons in top-left (standard position)

### Visual Hierarchy
1. **Primary**: Large center elements (temperature, status)
2. **Secondary**: Control buttons (toggle, media controls)
3. **Tertiary**: Labels and metadata
4. **Quaternary**: Navigation and back buttons

---

## Accessibility

### Text Contrast
- All text meets WCAG AA standards
- White text on dark backgrounds
- High contrast for readability

### Touch Targets
- All interactive elements ≥35px
- Adequate spacing between buttons
- No overlapping touch zones

### Visual Feedback
- Color changes on state transitions
- Clear active/inactive states
- Consistent button highlighting

---

## Responsive Behavior

### State Updates
- **Instant**: Local actions (button press)
- **Fast (<500ms)**: HA actions (light toggle)
- **Normal (1-2s)**: Sensor updates (media title)
- **Slow (15-30min)**: Weather updates

### Page Transitions
- **Immediate**: Page switching (<100ms)
- **Smooth**: No flicker or flash
- **Consistent**: Same transition style

### Touch Response
- **Instant**: Visual feedback on touch
- **Debounced**: No accidental double-taps
- **Reliable**: Every touch registers

---

This layout design ensures optimal usability on the 240x240 circular display while providing access to all Ball V5 features!
