# Album Art Token Authentication - Ball V6

## Overview

Ball V6 now supports **Home Assistant Long-Lived Access Token authentication** for album art display. This enhancement improves reliability when fetching album artwork from the Home Assistant media player proxy API.

## Why Use Token Authentication?

### Benefits:
- ✅ **More Reliable**: Works with Home Assistant instances that require authentication
- ✅ **Secure**: Proper authentication for accessing media resources
- ✅ **Flexible**: Works with both local and remote Home Assistant instances
- ✅ **Optional**: Still works without token for local, unauthenticated setups

### When You Need It:
- Your Home Assistant requires authentication
- You're accessing HA over the internet (external URL)
- Album art fails to load with basic URL
- You have authentication enabled on your HA instance

### When You Don't Need It:
- Local network access without authentication
- Home Assistant accessible without login
- Already working album art without token

---

## Configuration

### 1. Basic Setup (No Token)

If your Home Assistant is on the local network without authentication:

```yaml
substitutions:
  # ... other entities ...
  
  # Home Assistant base URL
  ha_base_url: "http://homeassistant.local:8123"
  
  # Leave token empty for local unauthenticated access
  ha_token: ""
```

### 2. With Token Authentication (Recommended)

For authenticated or remote access:

```yaml
substitutions:
  # ... other entities ...
  
  # Your Home Assistant base URL
  ha_base_url: "https://your-ha.duckdns.org"  # or http://192.168.1.100:8123
  
  # Long-lived access token
  ha_token: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.your_actual_token_here"
```

---

## How to Get Your Home Assistant Token

### Step 1: Access Your Profile
1. Open Home Assistant
2. Click on your username (bottom left corner)
3. Scroll down to **"Long-Lived Access Tokens"**

### Step 2: Create Token
1. Click **"Create Token"**
2. Enter a name: `ESPHome Ball V6 Album Art`
3. Click **"OK"**

### Step 3: Copy Token
1. **IMPORTANT**: Copy the token immediately - it's only shown once!
2. Token looks like: `eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...` (very long string)
3. Save it securely

### Step 4: Add to Configuration
Paste the token in the `ha_token` substitution in Ball_v6.yaml:

```yaml
ha_token: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.your_token_here"
```

---

## How It Works

### URL Construction

The system automatically constructs the proper URL based on your configuration:

#### Without Token:
```
http://homeassistant.local:8123/api/media_player_proxy/media_player.spotify
```

#### With Token:
```
http://homeassistant.local:8123/api/media_player_proxy/media_player.spotify?access_token=YOUR_TOKEN
```

### Smart URL Handling

The implementation intelligently handles different URL scenarios:

1. **Relative URLs** (from HA media player proxy):
   - Detected by leading `/` character
   - Prepends base URL
   - Adds token if provided
   - Example: `/api/media_player_proxy/...` → Full URL with auth

2. **Absolute URLs** (direct from service like Spotify):
   - Used as-is without modification
   - No token added (not needed for external sources)
   - Example: `https://i.scdn.co/image/...` → Used directly

3. **Query Parameter Handling**:
   - If URL already has `?` → appends `&access_token=...`
   - If URL has no `?` → appends `?access_token=...`

---

## Troubleshooting

### Album Art Still Not Displaying

#### 1. Check Token Validity
```bash
# Test token with curl
curl -H "Authorization: Bearer YOUR_TOKEN" \
     http://homeassistant.local:8123/api/
```

Should return JSON with HA version info.

#### 2. Verify Base URL
- Test URL in browser: `http://homeassistant.local:8123`
- Should load Home Assistant UI
- Use IP address if hostname doesn't resolve

#### 3. Check Media Player
In Home Assistant Developer Tools → States:
```yaml
entity_id: media_player.your_player
attributes:
  entity_picture: /api/media_player_proxy/media_player.your_player
```

Verify `entity_picture` attribute exists.

#### 4. ESPHome Logs
Monitor ESPHome logs for HTTP errors:
```bash
esphome logs Ball_v6.yaml
```

Look for:
- `Failed to download image`
- `HTTP error 401` (authentication failed)
- `HTTP error 404` (URL not found)

---

## Configuration Examples

### Example 1: Local Home Assistant (No Auth)
```yaml
substitutions:
  light_entity: "light.living_room"
  media_player_entity: "media_player.spotify"
  weather_entity: "weather.home"
  ha_base_url: "http://homeassistant.local:8123"
  ha_token: ""
```

### Example 2: Local with IP and Token
```yaml
substitutions:
  light_entity: "light.bedroom"
  media_player_entity: "media_player.sonos_living_room"
  weather_entity: "weather.forecast_home"
  ha_base_url: "http://192.168.1.50:8123"
  ha_token: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
```

### Example 3: Remote HTTPS with Token
```yaml
substitutions:
  light_entity: "light.office"
  media_player_entity: "media_player.youtube_music"
  weather_entity: "weather.home"
  ha_base_url: "https://myhome.duckdns.org"
  ha_token: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
```

---

## Security Best Practices

### 1. Token Storage
- ✅ **DO**: Store token in secrets.yaml (if using secrets)
- ✅ **DO**: Use unique tokens for each device
- ❌ **DON'T**: Share tokens publicly
- ❌ **DON'T**: Commit tokens to public repositories

### 2. Token Management
- Create descriptive token names
- Revoke old tokens when not needed
- Regenerate tokens periodically
- Monitor token usage in HA logs

### 3. Using secrets.yaml (Optional)
Move sensitive data to secrets.yaml:

**Ball_v6.yaml:**
```yaml
substitutions:
  ha_base_url: !secret ha_base_url
  ha_token: !secret ha_token
```

**secrets.yaml:**
```yaml
ha_base_url: "http://192.168.1.50:8123"
ha_token: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
```

---

## Technical Details

### Implementation

The album art sensor monitors the `entity_picture` attribute from the media player:

```cpp
// Simplified code snippet
if (url_starts_with_slash) {
  std::string full_url = ha_base_url + url;
  if (ha_token_not_empty) {
    full_url += has_query_params ? "&access_token=" : "?access_token=";
    full_url += ha_token;
  }
  download_and_display(full_url);
}
```

### Supported Media Players

Works with any Home Assistant media player that provides `entity_picture`:

- ✅ Spotify
- ✅ YouTube Music
- ✅ Plex
- ✅ Apple Music
- ✅ Google Cast
- ✅ Sonos
- ✅ Any media_player with album art support

---

## Migration from Previous Versions

### From Ball V6.0-V6.2

Previous versions used hardcoded `http://homeassistant.local:8123`:

**Old:**
```yaml
# No configuration - URL hardcoded in lambda
```

**New:**
```yaml
substitutions:
  ha_base_url: "http://homeassistant.local:8123"
  ha_token: ""  # Add token if needed
```

### No Breaking Changes
- Default values match previous behavior
- Existing setups work without modification
- Token is optional enhancement

---

## Progress Arc Real-Time Updates

Ball V6 includes **real-time progress arc** functionality that shows playback position:

### Features:
- ✅ Circular arc around album art
- ✅ Updates in real-time as media plays
- ✅ Green indicator (Spotify green: #1DB954)
- ✅ Automatic reset when track changes

### How It Works:
```yaml
# Automatically configured sensors:
- ha_media_position (tracks current position)
- ha_media_duration (tracks total duration)
- Calculates: (position / duration) * 100%
- Updates media_progress_arc widget
```

### Visual Result:
```
┌─────────────┐
│   ◕ Art     │  ← Green arc fills as song plays
│   Song      │
│   Artist    │
└─────────────┘
```

---

## Summary

✅ **Token authentication added** - Optional but recommended  
✅ **Progress arc working** - Real-time playback position  
✅ **Backward compatible** - Existing configs work unchanged  
✅ **Well documented** - Clear setup instructions  
✅ **Secure** - Proper authentication support  
✅ **Flexible** - Works with/without token  

---

## Support

### Common Issues:
1. **Token not working** → Regenerate token in HA
2. **Album art blank** → Check entity_picture attribute exists
3. **HTTP errors** → Verify base_url and network connectivity
4. **Progress arc at 0%** → Ensure media is actually playing

### Getting Help:
- Check ESPHome logs: `esphome logs Ball_v6.yaml`
- Verify HA connectivity: `ping homeassistant.local`
- Test media player: Home Assistant → Media Control
- Review documentation: ALBUM_ART_IMPLEMENTATION.md

---

**Version**: Ball V6.7  
**Last Updated**: 2025-10-11  
**Feature**: Album Art Token Authentication + Progress Arc
