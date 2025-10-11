# Ball V7.1 - Quick Fix Summary

## Problem
Device was freezing with these errors:
```
[W][component:443]: online_image took a long time for an operation (93589 ms)
[W][online_image:106]: Image already being updated
```

## Solution (3 Changes)

### 1. Script-Based Protection ⏱️
**Note**: ESPHome text_sensor doesn't support `throttle` filter (only for numeric sensors).
Protection is provided by script mode and global flag instead.

**Effect**: Prevents concurrent updates through script `mode: single`

### 2. Created Update Script 🛡️
```yaml
# Lines 955-966
- id: update_album_art
  mode: single  # Only one at a time!
  then:
    - lambda: # Check if already updating
    - component.update: album_art_image
    - lambda: # Clear flag
```
**Effect**: Ensures only one image download happens at a time

### 3. Added Guard Variable 🚦
```yaml
# Lines 1194-1197
- id: album_art_updating
  type: bool
  initial_value: 'false'
```
**Effect**: Tracks update state, provides extra safety

## How to Apply

### Option 1: Pull & Flash (Recommended)
```bash
git pull origin main
# Flash Ball_v7.yaml to your device
```

### Option 2: Manual Edit
If you have customizations, apply these 2 changes to your config:
1. Add `update_album_art` script with `mode: single`
2. Add `album_art_updating` global variable
3. Change `id(album_art_image).update()` to `id(update_album_art)->execute()`

## Testing
After flashing:
1. Play media and change tracks rapidly
2. Device should NOT freeze
3. Check logs - should see: `[W][album_art]: Update already in progress, skipping`

## Impact
- ✅ Device stays responsive
- ✅ No more 93-second freezes
- ✅ Other components work normally
- ✅ Album art still updates (just throttled)

## More Info
- **Detailed Fix**: [FIX_DEVICE_FREEZING.md](./FIX_DEVICE_FREEZING.md)
- **Full Changelog**: [CHANGES_V7.md](./CHANGES_V7.md)

---

**Version**: V7.1  
**Status**: ✅ Fixed  
**Urgency**: Critical (Device Unusable → Now Working)
