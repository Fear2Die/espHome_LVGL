# Ball V5.4 Quick Start Guide

**Get Ball V5.4 running in under 10 minutes!**

---

## What You Need

- ✅ Xiaozhi Ball V2 device (or compatible ESP32-S3 with GC9A01A circular display)
- ✅ Home Assistant instance running
- ✅ WiFi network
- ✅ USB cable to connect Ball to computer
- ✅ ESPHome installed (via Home Assistant Add-on or standalone)

---

## Step 1: Get Your Entity IDs (3 minutes)

### Find Your Light Entity

1. Open Home Assistant
2. Go to **Settings** → **Devices & Services**
3. Find your light device
4. Click on it
5. Copy the entity ID (example: `light.bedroom_lamp`)

### Find Your Media Player Entity

1. Open Home Assistant
2. Click **Media** in the sidebar
3. Find your media player
4. Click the three dots → **Settings**
5. Copy the entity ID (example: `media_player.kitchen_speaker`)

### Find Your Weather Entity

1. Open Home Assistant
2. Go to **Settings** → **Integrations**
3. Find your Weather integration (or add Met.no - it's free!)
4. Copy the entity ID (example: `weather.home`)

**Write these down! You'll need them in the next step.**

---

## Step 2: Configure Ball V5.4 (2 minutes)

1. Open `Ball_v5.4.yaml` in a text editor
2. Find lines 20-27 (the entity configuration section)
3. Replace the placeholder entity IDs with your real ones:

```yaml
## ENTITY CONFIGURATION - SET YOUR HOME ASSISTANT ENTITIES HERE
substitutions:
  # Light entity - the light you want to control
  light_entity: "light.bedroom_lamp"  # ← YOUR light entity here
  
  # Media player entity - your media player device
  media_player_entity: "media_player.kitchen_speaker"  # ← YOUR media player here
  
  # Weather entity - your weather integration
  weather_entity: "weather.home"  # ← YOUR weather entity here
```

4. **Save the file**

---

## Step 3: Setup WiFi & API (2 minutes)

1. Copy `secrets.yaml.example` to `secrets.yaml`
   ```bash
   cp secrets.yaml.example secrets.yaml
   ```

2. Edit `secrets.yaml` with your information:
   ```yaml
   wifi_ssid: "YourWiFiName"
   wifi_password: "YourWiFiPassword"
   api_key: "your-esphome-api-key"  # Generate in Home Assistant
   ```

3. **Save the file**

### How to Get API Key

In Home Assistant:
1. Go to **Settings** → **Add-ons, Backups & Supervisor**
2. Click **ESPHome**
3. Click on your device
4. Copy the API encryption key

---

## Step 4: Flash to Device (3 minutes)

### If Using Home Assistant ESPHome Add-on

1. Upload `Ball_v5.4.yaml` and `secrets.yaml` to ESPHome config folder
2. Click **Install** → **Wirelessly** (if already flashed) or **Plug into this computer**
3. Wait for compilation and upload
4. Done! ✅

### If Using ESPHome CLI

```bash
# First time (via USB)
esphome run Ball_v5.4.yaml

# Future updates (wireless)
esphome run Ball_v5.4.yaml --device ball_v54.local
```

Wait for:
- ⏳ Compiling... (2-3 minutes)
- ⏳ Uploading... (30 seconds)
- ✅ Done!

---

## Step 5: Test Everything (2 minutes)

### Initial Boot

1. Ball should show "Initializing..."
2. Then connect to WiFi
3. Connect to Home Assistant
4. Show "Ready" status

### Test Main Page (Idle)

- ✅ Time displayed in top-left
- ✅ Battery percentage in top-right
- ✅ Status shows "Ready" (green)
- ✅ Brightness slider works
- ✅ Toggle light button works

### Test Navigation

1. Tap **Media** button
   - ✅ Goes to media page
   - ✅ Shows current media (if playing)
   - ✅ Album art displayed (if available)

2. Tap **< Back**
   - ✅ Returns to main page

3. Tap **Weather** button
   - ✅ Goes to weather page
   - ✅ Shows temperature
   - ✅ Shows weather condition

4. Tap **< Back**
   - ✅ Returns to main page

### Test Media Controls

1. Go to Media page
2. Start playing something in Home Assistant
3. Check Ball displays:
   - ✅ Song title
   - ✅ Artist name
   - ✅ Album art
   - ✅ Playing status
4. Test buttons:
   - ✅ Previous track works
   - ✅ Play/pause works
   - ✅ Next track works
   - ✅ Volume slider works

### Test Voice Assistant

1. Say wake word: "Hey Jarvis" or "Okay Nabu" or "Alexa"
2. Ball should show blue "Listening..." screen
3. Say a command
4. Ball shows orange "Thinking..."
5. Ball shows green "Replying..."
6. Returns to idle

---

## Troubleshooting

### Ball Won't Connect to WiFi

**Problem:** Stuck on "No WiFi"

**Solutions:**
1. Check `secrets.yaml` - WiFi name and password correct?
2. Is WiFi 2.4GHz? (Ball doesn't support 5GHz)
3. Is WiFi in range?
4. Try restarting Ball (power cycle)

### Ball Won't Connect to Home Assistant

**Problem:** Shows "No Home Assistant"

**Solutions:**
1. Is Home Assistant running?
2. Check `secrets.yaml` - API key correct?
3. Check Home Assistant → Settings → Integrations
4. Look for ESPHome integration
5. Ball should appear there

### Light Control Doesn't Work

**Problem:** Slider/button doesn't control light

**Solutions:**
1. Check entity ID in Ball_v5.4.yaml - correct?
2. Check entity ID in Home Assistant - still exists?
3. Try controlling light from Home Assistant directly
4. Check Home Assistant logs for errors

### Media Player Shows "No Media"

**Problem:** Always shows "No media" even when playing

**Solutions:**
1. Check entity ID - correct?
2. Is media player actually playing in Home Assistant?
3. Does media player have `entity_picture` attribute? (for album art)
4. Try different media player

### Weather Shows "Loading..."

**Problem:** Weather never updates

**Solutions:**
1. Check entity ID - correct?
2. Is weather integration working in Home Assistant?
3. Check Home Assistant logs
4. Wait 1-2 minutes for first update

### Touch Not Working

**Problem:** Taps don't register

**Solutions:**
1. Touch sensor might be miscalibrated
2. Try tapping firmly
3. Try different areas of screen
4. May need to adjust touch sensitivity in code

### Elements Look Cut Off

**Problem:** Text or buttons appear cut off at edges

**Solutions:**
1. **You're probably using V5.3, not V5.4!**
2. Verify you're using Ball_v5.4.yaml (check `name: ball_v54`)
3. Re-flash with correct file
4. V5.4 is specifically designed to fix this issue!

---

## Quick Reference

### Entity IDs to Configure

| Entity | Line in YAML | Example |
|--------|--------------|---------|
| Light | Line 21 | `light.bedroom_lamp` |
| Media Player | Line 24 | `media_player.kitchen_speaker` |
| Weather | Line 27 | `weather.home` |

### Files You Need

| File | Purpose | Required? |
|------|---------|-----------|
| Ball_v5.4.yaml | Main config | ✅ Yes |
| secrets.yaml | WiFi & API keys | ✅ Yes |
| secrets.yaml.example | Template | ℹ️ Reference only |

### Navigation Map

```
        Main (Idle) Page
            ↙      ↘
           ↙        ↘
       Media      Weather
          ↓          ↓
        Back        Back
          ↓          ↓
        Main (Idle) Page
```

---

## Next Steps

### You're All Set! 🎉

Now you can:
- ✅ Control your lights from Ball
- ✅ Control media playback
- ✅ Check weather
- ✅ Use voice assistant

### Want to Learn More?

- **Understand the layout**: Read [LAYOUT.md](LAYOUT.md)
- **See what changed**: Read [CHANGES_V5.4.md](CHANGES_V5.4.md)
- **Visual comparison**: Read [VISUAL_COMPARISON.md](VISUAL_COMPARISON.md)
- **Full documentation**: Read [README.md](README.md)

### Want to Customize?

You can customize:
- **Fonts**: Change `font_family` in Ball_v5.4.yaml
- **Colors**: Change color hex codes (e.g., `0x00FF00` for green)
- **Positions**: Adjust x, y coordinates (stay within circular safe zone!)
- **Sizes**: Adjust width, height values
- **Add entities**: Add more lights, media players, etc.

See [LAYOUT.md](LAYOUT.md) for safe zone guidelines!

---

## Common Customizations

### Add Second Light

In Ball_v5.4.yaml, add this after line 27:
```yaml
  light_entity_2: "light.your_second_light"
```

Then use it in automations or create a second page!

### Change Status Colors

Find these lines and change hex colors:
```yaml
text_color: 0x00FF00  # Green - change to your color
bg_color: 0x111111    # Dark gray - change to your color
```

### Adjust Brightness Slider

Find the slider widget and adjust:
```yaml
- slider:
    id: my_light_slider
    y: 68           # Vertical position
    width: 180      # Width (keep ≤180 for circular!)
    min_value: 0    # Minimum brightness
    max_value: 100  # Maximum brightness
```

---

## Getting Help

### Check Documentation
- [README.md](README.md) - Full documentation
- [LAYOUT.md](LAYOUT.md) - Layout specifications
- [INDEX.md](INDEX.md) - Documentation index

### Common Issues
- [README.md - Tips & Tricks](README.md#-tips--tricks)
- [Troubleshooting section above](#troubleshooting)

### Online Resources
- ESPHome Documentation: https://esphome.io
- Home Assistant Forums: https://community.home-assistant.io
- ESPHome Discord: https://discord.gg/KhAMKrd

---

## Quick Start Checklist

Use this to verify your setup:

### Configuration
- [ ] Entity IDs configured in Ball_v5.4.yaml
- [ ] secrets.yaml created and configured
- [ ] WiFi credentials correct
- [ ] API key obtained from Home Assistant

### Flashing
- [ ] Ball connected to computer (first time)
- [ ] ESPHome compilation successful
- [ ] Upload to device successful
- [ ] Ball boots and connects to WiFi
- [ ] Ball connects to Home Assistant

### Testing
- [ ] Main page displays correctly
- [ ] Time and battery show
- [ ] Light control works
- [ ] Media page accessible
- [ ] Media controls work
- [ ] Weather page accessible
- [ ] Weather data displays
- [ ] Voice assistant responds

### Verification
- [ ] All elements visible (not cut off)
- [ ] All buttons touchable
- [ ] Navigation works smoothly
- [ ] No errors in ESPHome logs

---

**All checkboxes checked? Congratulations! You're running Ball V5.4! 🎉**

Enjoy your circular-optimized smart display!
