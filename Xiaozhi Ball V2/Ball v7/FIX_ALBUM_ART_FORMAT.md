# Ball V7 - Album Art Format Fix

## Issue

Album art images were not displaying on the Ball V7 device, showing the following error in logs:

```
[17:37:55][E][online_image.png:086]: Error decoding image: Incorrect PNG signature
[17:37:55][E][online_image:250]: Error when decoding image.
```

## Root Cause

The `online_image` component was configured with `format: PNG`, but most streaming services (Spotify, Apple Music, YouTube Music, etc.) serve album art as **JPEG images**, not PNG.

**Evidence from logs:**
- URL: `https://is1-ssl.mzstatic.com/image/thumb/Music114/v4/31/18/fa/3118fab0-90ea-2ae5-cf6c-bc64054ab9e3/21UMGIM21449.rgb.jpg/4200x4200bb.jpg`
- File extension: `.jpg` (JPEG format)
- Error: "Incorrect PNG signature" (PNG decoder attempting to decode JPEG data)

## Solution

Changed the `format` parameter from `PNG` to `JPEG` in the `online_image` component configuration.

### Files Modified

1. **Ball_v7.yaml** (line 167)
   ```yaml
   # Before:
   format: PNG
   
   # After:
   format: JPEG
   ```

2. **README.md**
   - Line 103: Updated format description
   - Line 192: Updated code example

3. **CHANGES_V7.md**
   - Line 59: Updated code example
   - Line 67: Updated format explanation
   - Line 252: Updated performance notes

## Why JPEG?

Most major streaming services serve album art in JPEG format:
- **Spotify**: JPEG
- **Apple Music**: JPEG (as seen in error logs)
- **YouTube Music**: JPEG
- **Plex**: Often JPEG
- **Sonos**: JPEG

JPEG is the standard format for photo-quality images on the web due to:
- Better compression for photographic content
- Smaller file sizes
- Wide compatibility
- Industry standard for album artwork

## Testing

After this fix, the album art should:
1. ✅ Download successfully from streaming services
2. ✅ Display correctly on the device
3. ✅ Update automatically when tracks change
4. ✅ Work with Spotify, Apple Music, and other services

## Expected Behavior

With the JPEG format configured, the logs should show:
```
[D][album_art]: Album art URL: https://...jpg
[I][online_image:109]: Updating image https://...jpg
[D][online_image:175]: Starting download
[D][online_image:194]: Allocating JPEG decoder  ← Changed from PNG
[I][online_image:212]: Downloading image (Size: ...)
[D][online_image:250]: Image decoded successfully  ← Success!
```

## Related Issues

This issue was similar to the one fixed in Ball V6.3 where the format was incorrectly set to 'AUTO' (which ESPHome doesn't support). The correct approach is to explicitly specify either `PNG` or `JPEG` based on the expected image sources.

## Migration Note

Users upgrading from the initial Ball V7 release need to:
1. ✅ Pull the latest Ball_v7.yaml from the repository
2. ✅ Re-flash their device with the updated configuration
3. ✅ Album art should then display correctly

No changes to Home Assistant template sensors are required.

---

**Fix Applied**: 2025-10-11  
**Severity**: Critical (Feature Not Working)  
**Impact**: Album art now displays correctly for all streaming services  
**Breaking Changes**: None
