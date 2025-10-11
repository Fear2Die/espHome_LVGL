# Ball V6.2 Errata

## Album Art Format Correction

**Issue**: The original Ball V6.2 release incorrectly used `format: AUTO` for the `online_image` component.

**Error Message**:
```
online_image: [source ball_v6.2.yaml:159]
  - id: album_art_image
    url: http://homeassistant.local:8123/
    type: RGB565

    Unknown value 'AUTO', valid options are 'BMP', 'JPEG', 'PNG', 'JPG'.
    format: AUTO
    resize: 100x100
    update_interval: never
```

**Root Cause**: ESPHome does not support `AUTO` as a format value for the `online_image` component.

**Correction Applied**: Changed `format: AUTO` to `format: PNG` (line 162 in Ball_v6.2.yaml).

**Rationale**: 
- PNG is a valid ESPHome format
- Home Assistant typically serves album art in PNG format (or converts to PNG)
- Works with all media sources (Spotify, YouTube Music, Plex, etc.)
- This is the same fix that was applied in Ball V6.3

**Date Corrected**: 2025-10-11

---

**Note**: The CHANGES_V6.2.md file documents the original (incorrect) intention to use AUTO format. The actual working configuration now uses PNG format as documented above.
