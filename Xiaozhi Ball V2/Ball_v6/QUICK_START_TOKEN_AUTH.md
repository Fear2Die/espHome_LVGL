# Quick Start: Album Art Token Authentication

## 🚀 5-Minute Setup

### Step 1: Configure Entity IDs (Required)

Edit `Ball_v6.yaml` lines 19-26:

```yaml
substitutions:
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
```

Replace with your actual Home Assistant entity IDs.

---

### Step 2: Set Home Assistant URL (Required)

Edit lines 30:

```yaml
ha_base_url: "http://homeassistant.local:8123"
```

**Options:**
- Local hostname: `http://homeassistant.local:8123`
- Local IP: `http://192.168.1.50:8123`
- Remote HTTPS: `https://your-ha.duckdns.org`

---

### Step 3: Add Token (Optional)

#### When to Skip This Step:
- ✅ Local network access without authentication
- ✅ Home Assistant accessible without login
- ✅ Album art already works

#### When You Need This:
- ❌ Album art not loading
- ❌ Home Assistant requires authentication
- ❌ Accessing HA remotely

#### How to Get Token:

1. **Open Home Assistant**
2. **Click your profile** (bottom left corner)
3. **Scroll down** to "Long-Lived Access Tokens"
4. **Click "Create Token"**
5. **Name it**: `ESPHome Ball V6`
6. **Click "OK"**
7. **Copy the token** (shown only once!)

Token looks like:
```
eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.very_long_string_here...
```

#### Add to Configuration:

Edit line 35:

```yaml
ha_token: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.your_token_here"
```

⚠️ **Keep the quotes!** The token must be in double quotes.

---

### Step 4: Flash to Device

```bash
esphome run Ball_v6.yaml
```

Or upload via ESPHome dashboard.

---

### Step 5: Test

1. Play media with album art (Spotify, YouTube Music, etc.)
2. Swipe to media screen on Ball V6
3. Album art should appear within 5-10 seconds
4. Progress arc should animate as song plays

---

## 🔍 Troubleshooting

### Album Art Not Showing

#### Check 1: Media Player
In Home Assistant → Developer Tools → States:

```yaml
entity_id: media_player.your_player
attributes:
  entity_picture: /api/media_player_proxy/...
```

✅ `entity_picture` attribute must exist

#### Check 2: Connectivity
```bash
ping homeassistant.local
```

✅ Device must reach Home Assistant

#### Check 3: Token (if using)
```bash
curl -H "Authorization: Bearer YOUR_TOKEN" \
     http://homeassistant.local:8123/api/
```

✅ Should return JSON (not error)

#### Check 4: ESPHome Logs
```bash
esphome logs Ball_v6.yaml
```

Look for:
- `Failed to download image` → Check URL
- `HTTP error 401` → Token invalid
- `HTTP error 404` → Wrong URL

---

## 📋 Configuration Examples

### Example 1: Local Without Token (Most Common)
```yaml
substitutions:
  light_entity: "light.living_room"
  media_player_entity: "media_player.spotify"
  weather_entity: "weather.home"
  ha_base_url: "http://homeassistant.local:8123"
  ha_token: ""
```

### Example 2: Local With IP and Token
```yaml
substitutions:
  light_entity: "light.bedroom"
  media_player_entity: "media_player.sonos"
  weather_entity: "weather.home"
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

## ✅ What Works Out of the Box

Without token (local network):
- ✅ Spotify album art
- ✅ YouTube Music album art
- ✅ Plex album art
- ✅ Local media files
- ✅ Any unauthenticated HA instance

With token (authenticated/remote):
- ✅ All of the above
- ✅ Remote access via internet
- ✅ Authenticated HA instances
- ✅ HTTPS connections
- ✅ External URLs

---

## 🎯 Quick Decision Tree

```
Is album art working?
├─ YES → You're done! No token needed.
└─ NO → Continue

Is Home Assistant on local network?
├─ YES → Try without token first
│   └─ Still not working? → Add token
└─ NO (remote access) → Add token

Is Home Assistant accessible without login?
├─ YES → Try without token first
│   └─ Still not working? → Add token
└─ NO (requires auth) → Add token
```

---

## 📖 Full Documentation

For complete details, security practices, and advanced configuration:
- **ALBUM_ART_TOKEN_AUTH.md** - Complete guide
- **CHANGES_V6.7.md** - Technical details
- **README.md** - Overview

---

## 🆘 Still Need Help?

1. Check ESPHome logs: `esphome logs Ball_v6.yaml`
2. Verify entity IDs in Home Assistant
3. Test Home Assistant connectivity
4. Review token validity (if using)
5. Check full documentation (ALBUM_ART_TOKEN_AUTH.md)

---

**Version**: Ball V6.7  
**Last Updated**: 2025-10-11  
**Setup Time**: ~5 minutes
