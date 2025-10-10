# Visual Changes in Ball V6.1

This document provides a quick visual reference of all UI changes made in version 6.1.

---

## Main Screen Changes

### Before (V6.0)
```
┌─────────────────────────┐
│   Light Control    [30] │ ← Title removed
│                         │
│ 10:15           100%    │
│                         │
│     Brightness          │
│  [=================>]   │ ← May cause swipe
│                         │
│    Light Control        │ ← Text changed
│      [  ○ ═══ ]         │
│                         │
└─────────────────────────┘
```

### After (V6.1)
```
┌─────────────────────────┐
│                         │ ← Title removed - cleaner!
│                         │
│ 10:15           100%    │
│                         │
│     Brightness          │
│  [=================>]   │ ← No swipe when dragging
│                         │
│    Light Switch         │ ← More accurate label
│      [  ○ ═══ ]         │
│                         │
└─────────────────────────┘
```

**Changes**:
- ✅ Removed "Light Control" title (saves 30px vertical space)
- ✅ Changed label from "Light Control" to "Light Switch"
- ✅ Slider now blocks swipe gestures during interaction

---

## Weather Screen Changes

### Before (V6.0)
```
┌─────────────────────────┐
│       Weather           │
│   Partly Cloudy         │
│                         │
│         20°             │ ← Hardcoded
│                         │
│                         │
│   ┌───────────────┐     │
│   │   Humidity    │     │
│   │      65%      │ ← Hardcoded [165]
│   └───────────────┘     │ ← Clips bottom!
└─────────────────────────┘
```

### After (V6.1)
```
┌─────────────────────────┐
│       Weather           │
│   Partly Cloudy         │
│                         │
│         --°             │ ← Placeholder
│                         │
│                         │
│   ┌───────────────┐     │ [155]
│   │   Humidity    │     │ ← Moved up 10px
│   │      --%      │ ← Placeholder
│   └───────────────┘     │ ← No clipping!
│                         │
└─────────────────────────┘
```

**Changes**:
- ✅ Temperature shows "--°" placeholder (was "20°")
- ✅ Humidity shows "--%" placeholder (was "65%")
- ✅ Humidity container moved from y:165 to y:155
- ✅ No bottom clipping - proper spacing
- ✅ Data updates from HA after connection

---

## Media Screen Changes

### Before (V6.0)
```
┌─────────────────────────┐
│                         │
│      ┌────────┐         │
│      │        │         │
│      │ Album  │         │
│      │  Art   │         │
│      └────────┘         │
│                         │
│    Song Title           │
│    Artist Name          │
│                         │
│  [<<]   [>]   [>>]      │
│                         │
│   (No volume control)   │
└─────────────────────────┘
```

### After (V6.1)
```
┌─────────────────────────┐
│                        ╱│ ← NEW!
│      ┌────────┐      ╱ │   Volume
│      │        │     │  │   Arc
│      │ Album  │     │  │
│      │  Art   │      ╲ │   (0-100)
│      └────────┘       ╲│
│                        │
│    Song Title           │
│    Artist Name          │
│                         │
│  [<<]   [>]   [>>]      │
│                         │
│                         │
└─────────────────────────┘
```

**Changes**:
- ✅ Added half-circle volume arc on right edge
- ✅ Arc spans full height (135° to 45°)
- ✅ Orange indicator matches brightness slider
- ✅ Touch and drag to adjust volume
- ✅ Arc blocks swipe during adjustment
- ✅ Album art remains centered and functional

---

## Side-by-Side Comparison

### Main Screen
| Aspect | V6.0 | V6.1 |
|--------|------|------|
| Title | "Light Control" at y:30 | Removed |
| Switch Label | "Light Control" | "Light Switch" |
| Slider Swipe | May trigger navigation | Blocked during use |
| Vertical Space | Less available | More available |

### Weather Screen
| Aspect | V6.0 | V6.1 |
|--------|------|------|
| Temperature Default | "20°" | "--°" |
| Humidity Default | "65%" | "--%" |
| Container Position | y:165 | y:155 |
| Bottom Clipping | Yes (slight) | No |
| Data Source | Static → HA | Placeholder → HA |

### Media Screen
| Aspect | V6.0 | V6.1 |
|--------|------|------|
| Volume Control | None | Half-circle arc |
| Volume Position | N/A | Right edge |
| Volume Style | N/A | Orange, 12px wide |
| Album Art | Centered | Centered (unchanged) |
| Swipe During Volume | N/A | Blocked |

---

## Color Reference

All colors maintained from V6.0, with additions for new volume arc:

| Element | Color | Hex | Usage |
|---------|-------|-----|-------|
| Background | Black | 0x000000 | All screens |
| Primary Text | White | 0xFFFFFF | Titles, values |
| Secondary Text | Light Gray | 0xAAAAAA | Labels, subtitles |
| Slider Track | Dark Gray | 0x2A2A2A | Brightness, volume |
| Slider Indicator | Orange | 0xFFB800 | Brightness, volume |
| Weather Accent | Sky Blue | 0x87CEEB | Condition, humidity |
| Switch On | Green | 0x34C759 | Light switch |
| Switch Off | Gray | 0x3A3A3A | Light switch |
| Progress Arc | Spotify Green | 0x1DB954 | Media progress |

---

## Typography

No changes to fonts in V6.1:

| Element | Font | Size | Weight |
|---------|------|------|--------|
| Removed Title | montserrat_18 | 18pt | Regular |
| Switch Label | montserrat_14 | 14pt | Regular |
| Temperature | montserrat_48 | 48pt | Regular |
| Humidity Value | montserrat_20 | 20pt | Regular |
| Song Title | montserrat_14 | 14pt | Regular |
| Artist Name | montserrat_12 | 12pt | Regular |

---

## Layout Measurements

### Main Screen
| Element | V6.0 Position | V6.1 Position | Change |
|---------|---------------|---------------|--------|
| Title | y: 30 | Removed | -30 |
| Time | x: 51, y: 48 | x: 51, y: 48 | None |
| Battery | x: 153, y: 48 | x: 153, y: 48 | None |
| Brightness Label | y: 90 | y: 90 | None |
| Brightness Slider | y: 115 | y: 115 | None |
| Switch Label | y: 155 | y: 155 | None |
| Light Switch | y: 175 | y: 175 | None |

### Weather Screen
| Element | V6.0 Position | V6.1 Position | Change |
|---------|---------------|---------------|--------|
| Weather Title | y: 30 | y: 30 | None |
| Condition | y: 60 | y: 60 | None |
| Temperature | y: 95 | y: 95 | None |
| Humidity Container | y: 165 | y: 155 | -10px |
| Container Height | 50 | 50 | None |
| Total Used Height | 215 | 205 | -10px |
| Bottom Margin | 25 | 35 | +10px |

### Media Screen
| Element | V6.0 Position | V6.1 Position | Change |
|---------|---------------|---------------|--------|
| Album Art | y: 30 | y: 30 | None |
| Progress Arc | y: 20 | y: 20 | None |
| Song Title | y: 140 | y: 140 | None |
| Artist Name | y: 158 | y: 158 | None |
| Control Buttons | y: 176 | y: 176 | None |
| Volume Arc | N/A | RIGHT_MID | NEW |

---

## Touch Interaction Changes

### Swipe Gesture Behavior

**V6.0**:
```
Touch → Drag → Release
         ↓
    Check direction
         ↓
   Change screen
```
Problem: Any drag (including on sliders) could trigger navigation

**V6.1**:
```
Touch → Drag → Release
         ↓
    Is slider?
    /        \\
  Yes        No
   ↓          ↓
Block    Check direction
swipe         ↓
         Change screen
```
Solution: Sliders set flag to block swipe detection

### Slider Interaction

**New Behavior** (V6.1):
1. User touches slider/arc
2. `slider_interaction = true` (flag set)
3. User drags to adjust value
4. Swipe detection ignores gesture
5. User releases
6. `slider_interaction = false` (flag cleared)
7. Swipe detection works normally again

**Applies to**:
- Brightness slider (main screen)
- Volume arc (media screen)

---

## Placeholder System

### Purpose
Show clear indication when data hasn't loaded from Home Assistant yet.

### Implementation
| Field | V6.0 Default | V6.1 Default | After HA Update |
|-------|-------------|-------------|-----------------|
| Temperature | "20°" | "--°" | "22°" (from HA) |
| Humidity | "65%" | "--%" | "45%" (from HA) |

### Visual States

**On Boot**:
```
Weather
Partly Cloudy

     --°

┌─────────────┐
│  Humidity   │
│    --%      │
└─────────────┘
```

**After HA Connection**:
```
Weather
Partly Cloudy

     22°

┌─────────────┐
│  Humidity   │
│    45%      │
└─────────────┘
```

---

## Volume Arc Details

### Geometry
```
      Right Edge
      
135° ←──╮
        │  Arc spans
        │  135° to 45°
        │  (180° total)
45°  ←──╯

Total: 180° semi-circle
Width: 80px (extends left from edge)
Height: 240px (full screen)
Arc Width: 12px
Knob: 8px radius, white
```

### Touch Zones
```
┌─────────────────────────┐
│ Swipe OK │   Volume     │
│          │   Control    │
│          │   (blocks    │
│          │   swipe)     │
│          │              │
│          │              │
│ Swipe OK │   80px wide  │
└─────────────────────────┘
```

---

## Animation & Feedback

No changes to animation timing in V6.1:

| Action | Duration | Type | Notes |
|--------|----------|------|-------|
| Screen Transition | 250ms | Slide | Left/Right |
| Slider Adjustment | Instant | None | Real-time |
| Volume Change | Instant | None | Real-time |
| Switch Toggle | ~200ms | Fade | iOS-style |
| Text Scroll | Variable | Scroll | Long text only |

---

## Accessibility Notes

### Improvements in V6.1

1. **Clearer Labels**:
   - "Light Switch" is more descriptive than "Light Control"
   
2. **Better Data Indication**:
   - Placeholders ("--°", "--%") clearly show when data is loading
   - Users know when data is real vs. loading

3. **Improved Touch Targets**:
   - Volume arc is 80px wide - easy to grab
   - Brightness slider unchanged (188px wide)
   
4. **Visual Clarity**:
   - Removed title provides more breathing room
   - Weather data better positioned (no clipping)

---

## Summary of All Changes

### Code Changes
- **Ball_v6.yaml**: 60 lines modified
- **screens.c**: 8 lines modified
- **Total impact**: 680 insertions, 18 deletions

### Functional Changes
- ✅ Title removal (cleaner UI)
- ✅ Label improvement (better description)
- ✅ Weather placeholders (clearer loading state)
- ✅ Position fix (no clipping)
- ✅ Gesture blocking (better UX)
- ✅ Volume control (new feature)

### Documentation Added
- ✅ CHANGES_V6.1.md (167 lines)
- ✅ VERIFICATION_CHECKLIST.md (214 lines)
- ✅ MEDIA_SCREEN_LAYOUT.md (249 lines)
- ✅ VISUAL_CHANGES_V6.1.md (this file)

### Backward Compatibility
- ✅ All changes are backward compatible
- ✅ No breaking changes
- ✅ Existing configurations work as-is
- ✅ No new dependencies

---

## Next Steps

1. **Flash** updated firmware to device
2. **Test** using VERIFICATION_CHECKLIST.md
3. **Verify** all changes work as expected
4. **Report** any issues found

## Version Info

- **Version**: 6.1
- **Release Date**: 2025-10-10
- **Based On**: Ball V6.0
- **Status**: Ready for testing
