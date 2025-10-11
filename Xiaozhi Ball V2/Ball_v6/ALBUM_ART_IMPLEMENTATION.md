# Album Art Implementation in Ball V6

## Overview
Ball V6 implements album art display using the standard Home Assistant media player integration approach, as documented in the official Home Assistant and ESPHome documentation.

## Implementation Details

### Authentication Requirement

**IMPORTANT**: Home Assistant's album art endpoints (like `/api/media_player_proxy/...`) are protected and require authentication. Without a valid access token, ESPHome will receive **401 Unauthorized** responses and album art won't display.

#### Setting Up Authentication Token

1. **Create a Long-Lived Access Token in Home Assistant**:
   - Click your **Profile icon** (bottom left in Home Assistant)
   - Scroll to **Long-Lived Access Tokens**
   - Click **Create Token**
   - Name it `ESPHome Display` (or any name you prefer)
   - **Copy the token immediately** (you won't see it again!)

2. **Add Token to Configuration**:
   - In `Ball_v6.yaml`, find the substitutions section at the top
   - Replace `YOUR_TOKEN_HERE` with your actual token:
   ```yaml
   ha_token: "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9..."  # Your actual token here
   ```

3. **How It Works**:
   - The token is appended to image URLs as `?authSig=YOUR_TOKEN`
   - This authenticates the ESPHome device with Home Assistant
   - Album art images can now be fetched from protected endpoints

### Components Required

1. **HTTP Request Component** (line 154-155)
   ```yaml
   http_request:
     timeout: 10s
   ```
   - Required by ESPHome to make HTTP requests
   - Fetches images from Home Assistant

2. **Online Image Component** (line 158-164)
   ```yaml
   online_image:
     - id: album_art_image
       url: "http://homeassistant.local:8123/"
       type: RGB565
       format: PNG
       resize: 100x100
       update_interval: never
   ```
   - Downloads and caches album art images
   - RGB565 format for memory efficiency on ESP32
   - 100x100 resolution fits the circular display layout
   - Manual update triggered when media changes

3. **Entity Picture Sensor** (line 1256-1269)
   ```yaml
   - platform: homeassistant
     id: ha_media_picture
     entity_id: ${media_player_entity}
     attribute: entity_picture
     on_value:
       - lambda: |-
           std::string token = "${ha_token}";
           if (x.length() > 0) {
             std::string url;
             if (x[0] == '/') {
               url = "http://homeassistant.local:8123" + x + "?authSig=" + token;
             } else {
               url = x + "?authSig=" + token;
             }
             id(album_art_image).set_url(url.c_str());
             id(album_art_image).update();
           } else {
             id(album_art_image).set_url("");
             id(album_art_image).update();
           }
   ```
   - Monitors the `entity_picture` attribute from the media player
   - Converts relative URLs (starting with `/`) to absolute URLs
   - **Appends authentication token to all image URLs**
   - Handles both relative and absolute URL formats
   - Updates the image when media changes
   - Clears image URL when no media is playing

4. **Display Widget** (line 1403-1410)
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
   - Displays the album art on screen
   - Rounded corners (10px radius)
   - Visual border for better presentation

## How It Works

### According to Home Assistant Documentation
(https://www.home-assistant.io/integrations/media_player/)

The `entity_picture` attribute is the standard way to access album art for media players in Home Assistant:
- It provides a URL to the album artwork
- URL can be relative (e.g., `/api/media_player_proxy/...`) or absolute
- Updates automatically when media changes
- Supported by most media player integrations (Spotify, YouTube Music, Plex, etc.)

### According to ESPHome Documentation  
(https://esphome.io/components/media_player/)

ESPHome media players and displays can fetch remote images using:
- `http_request` component for HTTP capabilities
- `online_image` for downloading and caching images
- Home Assistant sensor platform to monitor attributes
- Lambda functions to process URLs and trigger updates

## Compatibility

### Works With:
- ✅ Spotify
- ✅ YouTube Music
- ✅ Plex
- ✅ Chromecast
- ✅ Apple Music (if integrated via HA)
- ✅ Any media player that provides `entity_picture`

### Requirements:
- ESPHome 2023.7.0+ (for `online_image` platform)
- Stable WiFi connection
- Home Assistant on same network
- Media player integration that provides album art

## Troubleshooting

### Album Art Not Displaying
1. **Check Authentication Token** (Most Common Issue!)
   - Verify you've created a long-lived access token in Home Assistant
   - Ensure the token is correctly copied into `ha_token` substitution
   - Check ESPHome logs for "401 Unauthorized" errors
   - If you see 401 errors, your token is missing or incorrect

2. Check that your media player provides the `entity_picture` attribute
   - In Home Assistant: Developer Tools → States → Find your media player
   - Look for `entity_picture` in attributes

3. Verify network connectivity between ESP32 and Home Assistant
   - Ping test from ESP32 to Home Assistant
   - Check ESPHome logs for HTTP errors

4. Ensure `homeassistant.local` resolves correctly (or use IP address)
   - If `.local` doesn't work, update the URL to use your HA IP address:
   ```yaml
   # Change in the lambda function around line 1263
   url = "http://192.168.1.100:8123" + x + "?authSig=" + token;
   ```

### Slow Updates
- First load may take 5-10 seconds (normal)
- Subsequent updates are faster due to caching
- Image quality depends on source resolution

### Memory Issues
- RGB565 format uses less memory than RGB888
- 100x100 resolution is optimized for ESP32 S3 BOX memory
- Larger images may cause memory issues on ESP32

## Alternative Approaches Considered

### 1. Direct Media Player Integration
**Not viable**: ESPHome media_player component doesn't support album art directly.

### 2. Camera Component
**Not recommended**: Camera component is designed for video streams, not static images.
More complex and resource-intensive than `online_image`.

### 3. Custom HTTP Requests
**Unnecessary**: `online_image` component already handles this efficiently with built-in caching and error handling.

## Conclusion

The current implementation follows the official Home Assistant and ESPHome documentation exactly. It uses:
- Standard `entity_picture` attribute (HA best practice)
- ESPHome `online_image` component (ESPHome best practice)
- Automatic updates when media changes
- Memory-efficient image format

This is the correct and recommended approach for displaying album art on ESPHome devices.
