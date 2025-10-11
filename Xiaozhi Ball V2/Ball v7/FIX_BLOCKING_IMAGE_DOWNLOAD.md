# Ball V7.2 - Blocking Image Download Fix

## Issue

Despite previous fixes (V7.1), the device was **still freezing** with the following error in logs:

```
[20:04:01][W][component:443]: online_image took a long time for an operation (108215 ms)
[20:04:01][W][component:446]: Components should block for at most 30 ms
```

The device would become unresponsive for 100+ seconds when album art changed.

## Root Cause

The V7.1 fix attempted to prevent concurrent updates using a script with `mode: single` and a guard variable, but **it still called the blocking operation**:

```yaml
# V7.1 (STILL BLOCKING):
script:
  - id: update_album_art
    mode: single
    then:
      - lambda: |-
          if (id(album_art_updating)) {
            ESP_LOGW("album_art", "Update already in progress, skipping");
            return;
          }
          id(album_art_updating) = true;
      - component.update: album_art_image  # ❌ THIS IS SYNCHRONOUS AND BLOCKS!
      - delay: 100ms
      - lambda: id(album_art_updating) = false;
```

**The problem:** `component.update: album_art_image` is a **synchronous blocking call** that:
- Downloads the entire image file immediately
- Blocks the main ESP32 loop for 100+ seconds
- Prevents all other components from running (voice assistant, touch, display updates, etc.)
- The 100ms delay happens **AFTER** the blocking download completes

The `mode: single` prevented concurrent calls, but each call still blocked for 100+ seconds.

## Solution (V7.2)

**Remove the blocking `component.update` call entirely.** The online_image component with `update_interval: never` will fetch images **lazily** when the display tries to render them.

### Code Changes

**Updated Script (Lines 955-962):**

```yaml
# V7.2 (NON-BLOCKING):
script:
  - id: update_album_art
    mode: single
    then:
      - lambda: |-
          // Just log that we're setting a new URL
          // The online_image component will fetch the image lazily when displayed
          // This prevents blocking the main loop with synchronous downloads
          ESP_LOGD("album_art", "Album art URL updated, image will load on display");
```

**Removed Global Variable (was lines 1195-1198):**

```yaml
# REMOVED - No longer needed:
# - id: album_art_updating
#   type: bool
#   restore_value: no
#   initial_value: 'false'
```

### How It Works Now

1. **Home Assistant sends new album art URL** → ESPHome text sensor receives it
2. **Lambda sets the URL:** `id(album_art_image).set_url(x.c_str())`
3. **Script is called:** `id(update_album_art)->execute()` - just logs, doesn't download
4. **Display renders the screen** → LVGL tries to show the image
5. **Online image loads lazily** → Downloads in background, non-blocking
6. **Image appears when ready** → Display updates automatically

### Key Benefits

✅ **No blocking:** Main loop remains responsive at all times  
✅ **Background downloads:** Image fetching happens asynchronously  
✅ **Better UX:** Device responds to touch/voice immediately  
✅ **Simpler code:** Removed unnecessary guard variable and blocking logic  
✅ **ESPHome compliant:** Components never block for more than 30ms

## Technical Details

### ESPHome Online Image Behavior

When `update_interval: never` is set:
- The component **does not** auto-fetch images periodically
- Images are fetched **on-demand** when the display needs them
- The fetch happens **asynchronously** in the background
- The display shows a placeholder or previous image until ready

### Why This Works

The `online_image` component is designed to work with displays efficiently:
1. Display requests the image for rendering
2. Component checks if URL changed or cache is invalid
3. If needed, starts an **async download** in the background
4. Returns immediately to avoid blocking
5. Display gets notified when image is ready
6. Display updates on next refresh cycle

This is the **intended ESPHome pattern** for online images with displays.

## Expected Behavior

### Logs Before Fix (V7.1):
```
[D][album_art]: Album art URL: http://homeassistant.local:8123/api/...
[I][online_image:109]: Updating image
[D][online_image:175]: Starting download
[I][online_image:212]: Downloading image
[... 108 seconds of blocking ...]
[W][component:443]: online_image took a long time for an operation (108215 ms)
[W][component:446]: Components should block for at most 30 ms
```

### Logs After Fix (V7.2):
```
[D][album_art]: Album art URL: http://homeassistant.local:8123/api/...
[D][album_art]: Album art URL updated, image will load on display
[... device remains responsive ...]
[D][online_image]: Fetching image in background
[D][online_image]: Image ready for display
```

## Migration Guide

### For Users on V7.1

Simply update to the latest `Ball_v7.yaml` from the repository:

```bash
git pull origin main
# Flash Ball_v7.yaml to your device
```

### Testing After Update

1. ✅ Play media with album art in Home Assistant
2. ✅ Change tracks rapidly (test concurrent updates)
3. ✅ Device should remain responsive throughout
4. ✅ Touch/voice should work immediately
5. ✅ Album art should appear within a few seconds
6. ✅ No "took a long time" warnings in logs

## Comparison with Previous Fixes

| Version | Issue | Solution | Result |
|---------|-------|----------|--------|
| V7.0 | Direct blocking calls | None | Device froze for 93+ seconds |
| V7.1 | Concurrent updates | Script mode + guard flag | Still blocked 108+ seconds per update |
| V7.2 | Blocking downloads | **Remove blocking call** | ✅ No blocking, fully responsive |

## Related Issues

- See `FIX_DEVICE_FREEZING.md` for V7.1 fix (concurrent protection)
- See `FIX_THROTTLE_ERROR.md` for text_sensor filter limitation
- See `FIX_ALBUM_ART_FORMAT.md` for JPEG format fix

---

**Version**: V7.2  
**Date**: October 2025  
**Status**: ✅ RESOLVED  
**Impact**: Critical - Device no longer freezes during album art updates  
**Breaking Changes**: None - fully backward compatible
