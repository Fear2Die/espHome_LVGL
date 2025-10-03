# Ball V2 - Quick Start Guide

## 5-Minute Setup

### Step 1: Clone and Configure (1 min)
```bash
git clone https://github.com/Fear2Die/espHome_LVGL.git
cd espHome_LVGL/Ball_v2
cp secrets.yaml.example secrets.yaml
```

Edit `secrets.yaml`:
```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
```

### Step 2: Configure Light Entity (2 min)

Edit `Ball_v2.yaml` and replace **all 4 instances** of `light.YOUR_LIGHT_ENTITY`:

1. **Line ~205** (Home Assistant sensor):
   ```yaml
   - platform: homeassistant
     id: ha_light_brightness
     entity_id: light.living_room_lamp  # ← Change this
   ```

2. **Line ~1172** (Slider release):
   ```yaml
   on_release:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.living_room_lamp  # ← Change this
   ```

3. **Line ~1206** (Button click):
   ```yaml
   on_click:
     - homeassistant.action:
         action: light.toggle
         data:
           entity_id: light.living_room_lamp  # ← Change this
   ```

4. **Line ~858** (Number entity):
   ```yaml
   set_action:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.living_room_lamp  # ← Change this
   ```

**Quick Replace All:**
```bash
sed -i 's/light.YOUR_LIGHT_ENTITY/light.living_room_lamp/g' Ball_v2.yaml
```

### Step 3: Flash Device (1 min)
```bash
esphome run Ball_v2.yaml
```

Select connection method:
- **USB:** Plug in device via USB cable
- **OTA:** Enter device IP address (if already flashed once)

Wait for flash to complete...

### Step 4: Enable HA Actions (1 min)

**CRITICAL:** Without this, light control won't work!

1. Open Home Assistant web interface
2. Go to **Settings** → **Devices & Services**
3. Click **ESPHome** integration
4. Find **Ball V2** device
5. Click **CONFIGURE** button
6. ✅ Check **"Allow the device to perform Home Assistant actions"**
7. Click **SUBMIT**

### Step 5: Reboot and Test (30 sec)

Reboot the device:
- Unplug and replug power, OR
- In Home Assistant: Device → **REBOOT** button

**Test light control:**
1. Navigate to light control page (see navigation options below)
2. Move slider → Light brightness should change
3. Click button → Light should toggle on/off

---

## Quick Troubleshooting

### Light control doesn't work
```
❌ Problem: Slider/button don't control light
✅ Solution: Enable "Allow device to perform Home Assistant actions" in Step 4
```

### Slider doesn't update when light changes
```
❌ Problem: Slider stays at 128 when light changes in HA
✅ Solution: Check entity ID in homeassistant sensor matches your light
```

### Device won't connect to WiFi
```
❌ Problem: "No WiFi" screen shows
✅ Solution: Check secrets.yaml has correct WiFi credentials
```

### Can't flash device
```
❌ Problem: "No serial port found"
✅ Solution: Install USB drivers or use OTA with IP address
```

---

## Navigation to Light Control Page

The `light_control_page` exists but needs navigation setup. Choose one:

### Option A: Home Assistant Automation
```yaml
# In Home Assistant automations.yaml
- alias: "Show Ball V2 Light Control"
  trigger:
    - platform: state
      entity_id: input_boolean.ball_light_control_toggle
      to: 'on'
  action:
    - service: esphome.ball_v2_lvgl_page_show
      data:
        page: light_control_page
```

### Option B: Add Touch Long-Press (Edit Ball_v2.yaml)
```yaml
# Find the touchscreen section and add:
touchscreen:
  - platform: cst816
    # ... existing config ...
    on_touch:
      - if:
          condition:
            lambda: 'return id(touch_input).state;'
          then:
            - delay: 2s
            - lvgl.page.show: light_control_page
```

### Option C: Use Number Entity
Simply adjust "Ball V2 Light Brightness" in Home Assistant dashboard!

---

## Pin Reference

Already configured in Ball_v2.yaml - for reference only:

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
| Slider Min | 0 | Minimum brightness |
| Slider Max | 255 | Maximum brightness |
| Slider Default | 128 | Initial value |
| Number Min | 0 | Percentage minimum |
| Number Max | 100 | Percentage maximum |
| Number Step | 1 | Increment step |

---

## Next Steps

✅ **Working?** Configure page navigation (see options above)
✅ **Want RGB?** Add color picker widgets (see CHANGES.md)
✅ **Multiple lights?** Duplicate the page for each light
✅ **Customize?** Change colors in LVGL page definition

---

## Support

📖 Full docs: [README.md](README.md)
📝 Detailed changes: [CHANGES.md](CHANGES.md)
📊 Overview: [SUMMARY.md](SUMMARY.md)
🐛 Issues: [GitHub Issues](https://github.com/Fear2Die/espHome_LVGL/issues)

---

**Status:** ✅ Configuration validated and ready to use!
