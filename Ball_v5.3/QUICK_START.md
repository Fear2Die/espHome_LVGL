# Ball V5.3 - Quick Start Guide

## 3-Minute Setup

### Step 1: Configure Entities (1 min)

Open `Ball_v5.3.yaml` and find the substitutions section (around line 20):

```yaml
## ENTITY CONFIGURATION - SET YOUR HOME ASSISTANT ENTITIES HERE
substitutions:
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
  camera_entity: "camera.YOUR_CAMERA_ENTITY"
```

**Replace with your actual entity IDs:**

```yaml
substitutions:
  light_entity: "light.living_room_lamp"              # Your light
  media_player_entity: "media_player.living_room"     # Your media player
  weather_entity: "weather.forecast_home"             # Your weather
  camera_entity: "camera.front_door"                   # Your camera (optional)
```

**That's it!** The configuration will automatically apply to all 16+ locations in the file.

### Step 2: Setup Secrets (1 min)

```bash
cp secrets.yaml.example secrets.yaml
nano secrets.yaml
```

Add your credentials:
```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
api_encryption_key: "generate_with_esphome"
ota_password: "secure_password"
```

### Step 3: Flash Device (1 min)

```bash
esphome run Ball_v5.3.yaml
```

Choose your device and wait for flash to complete.

## Done! 🎉

Your device now has:
- ✅ Light control with brightness slider
- ✅ Media player with controls
- ✅ Weather display
- ✅ Camera page
- ✅ Voice assistant

## Finding Your Entity IDs (Quick Reference)

### In Home Assistant Web UI

**Lights:**
1. Settings → Devices & Services
2. Click your light device
3. Copy entity ID (starts with `light.`)

**Media Players:**
1. Media → Click player icon
2. More info → Settings (gear) → Copy entity ID
3. Or just look at the URL: `media_player.xxxxx`

**Weather:**
1. Settings → Integrations → Find "Weather"
2. Click the weather entity
3. Copy entity ID (starts with `weather.`)

**Camera:**
1. Settings → Devices → Find camera
2. Click entity → Copy ID (starts with `camera.`)

### Quick Command (Advanced)

```bash
# List all lights
ha-cli state list | grep light.

# List all media players  
ha-cli state list | grep media_player.

# List all weather
ha-cli state list | grep weather.

# List all cameras
ha-cli state list | grep camera.
```

## What's Different from Previous Versions?

### 🎯 V5.3 Improvements (NEW!)

1. **Fixed Button Overlap** ⭐
   - V5.2: Navigation buttons too close to toggle light ❌
   - V5.3: Proper spacing, no overlap ✅

2. **Live Camera Feed** ⭐
   - V5.2: Only placeholder text ❌
   - V5.3: Real camera images, updates every 10s ✅

### ✨ V5.2 Improvements

1. **Easy Configuration** (5 seconds vs 5 minutes)
   - Configure entities in ONE place
   - V5.1: Update 16 locations ❌
   - V5.2: Update 1 location ✅

2. **Fixed Media Buttons**
   - V5.1: Empty boxes (missing glyphs) ❌
   - V5.2: `<<` `>` `>>` symbols ✅

3. **Camera Page** (NEW in V5.2)
   - Quick access to security camera
   - Live feed in V5.3! ⭐

4. **Album Art** (NEW)
   - Visual placeholder on media page
   - Music note symbol

5. **No More Errors**
   - V5.1: "Can't convert 'None'" warnings ❌
   - V5.2: Handles None gracefully ✅

## First Test Checklist

After flashing, test these:

- [ ] Device appears in Home Assistant
- [ ] Light slider changes brightness
- [ ] Light toggle button works
- [ ] Tap "Media" → See media controls
- [ ] Media buttons respond (<<, >, >>)
- [ ] Volume slider works smoothly
- [ ] Tap "Weather" → See temperature
- [ ] Tap "Camera" → See live camera feed (wait 10s for first image)
- [ ] Tap "Back" → Return to main page
- [ ] Verify navigation buttons don't overlap with toggle light
- [ ] Press button → Voice assistant activates

## Troubleshooting (Quick Fixes)

### Device won't flash
```bash
# Hold boot button while connecting USB
esphome run Ball_v5.3.yaml
```

### Wrong entity ID
1. Edit substitutions at top of YAML
2. Reflash device
3. Done! (No need to find 16 locations)

### Media buttons show boxes
✅ Fixed in V5.2! Make sure you're using `Ball_v5.3.yaml`, not `Ball_v5.yaml`.

### "Can't convert 'None'" error
✅ Fixed in V5.2! Update to Ball_v5.3.yaml.

### Light doesn't work
1. Check entity exists: HA → Settings → Devices
2. Test manually in HA first
3. Verify entity ID in substitutions
4. Check light has brightness attribute

### Volume slider is laggy
This was fixed in V5.1 (retained in V5.2). If still laggy:
1. Check Home Assistant performance
2. Reduce polling interval (advanced)
3. Update HA to latest version

## Adding More Lights

Want to control multiple lights? Add more substitutions:

```yaml
substitutions:
  light_entity: "light.living_room"
  light_entity_2: "light.bedroom"
  light_entity_3: "light.kitchen"
```

Then duplicate the slider/button sections for each light (or use HA scenes).

## Navigation

**Main Page:**
- Tap "Media" → Media player controls
- Tap "Weather" → Weather info  
- Tap "Camera" → Camera entity

**Sub-pages:**
- Tap "Back" → Return to main

**Voice Assistant:**
- Press button → Starts listening (works from any page)

## Advanced: Multiple Devices

Running multiple Ball devices? Change the device name:

```yaml
substitutions:
  name: ball_v52_living_room  # Make unique
  friendly_name: "Ball Living Room"
```

Each device can control different lights/media players.

## What's NOT Supported

❌ Live camera streaming (ESP32 limitation)
- Camera page shows entity info only
- Use HA app for live view

❌ Automatic album art loading
- Shows placeholder (♪ symbol)
- Possible future enhancement

❌ Dynamic font loading
- Uses built-in Montserrat fonts only
- Sizes: 16, 20, 32

## Next Steps

### Customize Your Setup

1. **Change colors**: Edit `bg_color` hex values
2. **Adjust positions**: Edit x/y coordinates
3. **Add more pages**: Duplicate page structure
4. **Custom sounds**: Change `startup_sound` substitution

### Explore More

- Read `CHANGES.md` for detailed changes
- Check `README.md` for full feature list
- Look at Ball_v5 docs for advanced topics

## Need Help?

### Check these first
1. ✅ Using Ball_v5.3.yaml (not v5.yaml)?
2. ✅ Substitutions configured correctly?
3. ✅ secrets.yaml in same folder?
4. ✅ ESPHome 2025.5.0+?
5. ✅ Home Assistant accessible?

### Common Issues

**"Entity not found"**
- Entity ID typo in substitutions
- Entity doesn't exist in HA
- Entity not accessible

**"Connection failed"**
- Check WiFi credentials in secrets.yaml
- Check API key matches
- Check HA IP/hostname

**"Compilation failed"**
- Check YAML syntax (indentation!)
- Check ESPHome version
- Check all substitutions defined

## Default Configuration

If entities don't exist:
- Light: Slider won't update, button won't work
- Media: Shows "No media", buttons won't work
- Weather: Shows "Loading...", won't update
- Camera: Shows entity placeholder

Device will still work for voice assistant!

## Tips

💡 **Use Tab completion**: In HA, type partial entity ID and press Tab

💡 **Test in HA first**: Make sure light/media/weather work in HA before adding to Ball

💡 **Start simple**: Configure just light first, then add media/weather

💡 **Keep backups**: Save working YAML files

💡 **Use unique names**: If running multiple devices

## Success! What Now?

Your Ball V5.2 is ready! Try:
- 🎵 Play music and control from device
- 🌡️ Check weather at a glance  
- 💡 Adjust lights with slider
- 📷 Quick check camera status
- 🎙️ Ask voice assistant questions

Enjoy your smart display! 🎉

---

**Configuration took < 3 minutes? Tell us! Too complicated? Let us know what confused you.**
