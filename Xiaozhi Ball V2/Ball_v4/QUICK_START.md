# Ball V4 - Quick Start Guide

## 5-Minute Setup

### Step 1: Get the Files (30 sec)

```bash
git clone https://github.com/Fear2Die/espHome_LVGL.git
cd espHome_LVGL/Ball_v4
```

### Step 2: Configure WiFi (1 min)

```bash
cp secrets.yaml.example secrets.yaml
```

Edit `secrets.yaml`:
```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
ap_password: "FallbackPassword123"
```

### Step 3: Configure Light Entity (2 min)

Edit `Ball_v4.yaml` and replace **all 4 instances** of `light.YOUR_LIGHT_ENTITY`:

1. **Line ~213** (Home Assistant sensor):
   ```yaml
   - platform: homeassistant
     id: ha_light_brightness
     entity_id: light.living_room_lamp  # ← Change this
   ```

2. **Line ~1070** (Slider on_value on Ready page):
   ```yaml
   on_value:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.living_room_lamp  # ← Change this
   ```

3. **Line ~1108** (Button on_click on Ready page):
   ```yaml
   on_click:
     - homeassistant.action:
         action: light.toggle
         data:
           entity_id: light.living_room_lamp  # ← Change this
   ```

4. **Line ~873** (Number entity):
   ```yaml
   set_action:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.living_room_lamp  # ← Change this
   ```

**Tip**: Use Find & Replace in your editor:
- Find: `light.YOUR_LIGHT_ENTITY`
- Replace: `light.your_actual_light_name`

### Step 4: Flash the Device (1 min)

```bash
esphome run Ball_v4.yaml
```

Select your connection method:
- **USB**: Connect device via USB cable
- **OTA**: Enter device IP if already running ESPHome

### Step 5: Enable HA Actions (30 sec)

**CRITICAL STEP** - Light control won't work without this!

1. In Home Assistant: **Settings → Devices & Services → ESPHome**
2. Find **Ball V4** device
3. Click **Configure**
4. ✅ Check: **"Allow the device to perform Home Assistant actions"**
5. Click **Submit**

### Step 6: Reboot and Test (30 sec)

Reboot the device:
- Unplug and replug power, OR
- In Home Assistant: Device → **REBOOT** button

**Test the new features:**
1. ✅ Time displays in top-left corner (HH:MM)
2. ✅ Move slider → Light brightness changes **instantly**
3. ✅ Brightness shows as percentage (e.g., "50%")
4. ✅ Touch screen → Voice assistant does NOT activate
5. ✅ Press button → Voice assistant DOES activate
6. ✅ Click "Toggle Light" → Light turns on/off
7. ✅ All controls fit on screen without scrolling

---

## What's Different from Ball V3?

### Instant Updates ⚡
- **V3**: Release slider to apply brightness
- **V4**: Brightness changes as you move slider

### Percentage-Based 📊
- **V3**: Brightness 0-255 (confusing)
- **V4**: Brightness 0-100% (intuitive)

### Touch Behavior 👆
- **V3**: Touch activates voice assistant (annoying)
- **V4**: Touch only controls widgets (better)

### Screen Layout 📱
- **V3**: May need scrolling
- **V4**: Everything fits perfectly

### Time Display 🕐
- **V3**: No time shown
- **V4**: Shows HH:MM in corner

---

## Accessing Light Controls

The light control widgets (slider and button) are integrated into the **Ready page** (`idle_page`), which is the default screen when the device is idle.

**No navigation needed!** The controls are always visible on the Ready page.

### Control Layout (Top to Bottom)

```
┌─────────────────────────┐
│ 12:45  Ready        85% │ ← Time, Status, Battery
│                         │
│      [===========]      │ ← Brightness Slider (0-100%)
│          50%            │ ← Live Percentage
│                         │
│    [Toggle Light]       │ ← On/Off Button
│                         │
└─────────────────────────┘
```

### Alternative Control Options

- **Home Assistant Number Entity**: Adjust "Ball V4 Light Brightness" (0-100%) in Home Assistant dashboard
- **Voice Commands**: Use voice assistant to control the light (e.g., "Set brightness to 75%")

---

## Troubleshooting

### Light doesn't change when I move slider
1. ✅ Check HA Actions enabled (Step 5)
2. ✅ Verify light entity ID is correct
3. ✅ Check device is online in ESPHome
4. ✅ Reboot device

### Touch still activates voice assistant
1. ✅ Confirm you flashed Ball_v4.yaml (not Ball_v3.yaml)
2. ✅ Reboot device after flashing

### Time not showing
1. ✅ Wait up to 1 minute (updates every minute)
2. ✅ Check Home Assistant connection
3. ✅ Reboot device

### Slider doesn't update from external changes
1. ✅ Check light entity ID in sensor section
2. ✅ Verify Home Assistant connection
3. ✅ Try turning light on/off from HA

### Controls don't fit on screen
1. ✅ Confirm you're using Ball_v4.yaml
2. ✅ Check display is 240x240 (GC9A01A)
3. ✅ Reflash if needed

---

## Pin Reference

Already configured in Ball_v4.yaml - for reference only:

| Component | GPIO | Description |
|-----------|------|-------------|
| Touch INT | 12 | Touch interrupt |
| Touch RST | 6 | Touch reset |
| Display CS | 5 | SPI chip select |
| Display DC | 47 | Data/Command |
| Display RST | 38 | Display reset |
| SPI CLK | 4 | SPI clock |
| SPI MOSI | 2 | SPI data |
| Main Button | 0 | Physical button |
| LED | 48 | WS2812 RGB |
| Battery ADC | 1 | Battery voltage |

---

## Default Light Values

| Parameter | Value | Description |
|-----------|-------|-------------|
| Slider Min | 0 | Minimum brightness (%) |
| Slider Max | 100 | Maximum brightness (%) |
| Slider Default | 50 | Initial value (%) |
| Number Min | 0 | Percentage minimum |
| Number Max | 100 | Percentage maximum |
| Number Step | 1 | Increment step |

---

## Voice Assistant Usage

### Activation Methods
1. **Wake Word**: Say "Alexa", "Hey Jarvis", or "Okay Nabu"
2. **Physical Button**: Press the button on device
3. **NOT Touch Screen**: Touching screen does NOT activate (fixed in V4!)

### Voice Commands for Light
- "Turn on the living room light"
- "Set brightness to 75 percent"
- "Dim the lights"
- "Turn off the light"

---

## Battery Display

- **Toggle**: Long-press (1+ second) on screen
- **Location**: Top-right corner
- **Shows**: Battery percentage when enabled

---

## Advanced Tips

### Find Your Light Entity ID
In Home Assistant:
1. Go to **Settings → Devices & Services**
2. Click on your light integration
3. Find your light entity
4. Copy the entity ID (e.g., `light.bedroom_lamp`)

### Test Configuration Before Flashing
```bash
esphome config Ball_v4.yaml
```

### View Logs After Flashing
```bash
esphome logs Ball_v4.yaml
```

### Over-The-Air Updates
After first flash via USB:
```bash
esphome run Ball_v4.yaml
# Select OTA option and enter IP
```

---

## Need Help?

1. **Read full documentation**: See `README.md` for details
2. **Check changes**: See `CHANGES.md` for V3→V4 differences
3. **GitHub Issues**: Report problems at [Fear2Die/espHome_LVGL](https://github.com/Fear2Die/espHome_LVGL)

---

## Next Steps

After successful setup:
- ✅ Customize wake word in Ball_v4.yaml
- ✅ Adjust slider sensitivity if needed
- ✅ Set up voice assistant automation in HA
- ✅ Configure timer notifications
- ✅ Explore media player integration

---

**Enjoy your enhanced Ball V4!** 🎉
