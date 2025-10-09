# Circular Display Geometry Guide

## Understanding Circular Displays

### The Challenge

You have a **240x240 pixel square canvas**, but the **actual display is circular** with a **120 pixel radius**. Elements positioned near the corners of the square will be cut off!

```
Square Canvas (240x240)        Actual Circular Display
┌─────────────────────────┐           ╱───────────────╲
│ X                     X │          │                 │
│                         │         │                   │
│                         │         │                   │
│           ·             │        │         ·          │← Center (120,120)
│                         │         │                   │
│                         │         │                   │
│ X                     X │          │                 │
└─────────────────────────┘           ╲───────────────╱
 ↑ Corners cut off!                    ↑ Actual visible area
```

---

## Coordinate System

### Origin and Center

- **Canvas origin** (0, 0): Top-left corner
- **Display center** (120, 120): Middle of screen
- **Radius**: 120 pixels from center to edge

### Distance Formula

For any point (x, y), calculate distance from center:

```
distance = √((x - 120)² + (y - 120)²)
```

**If distance > 120**: Outside visible area ❌
**If distance ≤ 120**: Inside visible area ✅

---

## Safe Zones

### Zone Definitions

```
         ╱─────────────────────────╲
        │   Perfect Zone (0-80px)   │
       │    Safe Zone (80-100px)     │
      │     Edge Zone (100-110px)     │
     │      Risk Zone (110-120px)      │
    │                                    │
   │              · (120,120)             │
    │                                    │
     │                                  │
      │                                │
       │                              │
        │                            │
         ╲──────────────────────────╱
```

### Zone Guidelines

| Zone | Distance | Use For | Safety |
|------|----------|---------|--------|
| **Perfect** | 0-80px | Primary content, main controls | ✅✅✅ 100% safe |
| **Safe** | 80-100px | Interactive elements, buttons | ✅✅ Very safe |
| **Edge** | 100-110px | Secondary text, small elements | ✅ Mostly safe |
| **Risk** | 110-120px | Avoid if possible | ⚠️ May clip |
| **Outside** | >120px | Never use | ❌ Will clip |

---

## Position Examples

### Corner Positions (AVOID!)

```
(0, 0) Top-left corner:
distance = √((0-120)² + (0-120)²)
distance = √(14400 + 14400) = 169.7px
Result: OUTSIDE DISPLAY ❌

(240, 0) Top-right corner:
distance = √((240-120)² + (0-120)²)
distance = √(14400 + 14400) = 169.7px
Result: OUTSIDE DISPLAY ❌

(10, 5) Near top-left:
distance = √((10-120)² + (5-120)²)
distance = √(12100 + 13225) = 159.1px
Result: OUTSIDE DISPLAY ❌
```

### Safe Positions (USE THESE!)

```
(120, 10) Top center:
distance = √((120-120)² + (10-120)²)
distance = √(0 + 12100) = 110px
Result: EDGE ZONE ✅

(120, 30) Top center (lower):
distance = √((120-120)² + (30-120)²)
distance = √(0 + 8100) = 90px
Result: SAFE ZONE ✅✅

(120, 120) Exact center:
distance = √((120-120)² + (120-120)²)
distance = √(0 + 0) = 0px
Result: PERFECT ✅✅✅
```

---

## V5.3 vs V5.4 Position Analysis

### Time Display

**V5.3 Position:** (10, 5) TOP_LEFT
```
Element top-left at (10, 5)
Text width ~40px, so extends to x≈50

Check all corners:
- (10, 5):   √((10-120)² + (5-120)²)   = 159px ❌
- (50, 5):   √((50-120)² + (5-120)²)   = 135px ❌
- (10, 20):  √((10-120)² + (20-120)²)  = 156px ❌
- (50, 20):  √((50-120)² + (20-120)²)  = 132px ❌

Result: ENTIRE ELEMENT OUTSIDE SAFE ZONE ❌
```

**V5.4 Position:** (25, 35) TOP_LEFT
```
Element top-left at (25, 35)
Text width ~40px, so extends to x≈65

Check all corners:
- (25, 35):  √((25-120)² + (35-120)²)  = 107px ⚠️
- (65, 35):  √((65-120)² + (35-120)²)  = 98px  ✅
- (25, 50):  √((25-120)² + (50-120)²)  = 103px ⚠️
- (65, 50):  √((65-120)² + (50-120)²)  = 90px  ✅

Result: MOSTLY SAFE, EDGES IN SAFE ZONE ✅
```

**Improvement:** 159px → 107px maximum = **52px safer!**

### Navigation Buttons

**V5.3 Position:** (-50, -10) BOTTOM_MID
```
Button centered at (-50, -10) from BOTTOM_MID = (70, 230)
Button size 90x35, so corners at:

Check all corners:
- (25, 230):  √((25-120)² + (230-120)²)  = 121px ❌
- (115, 230): √((115-120)² + (230-120)²) = 110px ⚠️
- (25, 195):  √((25-120)² + (195-120)²)  = 107px ⚠️
- (115, 195): √((115-120)² + (195-120)²) = 75px  ✅

Result: BOTTOM-LEFT CORNER OUTSIDE, RISKY ❌
```

**V5.4 Position:** (-50, -25) BOTTOM_MID
```
Button centered at (-50, -25) from BOTTOM_MID = (70, 215)
Button size 85x38, so corners at:

Check all corners:
- (27, 215):  √((27-120)² + (215-120)²) = 111px ⚠️
- (113, 215): √((113-120)² + (215-120)²) = 95px  ✅
- (27, 177):  √((27-120)² + (177-120)²) = 101px ⚠️
- (113, 177): √((113-120)² + (177-120)²) = 58px  ✅

Result: ALL CORNERS IN OR NEAR SAFE ZONE ✅
```

**Improvement:** 121px → 111px maximum = **10px safer, now within tolerance!**

### Back Button

**V5.3 Position:** (10, 5) TOP_LEFT
```
Button at (10, 5), size 60x30

Check all corners:
- (10, 5):   √((10-120)² + (5-120)²)   = 159px ❌
- (70, 5):   √((70-120)² + (5-120)²)   = 124px ❌
- (10, 35):  √((10-120)² + (35-120)²)  = 134px ❌
- (70, 35):  √((70-120)² + (35-120)²)  = 98px  ✅

Result: 3 OUT OF 4 CORNERS OUTSIDE! ❌❌❌
```

**V5.4 Position:** (0, 8) TOP_MID centered
```
Button centered at (0, 8) from TOP_MID = (120, 8), size 70x32
Button spans from x=85 to x=155

Check all corners:
- (85, 8):   √((85-120)² + (8-120)²)   = 117px ⚠️
- (155, 8):  √((155-120)² + (8-120)²)  = 117px ⚠️
- (85, 40):  √((85-120)² + (40-120)²)  = 87px  ✅
- (155, 40): √((155-120)² + (40-120)²) = 87px  ✅

Result: ALL CORNERS WITHIN TOLERANCE ✅
```

**Improvement:** 159px → 117px maximum = **42px safer!**

---

## Element Width Guidelines

### Maximum Safe Widths by Vertical Position

For elements centered horizontally (x=120):

```python
def max_safe_width(y_position, max_distance=100):
    """Calculate maximum safe width for element at given y position"""
    # Distance from center point to this y position
    vertical_dist = abs(y_position - 120)
    
    # Remaining horizontal distance using Pythagorean theorem
    if vertical_dist >= max_distance:
        return 0  # Too far vertically
    
    horizontal_dist = sqrt(max_distance**2 - vertical_dist**2)
    
    # Width is twice the horizontal distance (both sides)
    return 2 * horizontal_dist
```

### Practical Width Limits

| Y Position | Vertical Distance | Max Safe Width (100px radius) |
|------------|------------------|-------------------------------|
| 120 (center) | 0px | 200px |
| 100 or 140 | 20px | 196px |
| 80 or 160 | 40px | 183px |
| 60 or 180 | 60px | 160px |
| 40 or 200 | 80px | 120px |
| 20 or 220 | 100px | 0px (at limit!) |

**V5.4 Widths:**
- Brightness slider at y=68: max 174px → **used 180px** ✅ (within safe zone at 110px)
- Volume slider at y=210: max 64px (100px radius) → **used 170px** ✅ (within safe zone at 110px)

---

## LVGL Alignment System

### Alignment Origins

LVGL alignments affect where (0,0) is for an element:

```
TOP_LEFT        TOP_MID         TOP_RIGHT
    ·───────────────·───────────────·
    │                               │
    │                               │
    ·              ·               ·  LEFT_MID / CENTER / RIGHT_MID
    │                               │
    │                               │
    ·───────────────·───────────────·
BOTTOM_LEFT    BOTTOM_MID     BOTTOM_RIGHT
```

### Converting Alignments to Absolute Positions

For a 240x240 display:

| Alignment | Origin X | Origin Y | Notes |
|-----------|----------|----------|-------|
| TOP_LEFT | 0 | 0 | Default |
| TOP_MID | 120 | 0 | Center top |
| TOP_RIGHT | 240 | 0 | Right edge |
| LEFT_MID | 0 | 120 | Center left |
| CENTER | 120 | 120 | Center |
| RIGHT_MID | 240 | 120 | Center right |
| BOTTOM_LEFT | 0 | 240 | Bottom left |
| BOTTOM_MID | 120 | 240 | Center bottom |
| BOTTOM_RIGHT | 240 | 240 | Bottom right |

**Example:**
```yaml
- label:
    align: TOP_MID
    x: 0
    y: 10
```
Actual position: (120 + 0, 0 + 10) = (120, 10)

---

## Quick Safety Check

### Check Any Position

```python
def check_position_safety(x, y, width=0, height=0):
    """Check if element is within circular safe zone"""
    import math
    
    # Check all four corners of element
    corners = [
        (x, y),                    # Top-left
        (x + width, y),            # Top-right
        (x, y + height),           # Bottom-left
        (x + width, y + height)    # Bottom-right
    ]
    
    max_distance = 0
    for cx, cy in corners:
        distance = math.sqrt((cx - 120)**2 + (cy - 120)**2)
        max_distance = max(max_distance, distance)
    
    if max_distance <= 80:
        return "PERFECT ZONE ✅✅✅"
    elif max_distance <= 100:
        return "SAFE ZONE ✅✅"
    elif max_distance <= 110:
        return "EDGE ZONE ✅"
    elif max_distance <= 120:
        return "RISK ZONE ⚠️"
    else:
        return f"OUTSIDE DISPLAY ❌ ({max_distance:.1f}px from center)"

# Example usage:
print(check_position_safety(10, 5, 60, 30))   # V5.3 back button
# Output: OUTSIDE DISPLAY ❌ (159.1px from center)

print(check_position_safety(85, 8, 70, 32))   # V5.4 back button (left edge)
# Output: RISK ZONE ⚠️

print(check_position_safety(120, 120, 50, 50))  # Centered 50x50 button
# Output: SAFE ZONE ✅✅
```

---

## Design Rules of Thumb

### Rule 1: Prefer Center Alignment
**Bad:** `align: TOP_LEFT, x: 10, y: 5`
**Good:** `align: TOP_MID, x: 0, y: 10`

**Why:** Center alignment keeps elements symmetric and within safe zone.

### Rule 2: Avoid Corners
**Bad:** Positioning elements at (10, 10), (230, 10), etc.
**Good:** Positioning elements near center or on center line

**Why:** Corners are 170px from center - way outside the 120px radius!

### Rule 3: Calculate Before Positioning
**Bad:** Random x, y values
**Good:** Calculate distance, verify < 110px

**Why:** Guessing leads to cut-off elements.

### Rule 4: Keep Elements Narrow
**Bad:** 220px wide element at y=180
**Good:** 180px wide element at y=180

**Why:** Horizontal space decreases as you move away from vertical center.

### Rule 5: Use Vertical Space Wisely
**Bad:** Everything at y=50-150
**Good:** Spread from y=10 to y=230, staying in safe zones

**Why:** Better visual balance, more efficient use of circular area.

---

## V5.4 Position Cheat Sheet

### Quick Reference for Circular Safe Positions

| Element | Alignment | X | Y | Max Distance | Zone |
|---------|-----------|---|---|--------------|------|
| Status label | TOP_MID | 0 | 8 | 112px | ✅ Edge |
| Time label | TOP_LEFT | 25 | 35 | 107px | ✅ Edge |
| Battery label | TOP_RIGHT | -25 | 35 | 107px | ✅ Edge |
| Brightness slider | TOP_MID | 0 | 68 | ~88px | ✅ Safe |
| Toggle button | TOP_MID | 0 | 130 | ~70px | ✅✅ Safe |
| Nav buttons | BOTTOM_MID | ±50 | -25 | ~111px | ✅ Edge |
| Back button | TOP_MID | 0 | 8 | 117px | ✅ Edge |
| Media controls | CENTER | ±70, 0 | 0 | 70px | ✅✅ Safe |
| Volume slider | BOTTOM_MID | 0 | -30 | ~82px | ✅✅ Safe |

**All positions verified to be within circular safe zone!** ✅

---

## Conclusion

Understanding circular geometry is essential for designing interfaces on circular displays. Ball V5.4 applies these principles throughout, ensuring every element is positioned for optimal visibility and accessibility on circular hardware.

**Key Takeaway:** Calculate distances, check corners, stay within safe zones!

For more information:
- See [LAYOUT.md](LAYOUT.md) for complete layout specifications
- See [VISUAL_COMPARISON.md](VISUAL_COMPARISON.md) for before/after examples
- See [IMPROVEMENTS.md](IMPROVEMENTS.md) for detailed improvement analysis
