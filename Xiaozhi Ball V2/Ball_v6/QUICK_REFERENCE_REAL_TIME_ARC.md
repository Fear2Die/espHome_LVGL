# Quick Reference: Real-Time Progress Arc

## What Changed?

The media progress arc now updates **every second** during playback instead of only when Home Assistant sends position updates.

## Before vs After

### Before (V6.6 and earlier)
```
┌─────────────────┐
│   ◯ Album       │  ← Arc frozen at 25%
│                 │     (last HA update was 10 seconds ago)
│   Song Title    │     Real position is 35%, but arc shows 25%
│                 │
└─────────────────┘
```

### After (Current)
```
┌─────────────────┐
│   ◐ Album       │  ← Arc animates smoothly to 35%
│                 │     Updates every second with real-time calculation
│   Song Title    │     Arc position matches actual playback position
│                 │
└─────────────────┘
```

## How It Works (Simple Explanation)

1. **When HA sends position** → Record the timestamp
2. **Every second** → Calculate: `real_position = HA_position + elapsed_time`
3. **Update arc** → Show calculated real-time position

### Example Timeline

```
t=0s:  HA sends position: 45.2s → Record timestamp
       Arc shows: 45.2s / 180s = 25.1%

t=1s:  Calculate: 45.2s + 1s = 46.2s
       Arc shows: 46.2s / 180s = 25.7%

t=2s:  Calculate: 45.2s + 2s = 47.2s
       Arc shows: 47.2s / 180s = 26.2%

t=5s:  Calculate: 45.2s + 5s = 50.2s
       Arc shows: 50.2s / 180s = 27.9%

t=10s: HA sends new position: 55.3s → Record new timestamp
       Arc shows: 55.3s / 180s = 30.7%
       (reset to new base, continue calculating)
```

## Key Features

### ✅ Smooth Animation
- Arc advances every second
- No jumps or freezing
- Visual feedback feels natural

### ✅ Accurate Tracking
- Position matches real playback within 1 second
- Syncs with HA updates automatically
- Handles play/pause/skip correctly

### ✅ Smart Behavior
- **Playing** → Arc advances automatically
- **Paused** → Arc stays static at current position
- **Track change** → Arc resets for new track
- **Seeking** → Arc updates to new position

### ✅ Reliable
- No timestamp conversion errors
- Graceful fallback if time not synced
- Clamps position to 0-100% range

## What You Need

### Prerequisites
1. ESPHome device with Ball V6 configuration
2. Home Assistant with media player entity
3. Time component synced from Home Assistant

### Already Configured?
If you already have Ball V6 running, just update your `Ball_v6.yaml` file with the changes and flash to your device.

## Installation

### Option 1: Fresh Install
Copy the entire `Ball_v6.yaml` file from this repository.

### Option 2: Update Existing
Apply these changes to your existing `Ball_v6.yaml`:

**1. Add global variable** (in `globals:` section):
```yaml
- id: media_position_updated_at
  type: time_t
  restore_value: no
  initial_value: '0'
```

**2. Update position sensor** (in `sensor:` section, `ha_media_position`):
Add before the existing `lvgl.arc.update`:
```yaml
on_value:
  - lambda: |-
      // Record timestamp when position is updated from HA
      auto now = id(ha_time).now();
      if (now.is_valid()) {
        id(media_position_updated_at) = now.timestamp;
      }
  - lvgl.arc.update:
      # ... existing code
```

**3. Add time trigger** (in `time:` section, `on_time:`):
```yaml
# Update progress arc every second for real-time animation
- seconds: '*'
  then:
    - lvgl.arc.update:
        id: media_progress_arc
        value: !lambda |-
          // Get base position and other values
          float base_position = id(ha_media_position).state;
          float duration = id(ha_media_duration).state;
          time_t updated_at = id(media_position_updated_at);
          
          // Check if media is playing
          std::string state = id(ha_media_state).state;
          bool is_playing = (state == "playing");
          
          // Calculate real-time position
          float current_position = base_position;
          if (is_playing && updated_at > 0) {
            // Get current timestamp and calculate elapsed time
            auto now = id(ha_time).now();
            if (now.is_valid()) {
              time_t current_timestamp = now.timestamp;
              float elapsed = current_timestamp - updated_at;
              current_position = base_position + elapsed;
            }
          }
          
          // Calculate and return percentage
          if (duration > 0 && !std::isnan(current_position) && !std::isnan(duration)) {
            float percentage = (current_position / duration) * 100.0;
            // Clamp to 0-100 range
            if (percentage < 0) percentage = 0;
            if (percentage > 100) percentage = 100;
            return percentage;
          } else {
            return 0;
          }
```

## Testing

### Quick Test (30 seconds)
1. Play music on your media player
2. Navigate to media screen on Ball V6
3. Watch the arc for 10 seconds
4. **Expected**: Arc advances smoothly every second

### Full Test (5 minutes)
1. ✅ Play media → Arc animates smoothly
2. ✅ Pause media → Arc stops at current position
3. ✅ Resume → Arc continues from paused position
4. ✅ Skip track → Arc resets and animates for new track
5. ✅ Compare with HA → Arc position matches HA position

## Troubleshooting

### Arc not updating
**Check**: Is time synced?
```
# In ESPHome logs, look for:
[time:XXX]: Synchronized time: YYYY-MM-DD HH:MM:SS
```

**Solution**: Wait for time sync from Home Assistant

### Arc position wrong
**Check**: Is media state correct?
```
# In ESPHome logs, look for media_state sensor
```

**Solution**: Verify media player entity is configured correctly

### Arc jumps around
**Check**: Are position updates coming through?
```
# In ESPHome logs, look for:
[sensor:XXX]: 'ha_media_position': Got value X.X
```

**Solution**: Check Home Assistant media player is working

### Arc stuck at 0%
**Check**: Duration sensor value
```
# If duration is 0 or NaN, arc will show 0%
```

**Solution**: Verify media has duration metadata

## Performance

### Resource Usage
- **Memory**: +8 bytes (one timestamp variable)
- **CPU**: Minimal (simple math every second)
- **Network**: No change (same HA updates)

### Battery Impact
Negligible - one timer per second is very lightweight

## FAQ

### Q: Does this use more battery?
**A**: No significant impact. The calculation runs once per second and is very simple.

### Q: Will this work with Spotify/YouTube Music/etc?
**A**: Yes, works with any media player that reports position and duration to Home Assistant.

### Q: What if my network is slow?
**A**: No problem! The arc uses the last known position and calculates from there. Network latency doesn't affect smoothness.

### Q: Does this need internet?
**A**: Only needs connection to Home Assistant (local network). No internet required for the arc animation itself.

### Q: Can I adjust the update frequency?
**A**: Yes, but not recommended. Change `seconds: '*'` to different interval if needed, but 1 second is optimal for smooth animation.

### Q: Will this conflict with other timers?
**A**: No, ESPHome handles multiple timers without conflict.

## Version Info

- **Introduced**: Ball V6.10 (this update)
- **Based on**: V6.5 and V6.8 implementations
- **Fixes**: Timestamp conversion errors from previous versions
- **Status**: Stable, ready for production use

## Related Documentation

- [`CHANGES_REAL_TIME_ARC.md`](CHANGES_REAL_TIME_ARC.md) - Detailed technical changes
- [`TEST_REAL_TIME_ARC.md`](TEST_REAL_TIME_ARC.md) - Implementation validation and test cases
- [`Ball_v6.yaml`](Ball_v6.yaml) - Complete configuration file

## Support

If you encounter issues:
1. Check ESPHome logs for errors
2. Verify time is synced from Home Assistant
3. Confirm media player entity is working in HA
4. Review the troubleshooting section above

## Summary

✅ **What it does**: Updates progress arc every second during playback  
✅ **How it works**: Calculates elapsed time since last HA update  
✅ **Why it's better**: Smooth animation, accurate position, no freezing  
✅ **What you need**: Updated Ball_v6.yaml and flash to device  
✅ **Impact**: Minimal resources, maximum user experience improvement
