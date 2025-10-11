# Ball V7 - Album Art Edition

## What's New in V7? 🎉

Ball V7 adds **album cover art display** to the media player page, showing the currently playing album artwork inside the progress arc.

### New Features

1. ✅ **Album Art Display** - Shows album cover art from currently playing media
2. ✅ **Centered in Progress Arc** - Album art perfectly positioned inside the progress arc
3. ✅ **Home Assistant Integration** - Uses HA template sensors for album art URL
4. ✅ **Automatic Updates** - Album art updates when track changes
5. ✅ **Professional Styling** - Rounded corners and border for polished look

---

## Required Home Assistant Configuration

Before using Ball V7, you **must** add the following template sensors to your Home Assistant `configuration.yaml`:

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

**Important Notes:**
- Replace `media_player.spotify` with your actual media player entity ID
- Replace `http://homeassistant.local:8123` with your Home Assistant URL if different
- After adding these templates, restart Home Assistant
- Verify the sensors are created in Developer Tools → States

---

## ESPHome Configuration

### Entity Setup

Update the entity configuration section in `Ball_v7.yaml`:

```yaml
substitutions:
  # Light entity
  light_entity: "light.YOUR_LIGHT_ENTITY"
  
  # Media player entity
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  
  # Weather entity
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
```

### How It Works

Ball V7 uses three components to display album art:

1. **HTTP Request Component** - Fetches images from Home Assistant
2. **Online Image Component** - Downloads and caches album art (100×100 RGB565)
3. **Home Assistant Text Sensor** - Monitors `sensor.now_playing_album_art` for URL updates

When media changes:
1. Home Assistant template sensor updates with new album art URL
2. ESPHome receives the URL change
3. Image component downloads and caches the album art
4. Display updates automatically

---

## Media Screen Layout

```
┌──────────────────────────┐
│ ▓│      ◐──────┐         │  1. Volume slider (left)
│ ▓│      │ Album│         │  2. Progress arc (green)
│ ▓│      │  Art │         │  3. Album art (center, 100×100)
│ ▓│      └──────┘         │  4. Song title (scrolling)
│ ▓│    Song Title         │  5. Artist name (scrolling)
│ ▓│    Artist Name        │  6. Controls (bottom)
│ ▓│  [<<]  [▶]  [>>]     │
└──────────────────────────┘
```

### Layout Details

- **Album Art**: 100×100 pixels, centered at y: 30
- **Progress Arc**: 120×120 pixels, centered at y: 20, wraps around album art
- **Styling**: 10px rounded corners, 2px gray border (#666666)
- **Format**: RGB565 (memory efficient), JPEG format (most common for streaming services)

---

## Supported Media Players

Ball V7 works with any Home Assistant media player that provides album art:

- ✅ Spotify
- ✅ YouTube Music
- ✅ Plex
- ✅ Apple Music
- ✅ Google Cast
- ✅ Sonos
- ✅ Any media_player with `entity_picture` attribute

---

## Troubleshooting

### Album Art Not Showing

**Check 1: Home Assistant Template Sensors**
```bash
# In Home Assistant Developer Tools → States
# Search for: sensor.now_playing_album_art
# Verify it shows a URL when media is playing
```

**Check 2: ESPHome Logs**
```bash
# In ESPHome logs, look for:
[album_art] Album art URL: http://...
```

**Check 3: Network Connectivity**
- Verify ESPHome device can reach Home Assistant
- Check WiFi connection is stable
- Ensure Home Assistant URL is correct

**Check 4: Media Player**
- Confirm media player entity provides `entity_picture` attribute
- Try playing different media (some tracks may not have album art)

### Image Not Updating

**Solution:**
- Check that Home Assistant template sensors are updating
- Restart ESPHome device
- Check ESPHome logs for errors

### Image Quality Issues

The image is resized to 100×100 pixels to fit within the circular display and progress arc. This is optimal for:
- Memory efficiency (RGB565 format)
- Display performance
- Visual balance with other UI elements

### Device Freezing or Long Operation Warnings

If you see warnings like:
```
[W][component:443]: online_image took a long time for an operation (93589 ms)
[W][component:446]: Components should block for at most 30 ms
[W][online_image:106]: Image already being updated
```

**This has been fixed in the latest version** with the following improvements:
- **5-second throttle filter** on album art sensor prevents rapid-fire updates
- **Single-mode script** ensures only one image update runs at a time
- **Concurrent update guard** prevents multiple simultaneous download attempts

**Solution:**
1. Pull the latest Ball_v7.yaml from the repository
2. Re-flash your device with the updated configuration
3. Device should no longer freeze during album art downloads

---

## Migration from Ball V6

Ball V7 maintains full compatibility with Ball V6 features:
- ✅ All V6 features work identically
- ✅ Same entity configuration
- ✅ Same gesture controls
- ✅ Same three-screen layout

**Additional Steps:**
1. Add Home Assistant template sensors (see above)
2. Flash Ball_v7.yaml to your device
3. Verify album art appears on media screen

---

## Technical Details

### Component Configuration

```yaml
# HTTP Request - for fetching images
http_request:
  timeout: 10s

# Online Image - for album art
online_image:
  - id: album_art_image
    url: "http://homeassistant.local:8123/"
    type: RGB565
    format: JPEG
    resize: 100x100
    update_interval: never
```

### Sensor Configuration

```yaml
text_sensor:
  - platform: homeassistant
    id: ha_album_art_url
    entity_id: sensor.now_playing_album_art
    on_value:
      - lambda: |-
          if (x.length() > 0) {
            ESP_LOGD("album_art", "Album art URL: %s", x.c_str());
            id(album_art_image).set_url(x.c_str());
            id(album_art_image).update();
          }
```

### Display Widget

```yaml
- image:
    id: album_art_display
    src: album_art_image
    align: TOP_MID
    y: 30
    radius: 10
    border_width: 2
    border_color: 0x666666
```

---

## Version History

### V7.1 (2025-10-11)
- ✅ **Fix**: Added throttling and concurrent update guards to prevent device freezing
- ✅ **Fix**: Added 5-second throttle on album art sensor updates
- ✅ **Fix**: Implemented single-mode script to prevent multiple simultaneous image downloads
- ✅ **Improvement**: Added concurrent update detection with warning logs

### V7.0 (2025-10-11)
- ✅ Initial release with album art support
- ✅ Home Assistant template sensor integration
- ✅ 100×100 album art display inside progress arc
- ✅ Automatic image updates on track change
- ✅ RGB565 format for memory efficiency

---

## Credits

Based on Ball V6 by Fear2Die with album art enhancement requested by user.

**Key Improvements:**
- Album art display inside progress arc
- Integration with Home Assistant template sensors
- Optimized image sizing and positioning
- Professional visual presentation

---

## License

Same as main ESPHome-Projects repository.
