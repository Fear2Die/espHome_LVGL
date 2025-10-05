# Ball V5.2 - Installation Guide

## Prerequisites

### Hardware
- ✅ ESP32-S3 Ball V2 device
- ✅ USB-C cable
- ✅ Computer with ESPHome

### Software
- ✅ ESPHome 2025.5.0 or newer
- ✅ Home Assistant with:
  - Light entity with brightness
  - Media player entity
  - Weather integration
  - (Optional) Camera entity

### Knowledge
- Basic understanding of YAML
- How to find entity IDs in Home Assistant
- How to use ESPHome (compile/flash)

---

## Installation Steps

### Step 1: Get the Files (2 minutes)

#### Option A: Clone Repository
```bash
git clone https://github.com/Fear2Die/espHome_LVGL.git
cd espHome_LVGL/Ball_v5.2
```

#### Option B: Download Files
1. Go to https://github.com/Fear2Die/espHome_LVGL
2. Navigate to Ball_v5.2 folder
3. Download `Ball_v5.2.yaml`
4. Download `secrets.yaml.example`

### Step 2: Setup Secrets (2 minutes)

```bash
cp secrets.yaml.example secrets.yaml
nano secrets.yaml  # or use your preferred editor
```

**Edit secrets.yaml:**
```yaml
wifi_ssid: "YourWiFiNetwork"
wifi_password: "YourWiFiPassword"
api_encryption_key: "your_api_key_here"  # Generate with 'esphome secrets generate'
ota_password: "your_ota_password"
```

**Generate API key** (if needed):
```bash
esphome secrets generate
```

### Step 3: Configure Entities (2 minutes)

**Open Ball_v5.2.yaml** and find the substitutions section (around line 20):

```yaml
## ENTITY CONFIGURATION - SET YOUR HOME ASSISTANT ENTITIES HERE
substitutions:
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
  camera_entity: "camera.YOUR_CAMERA_ENTITY"
```

**Replace with your actual entity IDs:**

#### Finding Light Entity
1. Home Assistant → Settings → Devices & Services
2. Find your light → Click it
3. Copy entity ID (e.g., `light.living_room_lamp`)

#### Finding Media Player Entity
1. Home Assistant → Media
2. Click any player → More info (⋮) → Settings
3. Copy entity ID (e.g., `media_player.living_room`)

#### Finding Weather Entity
1. Home Assistant → Settings → Integrations
2. Find "Weather" → Click configure
3. Copy entity ID (e.g., `weather.home` or `weather.forecast_home`)

**Don't have weather?** Install Met.no:
1. Settings → Integrations → Add Integration
2. Search "Met.no" → Configure with your location
3. Use entity ID: `weather.forecast_home`

#### Finding Camera Entity (Optional)
1. Home Assistant → Settings → Devices & Services
2. Find camera → Click it
3. Copy entity ID (e.g., `camera.front_door`)

**Example configuration:**
```yaml
substitutions:
  light_entity: "light.living_room_lamp"
  media_player_entity: "media_player.living_room"
  weather_entity: "weather.forecast_home"
  camera_entity: "camera.front_door"
```

### Step 4: Validate Configuration (1 minute)

```bash
esphome config Ball_v5.2.yaml
```

**Should see**: "Configuration is valid!"

**Common errors:**
- Indentation issues → Check spaces (not tabs)
- Missing secrets.yaml → Copy from example
- Wrong entity format → Should be `domain.entity_name`

### Step 5: Compile (2-5 minutes)

```bash
esphome compile Ball_v5.2.yaml
```

**This will:**
- Download dependencies
- Compile firmware
- Create binary file

**First compile takes longer** (2-5 minutes). Subsequent compiles are faster (30 seconds).

### Step 6: Flash Device (5 minutes)

#### First Time Flash (USB Required)

1. **Connect device via USB-C**
2. **Put device in flash mode** (if needed):
   - Hold BOOT button
   - Press RESET button
   - Release both
3. **Flash:**
```bash
esphome run Ball_v5.2.yaml
```
4. **Select USB port** (usually `/dev/ttyUSB0` or `/dev/ttyACM0`)
5. **Wait for upload** (2-3 minutes)
6. **Device will reboot automatically**

#### Subsequent Updates (OTA - Over The Air)

After first flash, you can update wirelessly:

```bash
esphome run Ball_v5.2.yaml
```

Select network option (device name will appear).

### Step 7: Verify Installation (2 minutes)

#### Check Home Assistant
1. Go to Settings → Devices & Services
2. Look for "Ball V5.2" device
3. Should auto-discover via ESPHome integration

#### Test on Device
1. **Main Page**: Should show time, battery, light slider
2. **Light Control**: Move slider → light should change
3. **Media Button**: Tap → should navigate to media page
4. **Weather Button**: Tap → should show weather
5. **Camera Button**: Tap → should show camera entity
6. **Back Buttons**: Should return to main page
7. **Voice Button**: Press physical button → should say "Listening"

---

## Troubleshooting Installation

### Device Won't Connect to WiFi

**Check:**
1. WiFi credentials correct in secrets.yaml
2. WiFi is 2.4GHz (ESP32 doesn't support 5GHz)
3. WiFi password has no special characters causing issues
4. Signal strength is good

**Fix:**
```bash
# Connect via USB and check logs
esphome logs Ball_v5.2.yaml
```

Look for WiFi connection messages.

### Compilation Fails

**Error: "secrets.yaml not found"**
```bash
cp secrets.yaml.example secrets.yaml
# Edit secrets.yaml with your values
```

**Error: "Invalid YAML"**
- Check indentation (use spaces, not tabs)
- Ensure entity IDs are in quotes
- Check for typos in substitutions

**Error: "Platform not found"**
```bash
# Update ESPHome
pip install --upgrade esphome
```

### Flash Fails

**Error: "Port not found"**
1. Check USB cable is data cable (not charge-only)
2. Check device is connected
3. Try different USB port
4. Install drivers (CH340/CP210x) if needed

**Error: "Permission denied"**
```bash
# Linux: Add user to dialout group
sudo usermod -a -G dialout $USER
# Logout and login again
```

**Error: "Failed to connect"**
- Hold BOOT button while connecting
- Press RESET while holding BOOT
- Try again

### Device Shows But Features Don't Work

**Light doesn't respond:**
- Check entity ID is correct: `${light_entity}`
- Test light works in Home Assistant first
- Check Home Assistant Actions are enabled
- Check API key matches in secrets.yaml

**Media controls don't work:**
- Check entity ID is correct: `${media_player_entity}`
- Check media player is online in HA
- Test media player in HA first

**Weather doesn't display:**
- Check entity ID is correct: `${weather_entity}`
- Wait 1-2 minutes for first update
- Check weather integration is working in HA

**Voice assistant doesn't work:**
- Check microphone is enabled
- Check speaker is working
- Configure voice assistant in HA
- Check voice pipeline is set up

---

## Post-Installation Setup

### 1. Configure Voice Assistant

In Home Assistant:
1. Settings → Voice assistants
2. Create new assistant or select existing
3. Device → Ball V5.2 → Select voice assistant

### 2. Adjust Settings (Optional)

In Ball_v5.2.yaml, you can modify:

**Startup sound:**
```yaml
startup_sound: "Home_Connected"
# Options: available, Home_Connected, Computer_Ready
```

**Device name:**
```yaml
name: ball_v52_living_room
friendly_name: "Ball Living Room"
```

**Light brightness range** (if needed):
```yaml
# In slider section, change:
min_value: 0
max_value: 100
```

### 3. Create Automations (Optional)

**Auto-adjust brightness based on time:**
```yaml
automation:
  - alias: "Ball Dim at Night"
    trigger:
      - platform: time
        at: "22:00:00"
    action:
      - service: number.set_value
        target:
          entity_id: number.ball_v5_2_light_brightness
        data:
          value: 20
```

**Update weather on schedule:**
(Weather already updates automatically, but you can force update)
```yaml
automation:
  - alias: "Update Weather Every Hour"
    trigger:
      - platform: time_pattern
        hours: "/1"
    action:
      - service: homeassistant.update_entity
        target:
          entity_id: weather.forecast_home
```

---

## Updating from V5.1

### Migration Steps

1. **Backup current config:**
```bash
cp Ball_v5.yaml Ball_v5.yaml.backup
```

2. **Copy secrets:**
```bash
cp Ball_v5/secrets.yaml Ball_v5.2/secrets.yaml
# No changes needed to secrets format
```

3. **Configure entities** in Ball_v5.2.yaml substitutions (see Step 3 above)

4. **Flash device** with new config (see Step 6 above)

5. **Verify** all features work (see Step 7 above)

**Note**: Device name changes from `ball_v5` to `ball_v52`. If you want to keep old name:
```yaml
substitutions:
  name: ball_v5  # Keep old name
```

---

## Advanced Installation

### Custom Component Versions

If you need specific ESPHome component versions:

```yaml
# In Ball_v5.2.yaml, add:
external_components:
  - source: github://esphome/esphome@2025.5.0
    components: [ lvgl ]
```

### Multiple Devices

**Different entities per device:**

Device 1 (Living Room):
```yaml
substitutions:
  name: ball_living_room
  light_entity: "light.living_room"
  media_player_entity: "media_player.living_room"
```

Device 2 (Bedroom):
```yaml
substitutions:
  name: ball_bedroom
  light_entity: "light.bedroom"
  media_player_entity: "media_player.bedroom"
```

### Development Mode

For testing/debugging:

```yaml
# Enable debug logging
logger:
  level: DEBUG
  
# Enable web server
web_server:
  port: 80
```

Then access http://ball_v52.local in browser.

---

## Verification Checklist

After installation, verify these work:

### Hardware
- [ ] Device powers on
- [ ] Screen displays correctly
- [ ] Touch screen responds
- [ ] Speaker works (startup sound)
- [ ] Microphone works (voice assistant)
- [ ] Battery indicator shows percentage

### Connectivity
- [ ] Device connects to WiFi
- [ ] Device appears in Home Assistant
- [ ] API connection established
- [ ] OTA updates work

### Features
- [ ] Light slider changes brightness
- [ ] Light toggle button works
- [ ] Light color updates (gray/yellow)
- [ ] Media page shows current song
- [ ] Media buttons work (<<, >, >>)
- [ ] Volume slider adjusts volume
- [ ] Weather shows temperature
- [ ] Weather shows humidity
- [ ] Camera page displays entity
- [ ] Navigation buttons work
- [ ] Back buttons work
- [ ] Time displays correctly
- [ ] Battery percentage updates

### Voice Assistant
- [ ] Press button → "Listening" appears
- [ ] Speaks command → processes
- [ ] Gets response → speaks reply
- [ ] Returns to main page after

### Logs
- [ ] No font glyph warnings
- [ ] No 'None' conversion errors
- [ ] No critical errors
- [ ] Normal operation messages only

---

## Getting Help

### Before Asking for Help

1. ✅ Check you're using Ball_v5.2.yaml (not v5.yaml)
2. ✅ Verify all entity IDs are correct in substitutions
3. ✅ Test entities work in Home Assistant first
4. ✅ Check secrets.yaml has correct credentials
5. ✅ Read error messages carefully
6. ✅ Check TROUBLESHOOTING section in README.md

### How to Report Issues

Include:
1. ESPHome version (`esphome version`)
2. Home Assistant version
3. Device hardware (Ball V2)
4. Full error message/log
5. Relevant YAML sections
6. What you've already tried

### Resources

- **README.md**: Main documentation
- **QUICK_START.md**: Fast setup guide
- **TROUBLESHOOTING**: Common issues
- **CHANGES.md**: What changed from V5.1
- **COMPARISON.md**: Should you upgrade?
- **ESPHome Docs**: https://esphome.io

---

## Success! Next Steps

Your Ball V5.2 is now installed and working! 🎉

**Try these:**
1. Ask voice assistant a question
2. Adjust light brightness from device
3. Control music playback
4. Check weather at a glance
5. View camera entity

**Customize:**
- Change colors (edit hex values in YAML)
- Adjust layout (edit x/y positions)
- Add more entities (duplicate sections)
- Create automations
- Explore features

**Share:**
- Tell others if setup was easy
- Report any issues you find
- Suggest improvements

Enjoy your smart display! 🎵🌡️💡📷

---

**Installation time: ~15 minutes total**
**Most steps: < 5 minutes each**
**No special tools needed**
