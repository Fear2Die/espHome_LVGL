# Ball V5.4 Screen Layout - Circular Display Optimized

## Display Specifications

- **Resolution**: 240x240 pixels
- **Shape**: Circular display (GC9A01A)
- **Color Depth**: 16-bit (RGB565)
- **Touch**: CST816 capacitive touch
- **Circular Display Radius**: 120 pixels (from center at 120,120)

## Circular Display Considerations

### Safe Zone Calculation

For a 240x240 circular display:
- **Center point**: (120, 120)
- **Maximum radius**: 120 pixels
- **Recommended safe zone**: ~100-110 pixels from center for full element visibility
- **Corner positions** (e.g., x=10, y=10) are ~156 pixels from center - **outside safe zone!**

### Distance from Center Formula
```
distance = √((x - 120)² + (y - 120)²)
```

Examples:
- Top-left corner (0, 0): 170 pixels from center ❌ Cut off
- Position (10, 10): 156 pixels from center ❌ Cut off
- Position (25, 35): 125 pixels from center ⚠️ Edge area
- Center (120, 120): 0 pixels from center ✅ Perfect
- Position (120, 60): 60 pixels from center ✅ Safe zone

## Page Overview

Ball V5.4 has 3 main pages plus voice assistant status pages:

1. **Idle Page** (Main) - Light controls and navigation
2. **Media Page** - Media player controls with live album art
3. **Weather Page** - Weather information
4. Voice Assistant Pages (Listening, Thinking, Replying, etc.)

---

## Idle Page Layout (Main Page)

### Visual Layout
```
        ┌─────────────────┐
       ╱                   ╲
      │      Ready          │  y=8 (Status - centered)
     │                       │
     │ Time           Battery │  y=35 (Info row - moved inward)
    │                         │
    │    ══════════════       │  y=68 (Slider - narrower)
    │         50%             │  y=100 (Brightness %)
   │                           │
   │   ┌───────────────┐      │  y=130 (Toggle button)
   │   │ Toggle Light  │      │
   │   └───────────────┘      │
  │                            │
  │                             │
   │   [Media] [Weather]       │  y=-25 (Nav buttons - higher up)
    │                          │
     │                        │
      ╲                      ╱
       └────────────────────┘
```

### Widget Positions (Optimized for Circular Display)

#### Top Section
| Widget | Position | Distance from Center | Status | Change from V5.3 |
|--------|----------|---------------------|---------|------------------|
| Status Label | (0, 8) TOP_MID | 112px | ✅ Safe | Moved down 3px |
| Time Label | (25, 35) TOP_LEFT | 97px | ✅ Safe | Moved right 15px, down 30px |
| Battery Label | (-25, 35) TOP_RIGHT | 97px | ✅ Safe | Moved left 15px, down 30px |

**Key Changes**: 
- Time and battery moved significantly inward (from x=±10 to x=±25)
- Moved down from y=5 to y=35 for better circular fit
- Status label moved down slightly for better spacing

#### Middle Section
| Widget | Position | Size | Distance from Center | Status | Change from V5.3 |
|--------|----------|------|---------------------|---------|------------------|
| Light Slider | (0, 68) TOP_MID | 180x20 | ~80px edges | ✅ Safe | Width: 200→180, y: 60→68 |
| Brightness Label | (0, 100) TOP_MID | auto | 20px | ✅ Safe | y: 90→100 |
| Toggle Button | (0, 112) TOP_MID | 140x33 | ~68px edges | ✅ Safe | y: 120→112, height: 35→33 (v5.4.1 fix) |

**Key Changes**:
- Slider narrowed from 200px to 180px to fit better in circular area
- Vertical spacing adjusted for better balance
- **v5.4.1 fix**: Toggle button moved up and made slightly shorter to prevent overlap

#### Bottom Section (Navigation)
| Widget | Position | Size | Distance from Center | Status | Change from V5.3 |
|--------|----------|------|---------------------|---------|------------------|
| Media Button | (-50, -61) BOTTOM_MID | 85x33 | ~92px | ✅ Safe | Width: 90→85, y: -10→-61 (v5.4.1 fix) |
| Weather Button | (50, -61) BOTTOM_MID | 85x33 | ~92px | ✅ Safe | Width: 90→85, y: -10→-61 (v5.4.1 fix) |

**Key Changes**:
- Moved up significantly from y=-10 to avoid circular edge and overlap
- Slightly narrower (90px → 85px) for better circular fit
- **v5.4.1 fix**: Height reduced to 33px and moved to y=-61 to prevent overlap with toggle button (1px gap)

### Colors
- Background: Dark gray (#111111)
- Light off slider: Gray (#555555)
- Light on slider: Warm yellow (#FFCC66)
- Buttons: Medium gray (#444444)
- Text: White/Green/Gray
- Time/Battery: Light gray (#CCCCCC)

---

## Media Player Page Layout

### Visual Layout
```
        ┌─────────────────┐
       ╱                   ╲
      │     < Back          │  y=8 (Back - centered)
     │                       │
     │      ┌───────┐        │  y=50 (Album art)
    │       │ IMAGE │        │
    │       └───────┘        │
   │                          │
   │   Song Title Here        │  y=118 (Title - narrower)
   │   Artist Name            │  y=140 (Artist)
   │   > Playing              │  y=162 (State)
  │                            │
  │  [<<]  [>]  [>>]           │  Center (Controls - tighter)
  │                            │
   │   ══════════════          │  y=-30 (Volume - higher, narrower)
    │                          │
     │                        │
      ╲                      ╱
       └────────────────────┘
```

### Widget Positions (Optimized for Circular Display)

#### Top Section
| Widget | Position | Size | Distance from Center | Status | Change from V5.3 |
|--------|----------|------|---------------------|---------|------------------|
| Back Button | (0, 8) TOP_MID | 70x32 | 112px | ✅ Safe | Centered, was at (10,5) TOP_LEFT |
| Album Art | (0, 45) TOP_MID | 60x60 | 67px | ✅ Safe | y: 40→45 (v5.4.1 fix) |
| Title Label | (0, 112) TOP_MID | 200 width | varies | ✅ Safe | Width: 220→200, y: 110→112, font: 14 (v5.4.1 fix) |
| Artist Label | (0, 128) TOP_MID | 200 width | varies | ✅ Safe | Width: 220→200, y: 135→128, font: 14 (v5.4.1 fix) |
| State Label | (0, 144) TOP_MID | auto | varies | ✅ Safe | y: 160→144, font: 14 (v5.4.1 fix) |

**Key Changes**:
- Back button now centered at top instead of corner (much better for circular!)
- Text width reduced from 220 to 200 pixels for circular safety
- **v5.4.1 fix**: All elements repositioned to prevent overlaps, fonts changed to montserrat_14 for tighter layout

#### Control Section
| Widget | Position | Size | Distance from Center | Status | Change from V5.3 |
|--------|----------|------|---------------------|---------|------------------|
| Previous Button | (-60, 162) TOP_MID | 44x40 | varies | ✅ Safe | x: -70→-60, size: 48→44x40, y: 0→162 (v5.4.1 fix) |
| Play/Pause Button | (0, 162) TOP_MID | 44x40 | varies | ✅ Safe | size: 48→44x40, y: 0→162 (v5.4.1 fix) |
| Next Button | (60, 162) TOP_MID | 44x40 | varies | ✅ Safe | x: 70→60, size: 48→44x40, y: 0→162 (v5.4.1 fix) |

**Key Changes**:
- **v5.4.1 fix**: Changed from CENTER alignment to TOP_MID at y=162 to prevent overlap
- Buttons brought closer together (±70 → ±60) for better circular fit
- Size reduced to 44x40 pixels for tighter spacing
- Now positioned below state label instead of overlapping with it

#### Volume Section
| Widget | Position | Size | Distance from Center | Status | Change from V5.3 |
|--------|----------|------|---------------------|---------|------------------|
| Volume Slider | (0, -22) BOTTOM_MID | 170x16 | ~84px edges | ✅ Safe | Width: 200→170, y: -30→-22, height: 18→16 (v5.4.1 fix) |

**Key Changes**:
- Volume label removed (saves space on circular display)
- Slider narrowed from 200 to 170 pixels
- **v5.4.1 fix**: Moved up to y=-22 and reduced height to 16px to prevent overlap with controls
- Positioned using BOTTOM_MID instead of TOP_MID

### Colors
- Background: Dark blue-gray (#1a1a2e)
- Buttons: Medium gray (#444455)
- Borders: Light gray (#666677)
- Album art bg: Medium gray (#333344)
- Text: White
- Accent: Yellow (#FFCC66)

---

## Weather Page Layout

### Visual Layout
```
        ┌─────────────────┐
       ╱                   ╲
      │     < Back          │  y=8 (Back - centered)
     │                       │
     │   Partly Cloudy       │  y=55 (Condition)
    │                         │
   │                           │
   │        22°C               │  y=-15 (Temp - centered)
  │                            │
  │                             │
   │      Humidity:            │  y=-65 (Label)
    │        65%               │  y=-38 (Value)
     │                        │
      ╲                      ╱
       └────────────────────┘
```

### Widget Positions (Optimized for Circular Display)

| Widget | Position | Size | Distance from Center | Status | Change from V5.3 |
|--------|----------|------|---------------------|---------|------------------|
| Back Button | (0, 8) TOP_MID | 70x32 | 112px | ✅ Safe | Centered, was at (10,5) TOP_LEFT |
| Condition Label | (0, 55) TOP_MID | 190 width | varies | ✅ Safe | Width: 200→190, y: 50→55 |
| Temperature | (0, -15) CENTER | auto | 15px | ✅ Safe | y: -10→-15 for better centering |
| Humidity Label | (0, -65) BOTTOM_MID | auto | 55px | ✅ Safe | y: 150→-65 (using BOTTOM_MID) |
| Humidity Value | (0, -38) BOTTOM_MID | auto | 82px | ✅ Safe | y: 175→-38 (using BOTTOM_MID) |

**Key Changes**:
- Back button centered at top (consistent with media page)
- Condition text slightly narrower (200 → 190)
- Humidity info moved to bottom using BOTTOM_MID alignment for better circular fit
- Better vertical balance around center

### Colors
- Background: Dark blue (#162447)
- Buttons: Medium blue (#1f4068)
- Borders: Light blue (#4a5a7a)
- Text: White
- Accent: Yellow (#FFCC66)
- Secondary text: Light gray (#CCCCCC)

---

## Voice Assistant Pages Layout

All voice assistant pages are centered and optimized for circular display:

### Listening Page
- Full screen blue background (#0000FF)
- "Listening..." text centered
- No edge elements

### Thinking Page
- Orange background (#FF8800)
- "Thinking..." centered
- Request text at (0, -30) BOTTOM_MID, width: 180 (narrowed from 200)

### Replying Page
- Green background (#00AA00)
- "Replying..." centered
- Response text at (0, -30) BOTTOM_MID, width: 180 (narrowed from 200)

### Other Status Pages
- Error, Timer Finished, Muted, etc.
- All use centered text
- No edge elements
- Optimized for circular display

**Key Changes**:
- Bottom text moved up (y: -20 → -30) to avoid circular edge
- Text width narrowed (200 → 180) for circular safety

---

## Design Principles for Circular Display

### 1. Centering Priority
- Primary content always centered
- Navigation and controls arranged symmetrically around center
- Avoid corner positioning

### 2. Safe Zone Compliance
- All interactive elements within 100-110px radius from center
- Text content within 90-100px radius for full readability
- Critical information never at screen edges

### 3. Symmetry
- Horizontal symmetry for all major layouts
- Balanced vertical spacing
- Equal margins on all sides

### 4. Touch Target Optimization
- Buttons positioned in easy-to-reach areas
- Minimum 32px touch target size
- Adequate spacing between interactive elements

### 5. Visual Hierarchy
- Larger elements toward center
- Smaller elements toward edges (within safe zone)
- Clear visual flow from top to center to bottom

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
- **Optimized zones**: All touch targets in circular safe zone

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
- **Circular safe zone awareness**: All touch targets positioned for circular display

### Performance
- 60 FPS target
- Updates on state change only
- Flag-based protection against feedback loops
- Minimal redraws
- Optimized for circular display rendering

---

## Circular Display Benefits

### What's Better in V5.4?

1. **No More Edge Cutoff**: All elements safely within circular boundaries
2. **Better Touch Accuracy**: Buttons positioned in easy-to-reach circular areas
3. **Improved Readability**: Text positioned for optimal viewing on circular display
4. **Consistent Layout**: All pages follow circular design principles
5. **Professional Look**: Design embraces circular form factor instead of fighting it
6. **Better Balance**: Symmetric layouts work perfectly with circular shape
7. **Easier Navigation**: Centered back buttons more intuitive on circular display

### V5.3 vs V5.4 Comparison

| Aspect | V5.3 (Rectangular) | V5.4 (Circular) |
|--------|-------------------|-----------------|
| Corner elements | May be cut off | All within safe zone |
| Time/Battery | x=±10 (edge) | x=±25 (inward) |
| Back buttons | Corner position | Center top |
| Button spacing | Wider | Optimized |
| Text width | 220px | 180-200px |
| Layout philosophy | Rectangular grid | Circular radial |
| Touch accuracy | Edge issues | All accessible |
| Visual balance | Top-heavy | Centered |

---

## Future Enhancements

Possible improvements for future versions:
- Radial menu layouts
- Circular progress indicators
- Arc-based sliders
- Rotation-aware positioning
- Dynamic safe zone calculation
- Gesture support (rotate to navigate)
- Circular animations

---

**For implementation details, see Ball_v5.4.yaml**
**For changes from V5.3, see CHANGES_V5.4.md**
**For setup instructions, see README.md**
