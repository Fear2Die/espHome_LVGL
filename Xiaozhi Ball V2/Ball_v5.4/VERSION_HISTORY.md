# Ball Version History

## Version 5.4.1 (Current - Overlap Fix Release)
**Release Date**: 2024
**Status**: ✅ Stable - Recommended

### Critical Fixes
- ✅ Fixed main page toggle button overlapping with navigation buttons (9px gap → 1px gap)
- ✅ Fixed media page massive overlap (state label overlapped controls by 82px!)
- ✅ Adjusted all element positions to ensure no overlaps
- ✅ Reduced button heights where needed (38→33px, 48→40px)
- ✅ Font size optimization (montserrat_16→14 on media page for tighter layout)

### Changes
- Toggle button: y=130→112, height=38→33
- Nav buttons: y=-25→-61, height=38→33
- Album art: y=50→45
- Media text: smaller fonts (montserrat_14)
- State label: Moved above controls (y=162→144)
- Control buttons: CENTER→TOP_MID at y=162, height=48→40
- Volume slider: y=-30→-22, height=18→16

### Files Added
- `CHANGES_V5.4.1.md` - Detailed changelog
- `OVERLAP_FIX_DETAILS.md` - Visual before/after comparison
- `SUGGESTED_IMPROVEMENTS.md` - Future enhancement ideas
- `VERSION_HISTORY.md` - This file

**Upgrade from V5.4**: Highly recommended! Just flash the new YAML.

---

## Version 5.4 (Circular Display Optimization)
**Release Date**: 2024
**Status**: ⚠️ Superseded by V5.4.1 (had overlap issues)

### Major Changes
- 🔵 Complete circular display optimization
- 📍 All elements positioned within circular safe zone
- 👆 Better touch experience on circular hardware
- 🎨 Centered back buttons (much more intuitive)
- 📊 Mathematically calculated positions

### Positioning Changes
- Status bar: Time/Battery moved inward (x=±10→±25, y=5→35)
- Navigation: Moved up (y=-10→-25)
- Media controls: Changed to CENTER alignment
- Text widths: Reduced (220→200px) for circular fit

### Files Added
- `CHANGES_V5.4.md` - V5.3 to V5.4 changes
- `CIRCULAR_GEOMETRY.md` - Circular display mathematics
- `LAYOUT.md` - Complete layout documentation

**Known Issues**: Element overlaps (fixed in V5.4.1)

---

## Version 5.3 (Layout Fixes & Album Art)
**Release Date**: 2024
**Status**: ⚠️ Superseded by V5.4+

### Changes
- Fixed navigation button overlap from V5.2
- Reverted to 2-button layout (removed camera button)
- Buttons moved down (y=-45→-10)
- Larger buttons (70x30→90x35)
- Album art display functional

### Navigation
- Media button: x=-50, y=-10
- Weather button: x=50, y=-10

**Issues**: Still had some overlap concerns, addressed in V5.4

---

## Version 5.2 (Camera Page & Media Enhancements)
**Release Date**: 2024
**Status**: ⚠️ Superseded

### Major Features
- ➕ Camera page added
- 🎵 Album art support
- 🎮 Fixed media player button glyphs
- 🔧 Easy entity configuration via substitutions

### Changes
- 3-button navigation (Media, Weather, Camera)
- Buttons smaller (90x35→70x30) to fit 3 buttons
- Buttons moved up (y=-10→-45)
- Media page: Album art at y=40, controls at y=185

### New Files
- Camera page functionality
- Entity substitutions

**Issues**: Navigation buttons too small and at edge (fixed in V5.3)

---

## Version 5.1
**Release Date**: 2024
**Status**: ⚠️ Superseded

### Features
- 2-button navigation (Media, Weather)
- Basic media player controls
- Weather page
- Light control

### Layout
- Navigation at y=-10 (90x35 buttons)
- No album art
- Unicode button glyphs

---

## Version 5.0 (Navigation Update)
**Release Date**: 2024
**Status**: ⚠️ Superseded

### Major Changes
- Added navigation system
- Multi-page interface
- Media player page
- Weather page
- Live state tracking from Home Assistant

### Previous Limitation
- Single page only
- No media controls
- No weather display

---

## Version 4.0 (Brightness Fix)
**Release Date**: 2024
**Status**: ⚠️ Superseded

### Changes
- Fixed vertical spacing issues from V3
- Optimized for 240x240 display
- Better button positioning
- Added time display

---

## Version 3.0 and Earlier
**Status**: Legacy versions

Basic light control functionality with voice assistant integration.

---

## Upgrade Path

### From V5.4 → V5.4.1
✅ **Highly Recommended** - Critical overlap fixes
- Just flash new YAML file
- No configuration changes needed
- All features preserved

### From V5.3 → V5.4.1
✅ **Recommended** - Better circular display support
- Flash V5.4.1 YAML
- Copy your entity IDs
- Enjoy circular optimizations + fixes

### From V5.2 or Earlier → V5.4.1
✅ **Strongly Recommended** - Major improvements
- Add entity substitutions (see QUICK_START.md)
- Update entity configuration at top of file
- Flash V5.4.1 YAML
- Significant layout and feature improvements

---

## Feature Comparison Matrix

| Feature | V3 | V4 | V5.0 | V5.1 | V5.2 | V5.3 | V5.4 | V5.4.1 |
|---------|----|----|------|------|------|------|------|--------|
| Light Control | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Time Display | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Navigation | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Media Player | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Weather Page | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| Album Art | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ |
| Camera Page | ❌ | ❌ | ❌ | ❌ | ✅ | ❌ | ❌ | ❌ |
| Easy Config | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ |
| Fixed Glyphs | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ | ✅ | ✅ |
| Circular Opt | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ | ✅ | ✅ |
| No Overlaps | ❌ | ❌ | ❌ | ❌ | ❌ | ⚠️ | ❌ | ✅ |
| Buttons (Nav) | - | - | 2 | 2 | 3 | 2 | 2 | 2 |

### Legend
- ✅ = Fully working
- ⚠️ = Partially working / Minor issues
- ❌ = Not available / Broken

---

## Recommended Version

### For New Installations
**Use V5.4.1** - Latest stable with all fixes

### For Existing V5.4 Users
**Upgrade to V5.4.1** - Critical overlap fixes

### For V5.3 and Earlier
**Upgrade to V5.4.1** - Significant improvements

---

## Breaking Changes History

### V5.4.1 → V5.4
- None - Fully compatible

### V5.4 → V5.3
- None - Fully compatible

### V5.3 → V5.2
- Removed camera page
- Changed from 3 buttons to 2
- Different button positioning

### V5.2 → V5.1
- Added camera page
- Changed from 2 buttons to 3

### V5.1 → V5.0
- None - Fully compatible

### V5.0 → V4.0
- Added navigation system
- Multi-page interface
- Requires entity configuration

---

## File Structure Evolution

### V5.4.1
```
Ball_v5.4/
├── Ball_v5.4.yaml              (Main config - with fixes)
├── README.md                   (Updated for v5.4.1)
├── CHANGES_V5.4.md            (V5.3→V5.4 changes)
├── CHANGES_V5.4.1.md          (V5.4→V5.4.1 fixes)
├── OVERLAP_FIX_DETAILS.md     (Visual comparisons)
├── LAYOUT.md                   (Updated layout docs)
├── SUGGESTED_IMPROVEMENTS.md   (Future ideas)
├── VERSION_HISTORY.md          (This file)
└── Other docs...
```

### V5.4
```
Ball_v5.4/
├── Ball_v5.4.yaml
├── README.md
├── CHANGES_V5.4.md
├── CIRCULAR_GEOMETRY.md
├── LAYOUT.md
└── Other docs...
```

---

## Statistics

### Code Metrics (V5.4.1)
- **Lines of YAML**: ~1692
- **LVGL Widgets**: ~40+
- **Pages**: 11 (idle, media, weather, + 8 assistant pages)
- **Buttons**: 9 interactive
- **Sensors**: 7 Home Assistant sensors
- **Text Sensors**: 5 text sensors
- **Scripts**: 8 automation scripts

### Layout Metrics (V5.4.1)
- **Main Page Gap**: 1px (was -9px overlap in V5.4)
- **Media Page Gaps**: 0-7px (was -82px to 10px in V5.4)
- **Circular Safe Zone**: All elements within 110px radius
- **Button Sizes**: 33-44px height (optimized for touch)

---

## Support

### Documentation
- See `README.md` for setup instructions
- See `LAYOUT.md` for layout details
- See `CHANGES_V5.4.1.md` for recent changes
- See `SUGGESTED_IMPROVEMENTS.md` for future ideas

### Issues
- Report issues on GitHub
- Check existing issues first
- Provide YAML version in report

---

**Ball V5.4.1** - The best version yet! 🎉
