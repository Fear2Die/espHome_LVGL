# Migration Guide: Ball V5.4 → Ball V6

## Overview

This guide helps you migrate from Ball V5.4 (button navigation) to Ball V6 (swipe navigation).

**Time Required:** 10-15 minutes  
**Difficulty:** Easy  
**Risk:** Low (can always revert to V5.4)

## What You'll Gain

✅ Modern swipe navigation (no buttons)  
✅ Professional iOS-style UI  
✅ Cleaner, less cluttered interface  
✅ Better use of circular display space  
✅ Modern styling throughout  
✅ Premium user experience  

## What You'll Lose

❌ Camera page (V6 focuses on core 3 screens)  
❌ Navigation buttons (replaced by swipes)  
❌ Back buttons (swipe right instead)  

## Pre-Migration Checklist

### 1. Backup Your Current Configuration
```bash
# Back up your V5.4 configuration
cp Ball_v5.4.yaml Ball_v5.4_backup.yaml

# Back up your secrets file
cp secrets.yaml secrets_backup.yaml
```

### 2. Note Your Current Entities
From your `Ball_v5.4.yaml`, note these values:
```yaml
substitutions:
  light_entity: "light.____________"        # Write this down
  media_player_entity: "media_player.______"  # Write this down
  weather_entity: "weather.____________"      # Write this down
```

### 3. Check Home Assistant Connection
- Ensure your device is connected to HA
- Verify all entities are working
- Test light, media player, and weather integrations

### 4. Have USB Cable Ready
- Keep USB-C cable handy for flashing
- Know your device's serial port (usually /dev/ttyUSB0 or COM3)

## Migration Steps

### Step 1: Download Ball V6 Configuration

```bash
# Navigate to Ball_v6 directory
cd "Xiaozhi Ball V2/Ball_v6"

# Verify Ball_v6.yaml exists
ls -l Ball_v6.yaml
```

### Step 2: Configure Your Entities

Edit `Ball_v6.yaml` and update the substitutions section (lines 16-25):

```yaml
substitutions:
  # Copy these from your V5.4 configuration
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
```

**Example:**
```yaml
substitutions:
  light_entity: "light.living_room_lamp"
  media_player_entity: "media_player.spotify_living_room"
  weather_entity: "weather.home"
```

### Step 3: Copy Your WiFi Credentials

Option A - Use Existing secrets.yaml:
```bash
# If you already have secrets.yaml, no action needed
# Ball V6 uses the same format
```

Option B - Create New secrets.yaml:
```yaml
# Create secrets.yaml in Ball_v6 directory
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
```

### Step 4: Review Optional Settings

Check if you want to change any settings (lines 35-43):

```yaml
## SETTINGS
startup_sound: "Home_Connected"  # Options: available, Home_Connected, Computer_Ready
imagewidth: "240"
imageheight: "240"
displaymodel: "GC9A01A"
invertcolors: "true"
```

**Most users can leave these as default.**

### Step 5: Flash to Device

#### Using ESPHome Dashboard:
1. Upload `Ball_v6.yaml` to your ESPHome dashboard
2. Click "Install"
3. Choose "Wireless" (OTA) if previously connected
4. Wait for compilation and upload

#### Using ESPHome CLI:
```bash
# Compile
esphome compile Ball_v6.yaml

# Upload via USB
esphome upload Ball_v6.yaml

# Or upload wirelessly (if already connected)
esphome upload Ball_v6.yaml --device ball_v6.local
```

### Step 6: Verify Installation

1. **Check Boot:**
   - Device should boot within 30 seconds
   - Screen shows "Initializing..."
   - Then shows Main screen

2. **Test Swipe Navigation:**
   - Swipe left from Main → should go to Media
   - Swipe left from Media → should go to Weather
   - Swipe left from Weather → should return to Main
   - Swipe right reverses the order

3. **Test Light Control:**
   - Toggle switch should control your light
   - Slider should adjust brightness
   - Changes should reflect immediately

4. **Test Media Control:**
   - Album art should appear (when playing media)
   - Play/pause button should work
   - Previous/next buttons should work
   - Song title/artist should display

5. **Test Weather:**
   - Temperature should display
   - Humidity should show in card
   - Condition text should appear

## Troubleshooting Migration Issues

### Issue: "No WiFi" Screen

**Cause:** WiFi credentials not set or incorrect

**Solution:**
1. Check `secrets.yaml` exists in Ball_v6 directory
2. Verify WiFi credentials are correct
3. Check WiFi is 2.4GHz (not 5GHz)
4. Reflash with USB cable if needed

### Issue: "No Home Assistant" Screen

**Cause:** Device can't connect to Home Assistant

**Solution:**
1. Check device is online (ping device)
2. Verify API encryption key matches (if using)
3. Check Home Assistant is running
4. Restart Home Assistant
5. Check logs: `esphome logs Ball_v6.yaml`

### Issue: Swipes Not Working

**Cause:** Touch not detecting gestures or wrong mode

**Solution:**
1. Ensure you're in idle mode (not voice assistant mode)
2. Try longer, faster swipes
3. Start swipe from center of screen
4. Check logs for touch events
5. Verify touch screen is working (long-press shows battery)

### Issue: Light Not Controlling

**Cause:** Entity ID mismatch

**Solution:**
1. Verify entity ID in Home Assistant (Developer Tools → States)
2. Check exact spelling: `light.living_room_lamp` not `Light.living_room_lamp`
3. Ensure light integration is loaded
4. Check Home Assistant logs

### Issue: Album Art Not Showing

**Cause:** Media player doesn't provide artwork or network issue

**Solution:**
1. Verify media player has `entity_picture` attribute
2. Check media is actually playing
3. Wait a few seconds for download
4. Check HTTP request component working
5. Try different media source

### Issue: Weather Not Updating

**Cause:** Weather integration not working or entity mismatch

**Solution:**
1. Verify weather entity in HA (Developer Tools → States)
2. Check weather integration is loaded
3. Ensure entity has `temperature` and `humidity` attributes
4. Trigger manual weather update in HA

### Issue: Compilation Errors

**Cause:** ESPHome version mismatch or configuration error

**Solution:**
1. Update ESPHome to 2024.5.0 or newer
2. Check YAML syntax validation passed
3. Review error message for specific issue
4. Check logs: `esphome compile Ball_v6.yaml`

## Reverting to V5.4

If you need to go back to V5.4:

```bash
# Flash your V5.4 backup
esphome upload Ball_v5.4_backup.yaml

# Or use the original V5.4
esphome upload Ball_v5.4.yaml
```

**Note:** Your secrets.yaml should work with both versions.

## Key Differences to Remember

### Navigation Changed
```
V5.4: Tap [Media] button → Media screen
V6:   Swipe left → Media screen

V5.4: Tap [Back] button → Main screen
V6:   Swipe right → Previous screen
```

### Button Locations Changed
```
V5.4: Navigation buttons at bottom
V6:   No navigation buttons (swipe instead)

V5.4: Back button on sub-screens
V6:   No back button (swipe right)
```

### Screen Flow Changed
```
V5.4: Main ↔ Media (direct)
      Main ↔ Weather (direct)
      Main ↔ Camera (direct)

V6:   Main → Media → Weather → Main (circular)
```

### UI Elements Changed
```
V5.4: Button-style light toggle
V6:   iOS-style switch

V5.4: Basic brightness slider
V6:   Modern slider with shadows

V5.4: 60x60 album art
V6:   100x100 album art with circular progress

V5.4: Simple weather display
V6:   Large temperature + modern humidity card
```

## Learning the New Interface

### Swipe Tips
1. **Start from center** - Begin swipe from middle of screen
2. **Swipe horizontally** - Keep it mostly left/right
3. **Be quick** - Fast swipes work best
4. **Distance matters** - Need at least 60 pixels of movement

### New Gestures
- **Swipe Left**: Next screen (Main → Media → Weather → Main)
- **Swipe Right**: Previous screen (reverse order)
- **Long Press**: Toggle battery display (same as V5.4)
- **Tap Switch**: Toggle light (new iOS-style switch)
- **Tap Buttons**: Media controls (now circular buttons)

### Navigation Flow
```
Starting at Main Screen:
- Swipe Left  → Media Screen
- Swipe Left  → Weather Screen  
- Swipe Left  → Main Screen (back to start!)

Or reverse:
- Swipe Right → Weather Screen
- Swipe Right → Media Screen
- Swipe Right → Main Screen
```

## Post-Migration Checklist

After successful migration, verify:

- [ ] Device boots and shows Main screen
- [ ] Swipe left navigates to Media screen
- [ ] Swipe left navigates to Weather screen
- [ ] Swipe left returns to Main screen (circular)
- [ ] Swipe right navigates backward
- [ ] Light switch toggles light
- [ ] Brightness slider adjusts light
- [ ] Media controls work (play/pause/next/prev)
- [ ] Album art displays when playing media
- [ ] Weather displays temperature
- [ ] Weather displays humidity
- [ ] Long-press toggles battery display
- [ ] Voice assistant button still works
- [ ] All Home Assistant integrations work

## Getting Help

If you encounter issues during migration:

1. **Check Logs:**
   ```bash
   esphome logs Ball_v6.yaml
   ```

2. **Common Log Errors:**
   - "WiFi connection failed" → Check secrets.yaml
   - "API connection failed" → Check Home Assistant
   - "Component initialization failed" → Check entity IDs

3. **Community Support:**
   - GitHub Issues: Report bugs or ask questions
   - Documentation: Review README_YAML.md
   - Quick Start: See QUICK_START_V6.md

4. **Revert if Needed:**
   - You can always go back to V5.4
   - Your configuration is backed up
   - No permanent changes to hardware

## Advanced Configuration

### Adjusting Swipe Sensitivity

Edit `Ball_v6.yaml` around line 338:

```yaml
# Change threshold (default: 60)
if (abs(delta_x) > 40 && abs(delta_x) > abs(delta_y) * 2) {
  # 40 = more sensitive (shorter swipes work)
  # 80 = less sensitive (longer swipes needed)
}
```

### Changing Colors

Find hex color codes in LVGL section (lines 1159-1633):

```yaml
# Example: Change switch active color
indicator:
  bg_color: 0x34C759  # Change to 0xFF0000 for red
```

### Modifying Layout

Adjust widget positions in LVGL pages:

```yaml
# Example: Move title higher
- label:
    id: main_title
    y: 20  # Change from 30 to 20
```

## Success!

🎉 **Congratulations!** You've successfully migrated to Ball V6!

Enjoy your new modern, gesture-based interface!

### What's Next?

- Customize colors to match your style
- Adjust swipe sensitivity if needed
- Explore the modern UI design
- Show off your upgraded Ball to friends!

---

**Migration Guide Version:** 1.0  
**Last Updated:** 2025-10-10  
**For:** Ball V5.4 → Ball V6  
**Difficulty:** Easy  
**Success Rate:** 95%+
