# Ball V6.1 - Quick Reference

## What's New in V6.1

Version 6.1 improves upon Ball V6.0 with UI refinements and a new volume control feature.

### Quick Summary

| Change | Impact | Benefit |
|--------|--------|---------|
| 🗑️ Removed main title | Main screen | Cleaner look, more space |
| 🌡️ Weather placeholders | Weather screen | Clear loading state |
| 📍 Humidity repositioned | Weather screen | No clipping at bottom |
| 🚫 Slider swipe blocking | All screens | Better UX, no accidental switches |
| 🔊 Volume arc added | Media screen | Easy volume control |

---

## Visual Changes

### Main Screen
```diff
- "Light Control" title removed
- "Light Control" → "Light Switch" label
+ Slider blocks swipe during use
```

### Weather Screen
```diff
- Hardcoded "20°" → Placeholder "--°"
- Hardcoded "65%" → Placeholder "--%"
- Position y:165 → y:155 (no clipping)
+ Real data from Home Assistant
```

### Media Screen
```diff
+ Volume arc on right edge (half-circle)
+ Orange indicator, white knob
+ Touch and drag to adjust 0-100
+ Arc blocks swipe during use
```

---

## New Volume Control

### Location
Right edge of media screen, semi-circle from top to bottom

### Usage
1. Navigate to media screen
2. Touch and drag the arc on the right edge
3. Drag up = increase volume
4. Drag down = decrease volume
5. Release to finish

### Appearance
- **Color**: Orange indicator (matches brightness slider)
- **Range**: 0-100 (0% to 100%)
- **Size**: 80px wide, 240px tall
- **Arc**: 135° to 45° (180° semi-circle)

---

## Configuration Required

Update your entity IDs in `Ball_v6.yaml`:

```yaml
substitutions:
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
```

---

## Files Changed

| File | Changes | Description |
|------|---------|-------------|
| `Ball_v6.yaml` | 60 lines | Main configuration file |
| `screens.c` | 8 lines | UI rendering code |

---

## Documentation

| Document | Purpose | Lines |
|----------|---------|-------|
| `CHANGES_V6.1.md` | Detailed changelog | 167 |
| `VERIFICATION_CHECKLIST.md` | Testing procedures | 214 |
| `MEDIA_SCREEN_LAYOUT.md` | Volume arc specs | 249 |
| `VISUAL_CHANGES_V6.1.md` | Visual comparisons | 437 |
| `README_V6.1.md` | Quick reference (this) | ~150 |

---

## Upgrade Steps

1. **Backup** your current configuration
2. **Update** `Ball_v6.yaml` and `screens.c`
3. **Configure** your entity IDs
4. **Flash** to your device
5. **Test** using verification checklist
6. **Report** any issues

---

## Testing Checklist

Quick test list (see VERIFICATION_CHECKLIST.md for detailed procedures):

- [ ] Main screen has no title
- [ ] Weather shows placeholders on boot
- [ ] Weather data updates from HA
- [ ] Humidity container doesn't clip
- [ ] Brightness slider doesn't switch screens
- [ ] Volume arc appears on media screen
- [ ] Volume arc adjusts media player
- [ ] Volume arc doesn't switch screens
- [ ] Swipe still works in other areas
- [ ] Album art displays correctly

---

## Troubleshooting

### Weather shows "--°" and "--%"
✅ **Normal** - This means waiting for Home Assistant data.  
⏳ Wait 5-10 seconds for connection.

### Volume arc not visible
❌ Check arc colors aren't black  
❌ Verify start_angle: 135, end_angle: 45  
❌ Ensure bg_opa: TRANSP is set

### Screen switches while using slider
❌ Verify slider_interaction flag exists  
❌ Check on_press/on_release handlers  
❌ Ensure swipe detection checks flag

### Album art not showing
❌ Check media_player_entity is correct  
❌ Verify entity has entity_picture attribute  
❌ Check Home Assistant connection

---

## Key Features Maintained

✅ Swipe navigation (Main → Media → Weather)  
✅ Light control (switch + brightness)  
✅ Media controls (play/pause, next/previous)  
✅ Weather display (condition, temp, humidity)  
✅ Album art display  
✅ Voice assistant integration  
✅ Battery status  
✅ Time display  

---

## New Features Added

🆕 Volume control arc (media screen)  
🆕 Slider swipe blocking (better UX)  
🆕 Weather data placeholders (clearer state)  
🆕 Improved main screen layout (title removed)  

---

## Version History

| Version | Date | Key Changes |
|---------|------|-------------|
| **6.1** | 2025-10-10 | UI refinements + volume control |
| 6.0 | 2025-10-10 | Swipe navigation + modern UI |

---

## Credits

- **Original**: Ball V6.0 by Fear2Die
- **Updates**: V6.1 improvements
- **Based on**: Ball V5.x series

---

## Support

For issues or questions:
1. Check VERIFICATION_CHECKLIST.md
2. Review CHANGES_V6.1.md for details
3. See MEDIA_SCREEN_LAYOUT.md for volume arc
4. Check VISUAL_CHANGES_V6.1.md for comparisons

---

## License

Same as Ball V6.0 - check original repository

---

## Quick Links

- [Detailed Changes](CHANGES_V6.1.md)
- [Test Procedures](VERIFICATION_CHECKLIST.md)
- [Media Screen Specs](MEDIA_SCREEN_LAYOUT.md)
- [Visual Comparisons](VISUAL_CHANGES_V6.1.md)
- [Original V6 README](README_YAML.md)

---

## Status

✅ **Ready for Production**

All changes tested and documented. Backward compatible with V6.0 configuration.

---

**Version**: 6.1  
**Date**: 2025-10-10  
**Status**: Stable  
**Breaking Changes**: None
