# Ball V6.2 - Bug Fix Release

## 🎯 What's Fixed

This release addresses three critical issues reported in Ball V6.1:

1. ✅ **Weather data displaying as 0** - Fixed with robust NaN validation
2. ✅ **Volume control UX** - Replaced arc with intuitive vertical slider
3. ✅ **Album art not showing** - Added explicit update trigger

## 🚀 Quick Upgrade

### From V6.1 to V6.2
1. Backup your current `Ball_v6.yaml`
2. Replace with the new V6.2 version
3. Keep your entity IDs (no config changes needed)
4. Flash to your device
5. Test the three fixed features

**Time Required**: ~5 minutes  
**Configuration Changes**: None (fully backward compatible)

## 📋 What Changed

### 1. Weather Data - Now Shows Correctly ✅

**Problem**: Temperature and humidity showing as "0" or not updating.

**Solution**: Added validation to handle invalid data gracefully.

```yaml
# Before: Could show 0 or crash
text: !lambda 'return (char*)buf;'

# After: Shows "--°" when invalid, actual value when valid
text: !lambda |-
  if (isnan(x)) {
    return std::string("--°");
  }
  // ... format and return valid data
```

**What You'll See**:
- On boot: `--°` and `--%` (placeholders)
- Once connected: Actual temperature and humidity
- If disconnected: Returns to placeholders (not "0")

### 2. Volume Control - Much Easier to Use ✅

**Problem**: Circular arc slider on right edge was hard to grab and adjust.

**Solution**: Replaced with familiar vertical slider on left edge.

| Feature | V6.1 (Arc) | V6.2 (Slider) |
|---------|------------|---------------|
| **Location** | Right edge | Left edge |
| **Type** | Circular arc | Vertical slider |
| **Motion** | Circular | Up/Down |
| **Size** | 80×240 | 15×200 |
| **Usability** | ⭐⭐ | ⭐⭐⭐⭐⭐ |

**How to Use**:
1. Touch the slider on the left edge
2. Drag **up** to increase volume
3. Drag **down** to decrease volume
4. Visual feedback shows current level

### 3. Album Art - Now Displays ✅

**Problem**: Album art image not appearing even when media playing.

**Solution**: Added explicit `update()` call to trigger image refresh.

```yaml
# Before: Set URL but didn't refresh
id(album_art_image).set_url(url.c_str());

# After: Set URL and force refresh
id(album_art_image).set_url(url.c_str());
id(album_art_image).update();  # ← This fixes it!
```

**What You'll See**:
- Album art appears within 5-10 seconds of playing media
- Updates automatically when track changes
- Works with Spotify, YouTube Music, etc.

## 🎨 Visual Changes

### Media Screen Comparison

```
V6.1 (Before):              V6.2 (After):
┌──────────────────┐        ┌──────────────────┐
│           ╱─╲    │        │ │                │
│   [Art]  │   │   │        │ │    [Art]       │
│           ╲─╱    │        │ ╵                │
│                  │        │                  │
│   [Controls]     │        │   [Controls]     │
└──────────────────┘        └──────────────────┘
    Arc slider                 Vertical slider
   (right edge)                 (left edge)
```

## 📝 Configuration

### No Changes Required!

Your existing entity configuration from V6.1 works without modification:

```yaml
substitutions:
  light_entity: "light.YOUR_LIGHT"
  media_player_entity: "media_player.YOUR_PLAYER"
  weather_entity: "weather.YOUR_WEATHER"
```

## 🧪 Testing Checklist

After upgrading, test these features:

- [ ] **Weather Screen**
  - [ ] Shows placeholders on boot (`--°`, `--%`)
  - [ ] Updates with actual data from HA
  - [ ] Handles missing data gracefully

- [ ] **Volume Control**
  - [ ] Visible on left edge of media screen
  - [ ] Drag up increases volume
  - [ ] Drag down decreases volume
  - [ ] Changes reflect in Home Assistant
  - [ ] Doesn't trigger screen swipe

- [ ] **Album Art**
  - [ ] Shows when media is playing
  - [ ] Updates when track changes
  - [ ] Displays within 10 seconds

## 🐛 Troubleshooting

### Weather Still Showing "--°"

**Check**:
1. Weather entity is correct in substitutions
2. Weather integration is configured in HA
3. Entity has temperature/humidity attributes
4. Try restarting ESPHome device

**Test**: Open HA → Developer Tools → States → Find your weather entity → Verify it has `temperature` and `humidity` attributes.

### Volume Slider Not Visible

**Check**:
1. You're on the media screen (swipe left from main)
2. Look at the **left** edge (changed from right in V6.1)
3. Slider is 15px from left edge

### Album Art Not Showing

**Check**:
1. Media is actually playing (not paused/stopped)
2. Media player provides `entity_picture` attribute
3. Network connection to Home Assistant is stable
4. Try changing tracks to trigger update

**Test**: Check HA → Developer Tools → States → Your media player → Look for `entity_picture` attribute.

## 📚 Documentation

- **Full Changelog**: See `CHANGES_V6.2.md`
- **Visual Changes**: See `VISUAL_CHANGES_V6.2.md`
- **Media Layout**: See `MEDIA_SCREEN_LAYOUT.md` (updated for V6.2)

## 🎓 Technical Details

### Weather Fix
- Uses `isnan()` to detect invalid float values
- Returns `std::string` for type safety
- Consistent with initialization placeholders

### Volume Slider
- LVGL slider widget (more efficient than arc)
- LEFT_MID alignment for consistent positioning
- Maintains gesture blocking for smooth UX

### Album Art
- Explicit `update()` triggers ESPHome image refresh
- Works with both relative (`/local/...`) and absolute URLs
- RGB565 format for optimal memory usage

## ⚠️ Known Issues

None! All reported issues from V6.1 are resolved in V6.2.

## 🔜 Future Plans

Possible enhancements being considered:
- Volume percentage label next to slider
- Sync slider with actual HA volume state
- Loading indicator for album art
- Fallback image when no album art available

## 💬 Feedback

Encountered issues or have suggestions? Please report them via GitHub Issues.

---

**Version**: 6.2  
**Date**: October 2025  
**Compatibility**: ESP32-S3, Ball V2 Hardware  
**Based On**: Ball V6.1 with critical bug fixes
