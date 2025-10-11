# Quick Start Guide: Album Art Authentication

## 🎯 Problem You're Solving

Album art not showing on your Xiaozhi Ball? Getting blank images or errors in logs?

**The issue:** Home Assistant requires authentication to access album art images. Without it, you get **401 Unauthorized** errors.

**The solution:** Add a long-lived access token to authenticate your ESPHome device.

---

## ⚡ Quick Setup (5 Minutes)

### Step 1: Create Token in Home Assistant (2 min)

1. Open Home Assistant in your browser
2. Click **Profile Icon** (bottom left) → **Profile**
3. Scroll to **Long-Lived Access Tokens**
4. Click **Create Token**
5. Name it: `ESPHome Display` (or any name)
6. **Copy the token** → You won't see it again!

   Example token:
   ```
   eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJhYmNkZWYxMjM0NTY3ODkwIiwiaWF0IjoxNjg5MDAwMDAwLCJleHAiOjIwMDQzNjAwMDB9.abcdefghijklmnopqrstuvwxyz1234567890
   ```

### Step 2: Add Token to Configuration (1 min)

1. Open your `Ball_v6.yaml` (or v5.3, v5.4, v6.2)
2. Find the **substitutions** section at the top
3. Look for this line:
   ```yaml
   ha_token: "YOUR_TOKEN_HERE"
   ```
4. Replace `YOUR_TOKEN_HERE` with your actual token:
   ```yaml
   ha_token: "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9..."
   ```

### Step 3: Flash Updated Config (2 min)

1. Save the YAML file
2. In ESPHome dashboard, click **Install** on your Ball device
3. Wait for compilation and flashing
4. Device will reboot automatically

### Step 4: Test It! (30 sec)

1. Start playing music on your media player
2. Navigate to media screen on your Ball device
3. **Album art should appear within 5-10 seconds!** 🎉

---

## ✅ Quick Verification

### It's Working If:
- ✅ Album art appears on media screen
- ✅ Art updates when you change tracks
- ✅ No errors in ESPHome logs
- ✅ Different media sources all show art (Spotify, YouTube Music, etc.)

### Still Not Working?

#### Check 1: Token Format
```yaml
# ✅ CORRECT - Plain token string
ha_token: "eyJ0eXAiOiJKV1QiL..."

# ❌ WRONG - Extra quotes or spaces
ha_token: ""eyJ0eXAiOiJKV1QiL...""
ha_token: " eyJ0eXAiOiJKV1QiL... "
```

#### Check 2: ESPHome Logs
In ESPHome, click **Logs** for your device and look for:
```
✅ Good: "Image downloaded successfully"
❌ Bad: "401 Unauthorized"
❌ Bad: "HTTP request failed"
```

#### Check 3: Home Assistant URL
If using IP address instead of `homeassistant.local`:
```yaml
# Find this line in the YAML (around line 1274 for v6)
url = "http://homeassistant.local:8123" + x + "?authSig=" + token;

# Change to your HA IP:
url = "http://192.168.1.100:8123" + x + "?authSig=" + token;
```

#### Check 4: Media Player Has Album Art
1. In Home Assistant: **Developer Tools** → **States**
2. Find your media player entity
3. Look for `entity_picture` attribute
4. If missing, your media source doesn't provide album art

---

## 🔒 Security Tips

### Keep Your Token Safe
- ✅ Don't commit token to public Git repos
- ✅ Don't share config files with token
- ✅ Use Home Assistant secrets if sharing code
- ✅ Revoke and recreate if compromised

### Example with Secrets (Optional)
```yaml
# In secrets.yaml
ha_access_token: "eyJ0eXAiOiJKV1QiL..."

# In Ball_v6.yaml
ha_token: !secret ha_access_token
```

---

## 📱 Which Versions Need This?

| Version | Needs Token? | Status |
|---------|--------------|--------|
| Ball v6 | ✅ Yes | Updated |
| Ball v6.2 | ✅ Yes | Updated |
| Ball v5.4 | ✅ Yes | Updated |
| Ball v5.3 | ✅ Yes | Updated |
| Ball v5.2 | ❌ No | Different implementation |
| Older | ❌ No | No album art support |

---

## 🎵 Supported Media Sources

Works with any Home Assistant media player that provides `entity_picture`:

- ✅ **Spotify** - Full support, best quality
- ✅ **YouTube Music** - Full support
- ✅ **Plex** - Full support with local/remote media
- ✅ **Apple Music** - If integrated via HA
- ✅ **Google Cast** - Shows casting app's art
- ✅ **Local Media** - If metadata includes art
- ✅ **Sonos** - Full support
- ✅ **MPD/Mopidy** - If configured with art

---

## 🐛 Common Issues & Fixes

### Issue: "401 Unauthorized" in logs
**Fix:** Token is missing, incorrect, or expired
- Recreate token in Home Assistant
- Copy it carefully (no spaces)
- Update YAML and reflash

### Issue: Album art shows briefly then disappears
**Fix:** Network/timeout issue
- Increase `http_request` timeout in YAML:
  ```yaml
  http_request:
    timeout: 20s  # Was 10s
  ```

### Issue: Some albums show art, others don't
**Fix:** This is normal - depends on media source
- Not all tracks have album art
- Some sources provide higher quality art
- ESPHome resizes to 100x100 automatically

### Issue: Token in logs (security concern)
**Fix:** ESPHome doesn't log tokens by default
- If you see it, you may have debug logging enabled
- Check your `logger:` configuration
- Tokens are safe in device memory

---

## 📚 More Help

- **Full Documentation:** See `ALBUM_ART_AUTH_FIX.md`
- **Technical Details:** See `ALBUM_ART_IMPLEMENTATION.md`
- **Version Changes:** See `CHANGES_V6.3.md` (or relevant version)

---

## 🎉 That's It!

Your album art should now be working! Enjoy your Xiaozhi Ball with full media player functionality.

**Questions?** Check the troubleshooting section above or the full documentation files.
