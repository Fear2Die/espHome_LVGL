# Ball V6 Quick Reference

## Navigation

### Swipe Gestures
```
┌─────────────────────────┐
│                         │
│   ←  Swipe Right        │  Previous Screen
│   →  Swipe Left         │  Next Screen
│                         │
└─────────────────────────┘
```

### Screen Flow (Circular)
```
     Main Screen
      ↙     ↘
     ↙       ↘
  Media    Weather
    ↓         ↓
     ↘       ↙
      ↘     ↙
     Main Screen
```

## Screen Controls

### Main Screen - Light Control
| Widget | Action | Result |
|--------|--------|--------|
| Toggle Switch | Tap | Turn light on/off |
| Brightness Slider | Drag | Adjust brightness 0-100% |
| Status Bar | View | See time and battery |

### Media Screen - Music Control
| Widget | Action | Result |
|--------|--------|--------|
| << Button | Tap | Previous track |
| \> Button | Tap | Play/Pause |
| >> Button | Tap | Next track |
| Album Art | View | Current album cover |
| Title/Artist | View | Scrolling text |
| Progress Arc | View | Playback progress |

### Weather Screen - Information
| Widget | Action | Result |
|--------|--------|--------|
| Temperature | View | Current temp in large text |
| Condition | View | Weather status |
| Humidity Card | View | Current humidity |

## Color Codes

### Main Screen
- **Background**: Black (#000000)
- **Slider Indicator**: Orange/Yellow (#FFB800)
- **Switch On**: Green (#34C759)
- **Switch Off**: Gray (#3A3A3A)

### Media Screen
- **Background**: Black (#000000)
- **Progress Arc**: Spotify Green (#1DB954)
- **Buttons**: Dark Gray (#333333)
- **Center Button**: Medium Gray (#4A4A4A)

### Weather Screen
- **Background**: Black (#000000)
- **Temperature**: White (#FFFFFF)
- **Condition**: Sky Blue (#87CEEB)
- **Humidity**: Sky Blue (#87CEEB)

## Widget Sizes

### Touch Targets
- **Buttons**: 45x45 pixels (circular)
- **Switch**: 90x40 pixels
- **Slider**: 188x30 pixels (188 width, 30 height)

### Display Elements
- **Album Art**: 100x100 pixels
- **Progress Arc**: 120x120 pixels
- **Humidity Card**: 180x50 pixels

## Typography

### Font Sizes
- **Hero (Temp)**: 48pt
- **H1 (Titles)**: 22pt
- **H2 (Values)**: 20pt
- **H3 (Labels)**: 18pt
- **Body**: 16pt
- **Small**: 14pt
- **Caption**: 12pt

## Gesture Settings

### Thresholds
- **Gesture Limit**: 50 pixels
- **Min Velocity**: 3 pixels/frame
- **Animation Duration**: 250ms

## Quick Tips

### Best Practices
✅ **DO**:
- Swipe smoothly across the screen
- Wait for animation to complete
- Use circular buttons in center area
- Check status bar regularly

❌ **DON'T**:
- Swipe during animations
- Tap rapidly on buttons
- Expect diagonal swipes to work
- Look for back buttons

### Common Issues

**Gesture Not Detected?**
- Swipe at least 50 pixels
- Move at consistent speed
- Start from screen edge
- Wait for current animation

**Button Not Responding?**
- Tap in button center
- Release on the button
- Don't drag while tapping
- Check if widget is active

**Display Looks Cut Off?**
- Normal for circular display
- Important content is centered
- Edges designed for circle
- Status bar optimized

## Keyboard Shortcuts

Not applicable - touch-only interface.

## Screen States

### Main Screen States
| State | Switch | Slider | Meaning |
|-------|--------|--------|---------|
| Light Off | Off (Gray) | Low | Light is off |
| Light On | On (Green) | Active | Light is on at brightness |
| Adjusting | Any | Moving | User changing brightness |

### Media Screen States
| State | Button | Arc | Meaning |
|-------|--------|-----|---------|
| Playing | \|\| | Moving | Music playing |
| Paused | > | Stopped | Music paused |
| Idle | > | 0 | No music |

### Weather Screen States
- Always display-only
- Updates periodically
- No interactive elements

## Troubleshooting

### Navigation Issues
```
Problem: Can't swipe to next screen
Solution: 
  1. Swipe at least 50 pixels
  2. Wait for animation to finish
  3. Check touch is working (test buttons)
```

### Display Issues
```
Problem: Elements look misaligned
Solution:
  1. This is a circular display
  2. Elements optimized for circle
  3. Important content centered
  4. Edges naturally cut off
```

### Touch Issues
```
Problem: Buttons not responding
Solution:
  1. Tap button center
  2. Use finger pad, not tip
  3. Don't slide while tapping
  4. Check backlight is on
```

## Integration Quick Start

### Minimal ESPHome Config
```yaml
lvgl:
  touchscreens:
    - touchscreen_id: touch_screen
      gesture_support: true
  
  on_setup:
    - lambda: |-
        create_screens();
```

### Connect Light Control
```yaml
# In lambda/interval
lv_obj_add_event_cb(objects.obj0, [](lv_event_t *e) {
  // Toggle light
}, LV_EVENT_VALUE_CHANGED, NULL);
```

### Update Time Display
```yaml
# In interval
lv_label_set_text_fmt(objects.date, "%02d:%02d", hour, min);
```

## Performance Tips

### Optimize Updates
- Update only on state change
- Batch multiple updates
- Use intervals wisely
- Cache values when possible

### Memory Management
- Screens created once
- Don't recreate widgets
- Reuse objects
- Monitor PSRAM usage

## Version Info

- **Version**: 6.0
- **Release**: 2025-10-10
- **LVGL**: 8.3.x
- **Display**: GC9A01A 240x240

## Documentation

### Full Docs
- **README.md**: Overview and features
- **LAYOUT.md**: Detailed layouts
- **INTEGRATION_GUIDE.md**: ESPHome setup
- **CHANGELOG.md**: Version changes

### External Links
- **LVGL Docs**: https://docs.lvgl.io/
- **ESPHome**: https://esphome.io/
- **Repository**: https://github.com/Fear2Die/ESPHome-Projects

## Support

### Get Help
1. Check this quick reference
2. Read full documentation
3. Check GitHub issues
4. Create new issue if needed

### Report Issues
Include:
- Ball V6 version
- ESPHome version
- LVGL version
- Hardware variant
- Problem description
- Steps to reproduce

---

**Quick Reference Version**: 1.0
**Last Updated**: 2025-10-10
**Print-Friendly**: Yes
