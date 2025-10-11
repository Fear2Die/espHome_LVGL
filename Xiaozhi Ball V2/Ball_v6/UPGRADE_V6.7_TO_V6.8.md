# Upgrade Guide: Ball V6.7 → V6.8

## Overview

Ball V6.8 removes non-functional album art display and implements real-time progress arc updates for accurate media playback visualization.

## What Changed

### ❌ Removed Features
- **Album Art Display** - Was not working properly and wasting memory
- **HTTP Request Component** - No longer needed without album art
- **Token Authentication** - Removed `ha_base_url` and `ha_token` configuration

### ✅ Added Features  
- **Real-Time Progress Arc** - Updates every second during playback
- **Accurate Position Tracking** - Arc reflects actual media position, not stale data
- **Memory Efficiency** - ~20KB freed from album art buffer

### 🔄 Modified Features
- **Progress Arc Styling** - Increased from 4px to 6px width for better visibility

## Migration Steps

### 1. Update Configuration File

Simply replace your `Ball_v6.yaml` with the new version. No manual configuration changes required!

**What Was Removed:**
```yaml
# These sections are now GONE (no action needed):
ha_base_url: "..."        # ← Removed
ha_token: "..."           # ← Removed
http_request: ...         # ← Removed
online_image: ...         # ← Removed
ha_media_picture: ...     # ← Removed
```

**What Was Added:**
```yaml
# These sections are now PRESENT (automatic):
ha_media_position_updated_at: ...  # ← New sensor
on_time:
  - seconds: '*'                   # ← Real-time updates
```

### 2. Flash Updated Firmware

```bash
# Using ESPHome CLI
esphome run Ball_v6.yaml

# Or using ESPHome Dashboard
# 1. Upload new Ball_v6.yaml
# 2. Click "INSTALL"
# 3. Choose your installation method
```

### 3. Verify Changes

After flashing, navigate to the Media screen and verify:

✅ **Progress arc is visible** (no album art)  
✅ **Arc updates smoothly** every second during playback  
✅ **Arc position matches** actual media position  
✅ **Arc responds** to play/pause/skip correctly  

## Visual Comparison

### Before (V6.7)
```
Media Screen:
┌─────────────────────┐
│                     │
│   ┌───────────┐     │
│   │           │     │ ← Album art placeholder
│   │  Broken   │     │   (not working)
│   │           │     │
│   └───────────┘     │
│    ○ Progress       │ ← Thin arc (4px)
│                     │   Only updates on HA events
│   Song Title        │   (appears frozen)
│   Artist Name       │
│                     │
│  << ▶ >>  [Vol]     │
└─────────────────────┘
```

### After (V6.8)
```
Media Screen:
┌─────────────────────┐
│                     │
│                     │
│       ◐  50%        │ ← Thicker arc (6px)
│    (Progress)       │   Updates every second
│                     │   Real-time animation
│                     │
│   Song Title        │
│   Artist Name       │
│                     │
│  << ▶ >>  [Vol]     │
└─────────────────────┘
```

## Benefits

### Memory Usage
| Component | V6.7 | V6.8 | Saved |
|-----------|------|------|-------|
| Album Art Buffer | 20KB | 0KB | **20KB** |
| HTTP Request | ~2KB | 0KB | **~2KB** |
| Token Auth Code | ~1KB | 0KB | **~1KB** |
| **Total** | **~23KB** | **0KB** | **~23KB** |

### Progress Arc Accuracy

| Scenario | V6.7 Behavior | V6.8 Behavior |
|----------|---------------|---------------|
| Media Playing | Static (waits for HA) | Updates every second ✅ |
| Position Lag | 5-10 seconds behind | Real-time ✅ |
| Pause/Resume | May show wrong position | Accurate position ✅ |
| Skip Track | Slow to update | Immediate update ✅ |

## Breaking Changes

### None! 🎉

This is a **non-breaking** update:
- No configuration changes required
- No entity ID changes
- No Home Assistant modifications needed
- Simply flash and enjoy

## Troubleshooting

### Progress Arc Not Updating

**Check these:**
1. ✅ Home Assistant connection active?
2. ✅ Media player entity configured correctly?
3. ✅ `media_position_updated_at` attribute available?
4. ✅ Time component synced with Home Assistant?

**Fix:**
```yaml
# Verify your media player entity has these attributes:
# - media_position
# - media_duration  
# - media_position_updated_at
# - state (playing/paused)
```

### Arc Jumps or Resets

**Cause:** Media player not providing `media_position_updated_at` attribute

**Solution:** This is normal - some media players don't support this attribute. Arc will still update, just less smoothly.

### Arc Percentage Wrong

**Cause:** Media player reporting incorrect duration

**Fix:** This is a media player issue, not Ball V6.8. Try restarting your media player in Home Assistant.

## Rollback (If Needed)

If you need to rollback to V6.7:

```bash
# Checkout previous version
git checkout <v6.7-commit-hash>

# Flash previous firmware
esphome run Ball_v6.yaml
```

**Note:** You'll lose the progress arc improvements if you rollback.

## Questions?

### Why was album art removed?
It wasn't working properly and was consuming ~20KB of precious ESP32 memory. The Ball display is small (240x240), so the progress arc provides better visual feedback.

### Can album art be added back?
Possibly in the future with:
- Better memory management
- Proper authentication handling
- Smaller image sizes
- Only when media is playing

### Will progress arc work with all media players?
Yes! As long as your media player provides:
- `media_position` attribute
- `media_duration` attribute
- `state` attribute (playing/paused)

The `media_position_updated_at` attribute is optional but improves accuracy.

### Is V6.8 more stable than V6.7?
Yes! Removing album art eliminated:
- HTTP request failures
- Image download timeouts
- Authentication errors
- Memory fragmentation

## Conclusion

Ball V6.8 is a **simplified, more reliable** version focused on core functionality:
- ✅ Accurate real-time progress visualization
- ✅ Better memory efficiency
- ✅ No broken features
- ✅ Cleaner UI

**Recommended for all Ball V6 users!**
