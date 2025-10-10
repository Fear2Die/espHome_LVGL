# Ball V6.5 Quick Reference

## What's New in V6.5?

### 🎯 Instant Volume Control
Volume slider now responds **instantly** with **zero bouncing**.
- Drag the slider → immediate response
- No lag, no jumping, no delays
- Smooth as butter!

### 📊 Real-Time Progress Arc  
Progress arc now **animates smoothly** during playback.
- Updates every second
- Shows actual real-time position
- No more frozen arc!

### 📐 Better Positioning
Volume slider moved up for better fit on circular screen.
- More clearance at bottom
- No overlap with other elements
- Perfect visual balance

### 📸 Album Art Verified
Current implementation confirmed correct.
- Uses standard HA entity_picture
- Works with Spotify, YouTube Music, etc.
- No changes needed

---

## How to Use

### Volume Control
1. **Touch** the volume slider on the left edge
2. **Drag** up or down to adjust volume
3. **Release** to finalize
   - Changes apply **instantly** to Home Assistant
   - No bouncing or lag!

### Media Controls
- **Play/Pause**: Center button
- **Previous**: Left button
- **Next**: Right button
- **Progress**: Circular arc around album art (auto-updates every second)

### Navigation
- **Swipe Left**: Main → Media → Weather → Main
- **Swipe Right**: Main → Weather → Media → Main
- Circular navigation (loops continuously)

---

## Key Improvements Explained

### Why Volume is Instant Now

**Before**: HA updates would interfere during dragging, causing bouncing.

**Now**: All HA updates are blocked while you're touching the slider.

**Result**: Perfect, instant response!

### Why Progress Arc Animates Smoothly Now

**Before**: Arc only updated when HA sent new position data (every 10+ seconds).

**Now**: Arc calculates real-time position using timestamps.

**Result**: Smooth 1-second updates!

---

## Configuration

### Required Substitutions
```yaml
media_player_entity: "media_player.YOUR_ENTITY"  # Your HA media player
```

### Required Components
- ✅ `http_request` - Fetches album art
- ✅ `online_image` - Displays album art
- ✅ Home Assistant time sync
- ✅ Media player in Home Assistant

### Optional Configuration
If `homeassistant.local` doesn't work, update line 160:
```yaml
url: "http://192.168.1.XXX:8123/"  # Use your HA IP
```

Also update line 1225:
```yaml
auto url = "http://192.168.1.XXX:8123" + x;  # Use your HA IP
```

---

## Troubleshooting

### Volume Slider Not Responding
1. Check `media_player_entity` in substitutions
2. Verify media player supports volume control
3. Check ESPHome logs for errors

### Progress Arc Not Animating
1. Ensure media player provides `media_position_updated_at` attribute
2. Check that HA time sync is working (`ha_time`)
3. Verify media is actually playing (not paused)

### Album Art Not Showing
1. Check that media player provides `entity_picture` attribute
2. Verify network connectivity to HA
3. Try using IP address instead of `homeassistant.local`
4. Check ESPHome logs for HTTP errors

### Position Issues on Screen
The current settings are optimized for 240×240 circular displays.
If you have a different display size, you may need to adjust:
- Volume slider: `y: -15` (line 1492)
- Album art: `y: 30` (line 1407)
- Other elements as needed

---

## Technical Details

### New Sensors Added
```yaml
- ha_media_position_updated_at  # Timestamp for position calculation
```

### Global Variables
```yaml
- slider_interaction        # True when user is touching volume slider
- updating_volume_from_ha   # True during HA volume updates
```

### Update Frequencies
- **Progress Arc**: Every 1 second (during playback)
- **Volume Sensor**: As soon as HA changes volume
- **Album Art**: When media changes
- **Media State**: When playback state changes

---

## Compatibility

### Tested With:
- ✅ Spotify
- ✅ YouTube Music  
- ✅ Chromecast

### Display Requirements:
- 240×240 pixels
- Circular display (like Xiaozhi Ball/ESP32 S3 BOX)
- Touch screen

### ESPHome Version:
- Requires ESPHome 2023.7.0 or later
- `online_image` platform required

---

## Upgrade from V6.4

### What Changed:
1. Volume sensor logic (blocking during interaction)
2. Progress arc calculation (real-time position)
3. Volume slider position (y: 0 → y: -15)
4. Added media_position_updated_at sensor

### No Breaking Changes:
- All entity IDs unchanged
- Configuration compatible
- Just flash new firmware

### Migration Steps:
1. Update `Ball_v6.yaml` file
2. Flash to device
3. Test volume and progress arc
4. Done!

---

## Performance Impact

### Memory Usage:
- Minimal increase (~100 bytes for new sensor)
- Album art caching already optimized

### CPU Usage:
- Progress arc: 1 calculation per second (negligible)
- Volume updates: Only when needed (no overhead)

### Network Usage:
- Same as V6.4
- No additional API calls

---

## Known Limitations

### Progress Arc:
- Requires `media_position_updated_at` attribute
  - Most modern media players provide this
  - If not available, arc will update only when position changes
  
### Album Art:
- First load: 5-10 seconds (normal)
- Image quality depends on source
- Requires WiFi connection

### Volume Control:
- Requires media player to support `volume_level` attribute
- Some media players don't support volume control

---

## Support

### Check Logs
```bash
esphome logs ball_v6.yaml
```

### Common Issues:
1. **"Sensor not found"** → Check media player attributes in HA
2. **"HTTP timeout"** → Check network connectivity
3. **"Invalid value"** → Check sensor data types

### Still Having Issues?
1. Review the detailed documentation:
   - `CHANGES_V6.5.md` - Full technical details
   - `VISUAL_CHANGES_V6.5.md` - Visual comparison
   - `ALBUM_ART_IMPLEMENTATION.md` - Album art specifics

2. Check ESPHome logs for error messages

3. Verify Home Assistant integration is working

---

## Version Information

- **Current Version**: Ball V6.5
- **Previous Version**: Ball V6.4
- **Release Date**: 2025
- **Breaking Changes**: None
- **Recommended Update**: Yes (significant improvements)

---

## Credits

Thanks to the ESPHome and Home Assistant communities for excellent documentation and support!

---

## Quick Links

- [Home Assistant Media Player Integration](https://www.home-assistant.io/integrations/media_player/)
- [ESPHome Documentation](https://esphome.io/)
- [ESPHome Display Components](https://esphome.io/components/display/)
- [LVGL Graphics Library](https://lvgl.io/)
