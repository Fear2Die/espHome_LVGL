# Ball V5.3 Screen Layout

## Display Specifications

- **Resolution**: 240x240 pixels
- **Shape**: Circular display
- **Model**: GC9A01A
- **Color Depth**: 16-bit (RGB565)
- **Touch**: CST816 capacitive touch

## Page Overview

Ball V5.3 has 3 main pages plus voice assistant status pages:

1. **Idle Page** (Main) - Light controls and navigation
2. **Media Page** - Media player controls with live album art
3. **Weather Page** - Weather information
4. Voice Assistant Pages (Listening, Thinking, Replying, etc.)

---

## Idle Page Layout (Main Page)

```
┌─────────────────────────┐
│ Time Ready    Battery   │  y=5 (Top row)
│        [⚡88%]          │
│                         │
│   ═══════════════       │  y=60 (Brightness slider)
│         50%             │  y=90 (Brightness %)
│                         │
│   ┌───────────────┐     │  y=120 (Toggle button)
│   │ Toggle Light  │     │
│   └───────────────┘     │
│                         │
│                         │
│                         │
│                         │
│    [Media] [Weather]    │  y=-10 (Navigation - 2 buttons) FIXED IN V5.3
└─────────────────────────┘
```

### Widget Positions

#### Top Row (y=5)
| Widget | Position | Alignment | Content |
|--------|----------|-----------|---------|
| Time Label | x=10, y=5 | TOP_LEFT | "HH:MM" |
| Idle Label | x=0, y=5 | TOP_MID | "Ready" |
| Battery Label | x=-10, y=5 | TOP_RIGHT | "⚡XX%" |

#### Middle Section
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------|
| Light Slider | x=0, y=60 | TOP_MID | 200x20 | 0-100% |
| Brightness Label | x=0, y=90 | TOP_MID | auto | "XX%" |
| Toggle Button | x=0, y=120 | TOP_MID | 140x35 | "Toggle Light" |

#### Bottom Section (Navigation - FIXED IN V5.3)
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------|
| Media Button | x=-50, y=-10 | BOTTOM_MID | 90x35 | "Media" |
| Weather Button | x=50, y=-10 | BOTTOM_MID | 90x35 | "Weather" |

**Change from V5.2**: Fixed overlap issue by moving buttons down (y=-10 instead of y=-45). Removed camera button for simplified navigation.

**Change from V5.1**: Restored 2-button layout with improved button sizing (90x35).

### Colors
- Background: Dark gray (#111111)
- Light off slider: Gray (#555555)
- Light on slider: Warm yellow (#FFCC66)
- Buttons: Medium gray (#444444)
- Text: White/Green/Gray

---

## Media Player Page Layout (NEW LAYOUT)

```
┌─────────────────────────┐
│ [Back]                  │  y=5 (Back button)
│                         │
│      ┌───────┐          │  y=40 (Album art 60x60)
│      │ IMAGE │          │  Live album art from entity_picture
│      └───────┘          │
│                         │
│  Song Title Here        │  y=110 (Title)
│  Artist Name            │  y=135 (Artist)
│  > Playing              │  y=160 (State)
│                         │
│   [<<]  [>]  [>>]       │  y=185 (Control buttons)
│                         │
│      Volume             │  y=195 (Label - hidden if no room)
│   ═══════════════       │  y=215 (Volume slider - bottom)
└─────────────────────────┘
```

### Widget Positions

#### Top Section
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------| 
| Back Button | x=10, y=5 | TOP_LEFT | 60x30 | "Back" |
| Album Art Image | x=0, y=40 | TOP_MID | 60x60 | Live album artwork |
| Title Label | x=0, y=110 | TOP_MID | 220 width | Song title |
| Artist Label | x=0, y=135 | TOP_MID | 220 width | Artist name |
| State Label | x=0, y=160 | TOP_MID | auto | "> Playing" / "|| Paused" / "[] Idle" |

**NEW in V5.3**: Live album art from entity_picture attribute, updates dynamically with media changes.

#### Control Section
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------| 
| Previous Button | x=-80, y=185 | TOP_MID | 50x50 | "<<" |
| Play/Pause Button | x=0, y=185 | TOP_MID | 50x50 | ">" or "||" |
| Next Button | x=80, y=185 | TOP_MID | 50x50 | ">>" |

**Changed in V5.2**: Buttons moved down (y=185 instead of y=130), glyphs replaced (⏮⏯⏭ → <<>|>>).

#### Volume Section
| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------| 
| Volume Label | x=0, y=195 | TOP_MID | auto | "Volume" |
| Volume Slider | x=0, y=215 | TOP_MID | 200x15 | 0-100% |

### Button Symbols (Fixed in V5.2)
```
   ┌────┐    ┌────┐    ┌────┐
   │ << │    │ >  │    │ >> │
   └────┘    └────┘    └────┘
   Previous  Play/Pause  Next
   
   Play button changes:
   > = Playing/Paused (press to play)
   || = Playing (press to pause)
```

### Colors
- Background: Dark blue-gray (#1a1a2e)
- Buttons: Medium gray (#444455)
- Borders: Light gray (#666677)
- Album art bg: Medium gray (#333344)
- Album art border: Light gray (#666677)
- Text: White
- Accent: Yellow (#FFCC66)

---

## Weather Page Layout

```
┌─────────────────────────┐
│ [Back]                  │  y=5 (Back button)
│                         │
│      Weather            │  y=10 (Title)
│                         │
│      Sunny              │  y=50 (Condition)
│                         │
│                         │
│       22.5°C            │  y=CENTER-10 (Temp)
│                         │
│                         │
│      Humidity:          │  y=150 (Label)
│        65%              │  y=175 (Value)
└─────────────────────────┘
```

### Widget Positions

| Widget | Position | Alignment | Size | Content |
|--------|----------|-----------|------|---------| 
| Back Button | x=10, y=5 | TOP_LEFT | 60x30 | "Back" |
| Title | x=0, y=10 | TOP_MID | auto | "Weather" |
| Condition | x=0, y=50 | TOP_MID | 200 width | Condition text |
| Temperature | x=0, y=CENTER-10 | CENTER | auto | "XX.X°C" |
| Humidity Label | x=0, y=150 | TOP_MID | auto | "Humidity:" |
| Humidity Value | x=0, y=175 | TOP_MID | auto | "XX%" |

### Colors
- Background: Deep blue (#162447)
- Buttons: Blue-gray (#1f4068)
- Borders: Light blue-gray (#4a5a7a)
- Temperature: Large white text (montserrat_32)
- Condition: Yellow accent (#FFCC66)
- Humidity: White text

---

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
- Text: White, large (montserrat_32)

### Thinking Page
```
┌─────────────────────────┐
│                         │
│                         │
│     Thinking...         │  CENTER
│                         │
│                         │
│  "Turn on the light"    │  y=-20 (Request text)
│                         │
└─────────────────────────┘
```
- Background: Orange (#FF8800)
- Text: White, large (montserrat_32)
- Request: White, small (montserrat_16)

### Replying Page
```
┌─────────────────────────┐
│                         │
│                         │
│     Replying...         │  CENTER
│                         │
│                         │
│  "Turning on the light" │  y=-20 (Response text)
│                         │
└─────────────────────────┘
```
- Background: Green (#00FF00)
- Text: White, large (montserrat_32)
- Response: White, small (montserrat_16)

---

## Comparison: V5.1 vs V5.2

### Main Page
**V5.1:**
- 2 navigation buttons (Media, Weather)
- Buttons at y=-10, 90x35 size

**V5.2:**
- 3 navigation buttons (Media, Weather, Camera)
- Buttons at y=-45, 70x30 size
- Smaller to fit 3 buttons

### Media Page
**V5.1:**
- No album art
- Title at y=40
- Buttons at y=130
- Unicode glyphs (⏮⏯⏭)

**V5.2:**
- Album art at y=40 (60x60)
- Title at y=110
- Buttons at y=185
- Text symbols (<<>||>>)

### Camera Page
**V5.1:** Doesn't exist

**V5.2:** New page added

---

## Layout Optimization

### Vertical Spacing Strategy

**Main Page:**
```
Top:     y=5   (Status bar)
         ↓ 55px gap
Middle:  y=60  (Slider)
         ↓ 30px gap
         y=90  (Label)
         ↓ 30px gap
         y=120 (Button)
         ↓ flexible gap
Bottom:  y=-45 (Navigation)
```

**Media Page:**
```
Top:     y=5   (Back)
         ↓ 35px gap
         y=40  (Album art)
         ↓ 70px gap
         y=110 (Title)
         ↓ 25px gap
         y=135 (Artist)
         ↓ 25px gap
         y=160 (State)
         ↓ 25px gap
         y=185 (Buttons)
         ↓ 30px gap
Bottom:  y=215 (Slider)
```

### Font Sizes

- **montserrat_32**: Large text (temperature, voice status)
- **montserrat_20**: Medium text (titles, idle label, symbols)
- **montserrat_16**: Small text (most UI elements, buttons)

**Removed in V5.2**: montserrat_14, montserrat_12 references (not available)

---

## Design Principles

### Consistency
- All pages have "Back" button at same position (x=10, y=5)
- All titles centered at TOP_MID
- All pages use consistent color scheme per category

### Accessibility
- Large touch targets (buttons 50x50 or larger)
- High contrast text (white on dark backgrounds)
- Clear visual hierarchy (size indicates importance)

### Responsive Behavior
- Sliders update in real-time
- Button states reflect actual device status
- Colors change based on state (light on/off)

---

## Navigation Flow

```
        Main (Idle) Page
            ↙      ↘
           ↙        ↘
       Media      Weather
          ↓          ↓
        Back        Back
          ↓          ↓
        Main (Idle) Page

Voice Assistant (from any page):
  Press Button → Listening → Thinking → Replying → Return
```

---

## Space Usage

### Main Page
- Used: ~165px (y=5 to y=155)
- Navigation: 30px (y=-45 to y=-15)
- Free space: ~45px (middle)

### Media Page
- Used: ~220px (y=5 to y=225)
- Very tight! Volume slider at bottom edge

### Weather Page
- Used: ~185px (y=5 to y=175)
- Free space: ~55px (bottom)

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

### Touch Areas
- Full screen touch enabled (240x240)
- Touch triggers on release (tap)
- No multi-touch support
- No gestures (swipe, pinch, etc.)

### Performance
- 60 FPS target
- Updates on state change only
- Flag-based protection against feedback loops
- Minimal redraws

---

## Future Layout Considerations

Possible for V5.3+:
- Swipe navigation (left/right between pages)
- Grid layout for multiple devices
- Scrollable content areas
- Dynamic page generation
- Tabs or menu system
- Status bar across all pages

---

**For implementation details, see Ball_v5.2.yaml**
**For setup instructions, see README.md**
