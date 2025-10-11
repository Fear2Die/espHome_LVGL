# Ball V7 - Documentation Index

## Quick Links

### Getting Started
- [README.md](README.md) - Main documentation with features and setup
- [QUICK_START.md](QUICK_START.md) - Fast 5-minute setup guide

### Technical Documentation
- [CHANGES_V7.md](CHANGES_V7.md) - Detailed changelog from Ball V6 to V7
- [VISUAL_LAYOUT.md](VISUAL_LAYOUT.md) - Complete visual layout guide with diagrams
- [Ball_v7.yaml](Ball_v7.yaml) - Main ESPHome configuration file

---

## What's New in Ball V7?

**Album Art Display** - The key feature that sets V7 apart from V6:
- Album cover art displayed inside the progress arc on media page
- 100×100 pixel image, perfectly centered
- Automatic updates when track changes
- Professional styling with rounded corners and border

---

## File Structure

```
Ball v7/
├── Ball_v7.yaml          # Main ESPHome configuration (1774 lines)
├── README.md             # Main documentation
├── QUICK_START.md        # 5-minute setup guide
├── CHANGES_V7.md         # Detailed changelog and technical details
├── VISUAL_LAYOUT.md      # Complete visual layout guide
└── INDEX.md              # This file - documentation index
```

---

## Quick Reference

### For First-Time Users
1. Read [QUICK_START.md](QUICK_START.md)
2. Add Home Assistant template sensors
3. Flash Ball_v7.yaml to device
4. Enjoy album art!

### For Upgrading from Ball V6
1. Read [CHANGES_V7.md](CHANGES_V7.md)
2. Add Home Assistant template sensors (required!)
3. Flash Ball_v7.yaml
4. No other changes needed

### For Developers
1. Review [CHANGES_V7.md](CHANGES_V7.md) for technical implementation
2. Check [VISUAL_LAYOUT.md](VISUAL_LAYOUT.md) for layout details
3. Study [Ball_v7.yaml](Ball_v7.yaml) for code structure

### For Visual Design
1. See [VISUAL_LAYOUT.md](VISUAL_LAYOUT.md) for complete layout
2. Review color scheme and positioning
3. Check size optimization strategy

---

## Home Assistant Requirements

**Required Template Sensors:**
```yaml
template:
  - sensor:
      - name: "Now Playing Title"
        state: >
          {{ state_attr('media_player.spotify', 'media_title') or 'No media' }}

      - name: "Now Playing Artist"
        state: >
          {{ state_attr('media_player.spotify', 'media_artist') or '' }}

      - name: "Now Playing Album Art"
        state: >
          {% set art = state_attr('media_player.spotify', 'entity_picture') %}
          {% if art %}
            http://homeassistant.local:8123{{ art }}
          {% else %}
            ""
          {% endif %}
```

Replace `media_player.spotify` with your actual media player entity.

---

## Key Features

### Album Art Display
- ✅ 100×100 pixels inside 120×120 progress arc
- ✅ RGB565 format (memory efficient)
- ✅ PNG support
- ✅ Automatic updates
- ✅ Rounded corners (10px)
- ✅ Gray border (2px)

### Media Controls
- ✅ Play/Pause button
- ✅ Previous/Next track buttons
- ✅ Volume slider
- ✅ Real-time progress arc
- ✅ Song title and artist (scrolling)

### All Ball V6 Features
- ✅ Three screens (Main, Media, Weather)
- ✅ Swipe navigation
- ✅ Light control
- ✅ Weather display
- ✅ Modern UI design

---

## Technical Specs

### Hardware Requirements
- ESP32-S3 based device (Ball V2 hardware)
- GC9A01A display (240×240 circular)
- WiFi connectivity
- Touch screen support

### Software Requirements
- ESPHome 2025.5.0 or later
- Home Assistant instance
- Media player with album art support
- Network connectivity

### Memory Usage
- Base configuration: ~same as Ball V6
- Album art cache: ~20KB
- HTTP buffer: ~10KB
- Total extra: ~30KB

---

## Support & Troubleshooting

### Album Art Issues
See [README.md](README.md) section "Troubleshooting"

### Configuration Issues
See [QUICK_START.md](QUICK_START.md) troubleshooting section

### Layout Questions
See [VISUAL_LAYOUT.md](VISUAL_LAYOUT.md) for complete details

### Technical Details
See [CHANGES_V7.md](CHANGES_V7.md) for implementation details

---

## Version History

### V7.0 (2025-10-11)
- Initial release with album art support
- Home Assistant template sensor integration
- 100×100 album art display inside progress arc
- Automatic image updates on track change
- RGB565 format for memory efficiency
- Validated configuration with ESPHome

---

## Credits

**Ball V7** by Fear2Die  
**Album Art Feature** requested by user  
**Based on** Ball V6 architecture  

---

## License

Same as main ESPHome-Projects repository.

---

## Contributing

Found an issue or have a suggestion?
- Report issues in the main repository
- Test with different media players
- Share your improvements
- Help others in the community

---

## Related Documentation

### External Links
- [ESPHome Documentation](https://esphome.io/)
- [LVGL Documentation](https://lvgl.io/)
- [Home Assistant Template Documentation](https://www.home-assistant.io/docs/configuration/templating/)

### Repository Links
- Ball V6 Documentation (previous version)
- Ball V5.4 Documentation (earlier version)
- Main repository README

---

**Last Updated**: 2025-10-11  
**Documentation Version**: 1.0  
**Ball Version**: V7.0
