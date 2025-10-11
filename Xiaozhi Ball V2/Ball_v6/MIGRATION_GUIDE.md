# Migration Guide: Adding Album Art Authentication

## 📋 Overview

This guide helps you migrate your existing Ball configuration to support authenticated album art fetching.

**Time Required:** 5-10 minutes  
**Difficulty:** Easy  
**Breaking Changes:** None (requires token addition)

---

## 🎯 Who Needs This?

If you're using:
- Ball v6 or v6.2
- Ball v5.3 or v5.4
- Any version with album art support

And experiencing:
- ❌ Album art not displaying
- ❌ 401 Unauthorized errors in logs
- ❌ Blank media screen images

---

## 📝 What Changed?

### Summary
Album art URLs now require a Home Assistant authentication token to access protected endpoints.

### Technical Changes
Two small additions to your YAML file:
1. New `ha_token` substitution variable
2. Updated lambda function to append token to URLs

---

## 🔄 Migration Steps

### Step 1: Get Your Token (2 minutes)

1. Open **Home Assistant**
2. Click **Profile** (bottom left)
3. Scroll to **Long-Lived Access Tokens**
4. Click **Create Token**
5. Name: `ESPHome Display`
6. **Copy the token** (save it somewhere safe)

Example token:
```
eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJhYmNkZWYxMjM0NTY3ODkwIiwiaWF0IjoxNjg5MDAwMDAwLCJleHAiOjIwMDQzNjAwMDB9.abcdefghijklmnopqrstuvwxyz1234567890
```

### Step 2: Update Your YAML (3 minutes)

#### Change 1: Add Token to Substitutions

Find the substitutions section at the top of your file (around line 28):

**Before:**
```yaml
substitutions:
  name: ball_v6
  friendly_name: "Ball V6"
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
```

**After:**
```yaml
substitutions:
  name: ball_v6
  friendly_name: "Ball V6"
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
  
  # Home Assistant long-lived access token for album art authentication
  ha_token: "eyJ0eXAiOiJKV1QiLC..."  # Your actual token here
```

#### Change 2: Update Lambda Function

Find the `ha_media_picture` sensor (around line 1260 in v6):

**Before:**
```yaml
- platform: homeassistant
  id: ha_media_picture
  entity_id: ${media_player_entity}
  attribute: entity_picture
  on_value:
    - lambda: |-
        if (x.length() > 0 && x[0] == '/') {
          auto url = "http://homeassistant.local:8123" + x;
          id(album_art_image).set_url(url.c_str());
          id(album_art_image).update();
        } else if (x.length() > 0) {
          id(album_art_image).set_url(x.c_str());
          id(album_art_image).update();
        }
```

**After:**
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

### Step 3: Flash Your Device (2 minutes)

1. Save the YAML file
2. In ESPHome dashboard, click **Install**
3. Choose your preferred method (OTA, USB, etc.)
4. Wait for compilation and upload
5. Device will reboot automatically

### Step 4: Verify It Works (1 minute)

1. Start playing music
2. Navigate to media screen
3. **Album art should appear!** ✅

---

## 🔍 What Each Change Does

### Addition 1: `ha_token` Substitution
```yaml
ha_token: "YOUR_TOKEN_HERE"
```
- Stores your authentication token
- Used throughout the configuration via `${ha_token}`
- Keeps token in one place for easy management

### Addition 2: Token in Lambda
```cpp
std::string token = "${ha_token}";
```
- Retrieves the token from substitutions
- Makes it available to the URL builder

### Addition 3: URL Authentication
```cpp
url = "http://homeassistant.local:8123" + x + "?authSig=" + token;
```
- Appends token as a URL parameter
- Format: `?authSig=YOUR_TOKEN`
- Authenticates with Home Assistant API

### Addition 4: Empty URL Handling
```cpp
else {
  id(album_art_image).set_url("");
  id(album_art_image).update();
}
```
- Explicitly clears image when no media playing
- Prevents showing old album art
- Cleaner UI experience

---

## 📊 Version-Specific Line Numbers

| Version | Token Location | Lambda Location |
|---------|---------------|-----------------|
| Ball v6 | Line ~34 | Lines ~1269-1283 |
| Ball v6.2 | Line ~34 | Lines ~1280-1295 |
| Ball v5.4 | Line ~34 | Lines ~1144-1159 |
| Ball v5.3 | Line ~34 | Lines ~1144-1159 |

---

## ⚠️ Common Migration Issues

### Issue 1: "Unknown variable 'ha_token'"

**Cause:** Forgot to add `ha_token` to substitutions  
**Fix:** Add the token substitution (see Change 1 above)

### Issue 2: Album art still not showing

**Cause:** Token might be incorrect  
**Fix:**
1. Verify token copied correctly (no spaces)
2. Check token still exists in Home Assistant
3. Try creating a new token

### Issue 3: ESPHome won't compile

**Cause:** Syntax error in YAML  
**Fix:**
1. Check indentation (use spaces, not tabs)
2. Ensure quotes around token value
3. Validate YAML syntax

### Issue 4: "401 Unauthorized" still in logs

**Cause:** Token not being sent or invalid  
**Fix:**
1. Verify `${ha_token}` used in lambda (not `$ha_token`)
2. Check token is valid in Home Assistant
3. Ensure no extra quotes in substitution

---

## 🔒 Security Notes

### Token Storage
- Token is stored in YAML configuration
- Same security as entity IDs and passwords
- Not exposed in logs by default

### Token Management
- Create dedicated token for ESPHome
- Name it descriptively: "ESPHome Display"
- Can revoke and recreate anytime
- Consider using ESPHome secrets for Git

### Example with Secrets (Optional)
```yaml
# secrets.yaml
ha_token: "eyJ0eXAiOiJKV1QiLC..."

# Ball_v6.yaml
substitutions:
  ha_token: !secret ha_token
```

---

## ✅ Migration Checklist

Use this checklist to ensure you've completed all steps:

- [ ] Created long-lived token in Home Assistant
- [ ] Copied token to safe location
- [ ] Added `ha_token` substitution to YAML
- [ ] Updated lambda function with new code
- [ ] Saved YAML file
- [ ] Validated YAML syntax
- [ ] Compiled configuration successfully
- [ ] Flashed device via ESPHome
- [ ] Device rebooted and reconnected
- [ ] Tested album art display
- [ ] Verified art updates with track changes
- [ ] No errors in ESPHome logs
- [ ] Documented token location (for future reference)

---

## 📚 Additional Resources

| Resource | Purpose |
|----------|---------|
| `QUICK_START_ALBUM_ART.md` | Fast setup guide |
| `ALBUM_ART_AUTH_FIX.md` | Detailed explanation |
| `ALBUM_ART_IMPLEMENTATION.md` | Technical documentation |
| `PR_SUMMARY.md` | Complete change summary |

---

## 🆘 Still Having Issues?

### Debug Steps

1. **Check ESPHome logs:**
   ```
   # Look for these:
   ✅ "Image downloaded successfully"
   ❌ "401 Unauthorized"
   ❌ "HTTP request failed"
   ```

2. **Test URL manually:**
   - Get `entity_picture` from HA Developer Tools
   - Build full URL with token
   - Try in browser:
     ```
     http://homeassistant.local:8123/api/media_player_proxy/...?authSig=YOUR_TOKEN
     ```

3. **Verify token validity:**
   - Check token exists in HA profile
   - Try creating a new token
   - Test with curl:
     ```bash
     curl -H "Authorization: Bearer YOUR_TOKEN" \
          http://homeassistant.local:8123/api/
     ```

### Get Help

If you're still stuck:
1. Check troubleshooting in `QUICK_START_ALBUM_ART.md`
2. Review `ALBUM_ART_AUTH_FIX.md` for detailed help
3. Verify your Home Assistant version supports tokens (2018.7+)

---

## 🎉 Success!

Once you see album art on your media screen, you're done! Enjoy your fully functional Xiaozhi Ball with authenticated album art support.

**Next:** Check out other Ball features in the main README files.

---

**Migration Complete** ✅  
**Time Spent:** ~10 minutes  
**Result:** Working album art with authentication  
**Effort:** Minimal changes, maximum impact
