# Ball V4 Screen Layout

## Display Specifications
- **Screen Size**: 240x240 pixels (round display)
- **Model**: GC9A01A
- **Touch**: CST816 capacitive touch

## Ready Page Layout (idle_page)

```
┌─────────────────────────────────────┐
│                                     │
│  12:45       Ready           85%    │  ← y=5
│  (time)     (status)      (battery) │
│                                     │
│                                     │  ← y=30 (spacing)
│         ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓          │  ← y=60
│         ███████░░░░░░░░░          │  ← Brightness Slider (200x20)
│         ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓          │  ← (0-100%)
│                                     │
│              50%                    │  ← y=90 (Brightness Label)
│                                     │
│                                     │  ← y=110 (spacing)
│       ┌─────────────────┐          │  ← y=130
│       │  Toggle Light   │          │  ← On/Off Button (140x45)
│       └─────────────────┘          │  ← y=175
│                                     │
│                                     │
│                                     │
│                                     │
└─────────────────────────────────────┘
```

## Widget Positions

### Top Row (y=5)
| Widget | Position | Alignment | Content |
|--------|----------|-----------|---------|
| Time Label | x=10, y=5 | TOP_LEFT | "12:45" |
| Status Label | x=0, y=5 | TOP_MID | "Ready" (green) |
| Battery Label | x=-10, y=5 | TOP_RIGHT | "85%" |

### Middle Section
| Widget | Position | Size | Content |
|--------|----------|------|---------|
| Brightness Slider | x=0, y=60 | 200x20 | 0-100% |
| Brightness Label | x=0, y=90 | auto | "50%" |

### Bottom Section
| Widget | Position | Size | Content |
|--------|----------|------|---------|
| Toggle Button | x=0, y=130 | 140x45 | "Toggle Light" |

## Layout Optimization

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
y=110 ├─────────────────────────┤ (40px gap)
      │                         │
y=130 │  ┌───────────────┐     │ (Button start)
      │  │ Toggle Light  │     │
y=175 │  └───────────────┘     │ (Button end)
      │                         │
y=240 └─────────────────────────┘
```

### Total Height Usage
- **Top labels**: y=5 to y=25 (20px)
- **Gap 1**: y=25 to y=60 (35px)
- **Slider**: y=60 to y=80 (20px)
- **Gap 2**: y=80 to y=90 (10px)
- **Label**: y=90 to y=105 (15px)
- **Gap 3**: y=105 to y=130 (25px)
- **Button**: y=130 to y=175 (45px)
- **Gap 4**: y=175 to y=240 (65px)

**Total**: 235px used (fits perfectly in 240px screen!)

## Comparison: V3 vs V4

### Ball V3 Layout Issues
```
┌─────────────────────────┐
│                         │
│   Ready          85%    │  y=5 ✓
│                         │
│                         │  
│   ████████████          │  y=70 ⚠️
│                         │
│   Brightness: 128       │  y=105 ⚠️
│                         │
│   ┌───────────────┐    │  y=150 ⚠️ TOO LOW!
│   │ Toggle Light  │    │
│   └───────────────┘    │  y=200
│                         │
│   ⋮ NEEDS SCROLLING ⋮  │  y=240 ❌
└─────────────────────────┘
```

### Ball V4 Layout Fixed
```
┌─────────────────────────┐
│                         │
│ 12:45  Ready      85%   │  y=5 ✓ (added time!)
│                         │
│   ████████████          │  y=60 ✓ (moved up)
│                         │
│        50%              │  y=90 ✓ (moved up)
│                         │
│   ┌───────────────┐    │  y=130 ✓ (moved up)
│   │ Toggle Light  │    │
│   └───────────────┘    │  y=175 ✓ (fits!)
│                         │
│                         │
└─────────────────────────┘
```

## Touch Zones

### Interactive Areas
```
┌─────────────────────────┐
│  [T]    [S]      [B]    │  T=Time, S=Status, B=Battery
│   ↑      ↑        ↑     │  (All display only)
│                         │
│    [━━━━SLIDER━━━━]    │  ← Draggable slider
│         ↕️              │
│      [LABEL]            │  ← Display only
│                         │
│    [━━BUTTON━━]        │  ← Tappable button
│         ↕️              │
└─────────────────────────┘
```

### Touch Behavior
- **Long press anywhere**: Toggle battery display
- **Slider area**: Drag to adjust brightness (instant update!)
- **Button area**: Tap to toggle light on/off
- **Elsewhere**: No action (voice assistant NOT activated)

## Color Scheme

### Ready Page (Idle)
- **Background**: Dark gray (#111111)
- **Status text**: Green (#00FF00)
- **Time text**: White (#FFFFFF)
- **Battery text**: White (#FFFFFF)
- **Slider track**: Default LVGL
- **Slider indicator**: Default LVGL
- **Brightness label**: Light gray (#CCCCCC)
- **Button background**: Gray (#555555)
- **Button border**: Light gray (#888888)
- **Button text**: White (#FFFFFF)

## Font Sizes

| Element | Font | Size |
|---------|------|------|
| Status Label | montserrat_20 | 20px |
| Time Label | montserrat_16 | 16px |
| Battery Label | montserrat_16 | 16px |
| Brightness Label | montserrat_16 | 16px |
| Button Text | montserrat_16 | 16px |

## Responsive Behavior

### When Battery Display is Hidden
```
┌─────────────────────────┐
│  12:45      Ready       │  ← Battery label empty
│                         │
│   ████████████          │
│        50%              │
│   ┌───────────────┐    │
│   │ Toggle Light  │    │
│   └───────────────┘    │
└─────────────────────────┘
```

### When Battery Display is Shown
```
┌─────────────────────────┐
│  12:45      Ready  85%  │  ← Battery label shown
│                         │
│   ████████████          │
│        50%              │
│   ┌───────────────┐    │
│   │ Toggle Light  │    │
│   └───────────────┘    │
└─────────────────────────┘
```

## Design Principles

### V4 Layout Goals
1. ✅ **Fit everything on one screen** (no scrolling)
2. ✅ **Logical top-to-bottom flow** (status → control → action)
3. ✅ **Clear visual hierarchy** (labels → slider → button)
4. ✅ **Touch-friendly spacing** (easy to tap/drag)
5. ✅ **Information density** (all important info visible)
6. ✅ **Clean aesthetics** (balanced, not crowded)

### Spacing Strategy
- **Top margin**: 5px (tight but readable)
- **Between sections**: 25-35px (comfortable separation)
- **Within controls**: 10px (compact but clear)
- **Bottom margin**: 65px (breathing room)

### Alignment Strategy
- **Horizontal**: Center-aligned for main controls
- **Top labels**: Left, center, right for full width usage
- **Slider**: Center-aligned (TOP_MID)
- **Button**: Center-aligned (TOP_MID)

## Accessibility

### Touch Targets
- **Slider**: 200x20px (easy to grab)
- **Button**: 140x45px (large enough for finger)
- **Long press**: 1+ second (prevents accidental triggers)

### Visual Clarity
- **High contrast**: White/green on dark backgrounds
- **Font sizes**: 16-20px (readable at arm's length)
- **Color coding**: Green=ready, Red=error, Blue=listening, etc.

### Feedback
- **Slider**: Immediate brightness change
- **Button**: Visual state change (checkable)
- **Labels**: Real-time updates

## Other Pages

All other pages (listening, thinking, replying, error, etc.) remain unchanged from Ball V3:
- Full-screen colored backgrounds
- Centered status text
- No controls needed

---

**Ball V4 Layout** - Optimized for 240x240 round display with perfect fit and no scrolling! 📐
