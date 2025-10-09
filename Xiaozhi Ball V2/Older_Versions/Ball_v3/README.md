# ESPHome Xiaozhi Ball V2 - LVGL with Light Control

This configuration for the Xiaozhi Ball V2 device includes full **Home Assistant Voice Assistant** functionality plus **on-screen light control** with LVGL widgets.

## Features

### Voice Assistant
- **LVGL Display System**: Clean, modern UI with colored pages for different states
- **Home Assistant Voice Assistant**: Full voice assistant integration with wake word detection
- **Voice States**:
  - Idle (Green) - Ready for commands
  - Listening (Blue) - Actively listening
  - Thinking (Orange) - Processing your request
  - Replying (Green) - Speaking response
  - Error (Red) - Error state
  - Muted (Black with red text) - Microphone muted
  - Timer Finished (Red) - Timer alert
  - No WiFi (Yellow) - WiFi connection issue
  - No Home Assistant (Dark Red) - HA connection issue

### Light Control (NEW)
- **Brightness Slider**: On-screen slider (0-255) to control Home Assistant light brightness
- **Toggle Button**: Checkable button to toggle the light on/off
- **External Sync**: Slider automatically updates when the light changes externally (via HA app, voice commands, etc.)
- **HA Number Entity**: Optional percentage-based (0-100%) control visible in Home Assistant UI

## Hardware

- ESP32-S3 Device (Xiaozhi Ball V2)
- 240x240 GC9A01A Round Display
- ES8311 Audio DAC
- Microphone and Speaker
- Touch Screen (CST816)
- Battery powered with monitoring
- WS2812 RGB LED

## Configuration

### 1. Create secrets file

Create a `secrets.yaml` file with your WiFi credentials:
```yaml
wifi_ssid: "your_ssid"
wifi_password: "your_password"
```

### 2. Configure your light entity

**IMPORTANT:** Before flashing, replace `light.YOUR_LIGHT_ENTITY` with your actual Home Assistant light entity ID in four places in `Ball_v2.yaml`:

1. **Home Assistant sensor** (around line 207):
   ```yaml
   - platform: homeassistant
     id: ha_light_brightness
     entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

2. **Slider on_release action on Ready page** (around line 1043):
   ```yaml
   on_release:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

3. **Button on_click action on Ready page** (around line 1078):
   ```yaml
   on_click:
     - homeassistant.action:
         action: light.toggle
         data:
           entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

4. **Number entity** (around line 857):
   ```yaml
   set_action:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

Example: If your light is `light.living_room_floor`, replace all instances of `light.YOUR_LIGHT_ENTITY` with `light.living_room_floor`.

### 3. Flash the device

```bash
esphome run Ball_v2.yaml
```

### 4. Enable Home Assistant actions (REQUIRED)

**This step is mandatory** - without it, the light control will not work!

1. Go to **Settings → Devices & Services → ESPHome** in Home Assistant
2. Find your **Ball V2** device and click **Configure**
3. Check the box: **"Allow the device to perform Home Assistant actions"**
4. Click **Submit**

This allows the ESP device to call Home Assistant services from its automations.

### 5. Reboot the device

After enabling HA actions, reboot your Ball V2 device for changes to take effect.

## Usage

### Using the Light Control

The light control widgets (brightness slider and toggle button) are integrated directly into the **Ready page** (`idle_page`), which is the default display when the device is idle and ready for voice commands.

1. **Brightness Slider**: 
   - Drag the slider to adjust brightness (0-255)
   - Release to apply the new brightness to your Home Assistant light
   - The slider automatically updates if the light is changed elsewhere

2. **Toggle Button**: 
   - Click to toggle the light on/off
   - Works with any light state

3. **Number Entity** (optional):
   - Visible in Home Assistant as "Ball V2 Light Brightness"
   - Uses percentage (0-100%) for easier control
   - Useful for automations and quick adjustments from HA dashboard

## Voice Assistant Setup

The device supports:
- On-device wake word detection (Alexa, Hey Jarvis, Okay Nabu)
- Or Home Assistant-based wake word detection
- Configurable wake word engine location in Home Assistant

## Battery Status

Long-press the touch screen to toggle battery percentage display.

## Troubleshooting

### Light control not working

1. **Check HA actions permission**: Make sure you enabled "Allow the device to perform Home Assistant actions" in ESPHome device settings
2. **Check entity ID**: Verify your light entity ID is correct (check in Home Assistant Developer Tools → States)
3. **Check logs**: Use `esphome logs Ball_v2.yaml` to see if actions are being called
4. **Check HA logs**: Look for permission errors in Home Assistant logs

### Slider not updating from external changes

1. Verify the light entity ID in the `homeassistant` sensor matches your light
2. Check that the light has a `brightness` attribute (not all lights support brightness)
3. Look for errors in ESPHome logs

### Debug logging

Add temporary logging to troubleshoot:
```yaml
# In slider on_release:
on_release:
  - lambda: |-
      ESP_LOGD("lvgl", "Slider value=%f", x);
  - homeassistant.action:
      action: light.turn_on
      data:
        entity_id: light.YOUR_LIGHT_ENTITY
        brightness: !lambda 'return (int) x;'
```

## Pin Mappings

All pin assignments are configured in the substitutions section:

- **I²C Bus A**: SDA=15, SCL=14
- **I²C Bus B**: SDA=11, SCL=7
- **I²S Audio**: LRCLK=45, BCLK=9, MCLK=16, DIN=10, DOUT=8
- **Touch**: Input=12, Reset=6
- **Display**: CS=5, DC=47, Reset=38
- **SPI**: CLK=4, MOSI=2
- **Other**: Button=0, LED=48, Battery ADC=1

## Technical Details

- **Display**: GC9A01A 240x240 round display (SPI)
- **Audio**: ES8311 DAC with I2S microphone and speaker (16kHz, 16-bit)
- **Touch**: CST816 capacitive touch controller
- **LVGL**: Version 8.x compatible
- **ESPHome**: Requires 2025.5.0 or newer

## Notes

- The light control page uses absolute brightness values (0-255) which is the native HA light.turn_on brightness parameter
- The optional number entity uses percentage (0-100%) via `brightness_pct` for easier percentage-based control
- Lambda functions convert float slider values to integers to ensure proper HA compatibility
- The `homeassistant` sensor with `attribute: brightness` keeps the slider in sync with external light changes

## File Structure

```
Ball_v2/
├── Ball_v2.yaml              # Main configuration with LVGL and light control
├── secrets.yaml.example      # WiFi credentials template
└── README.md                 # This file
```

## Credits

Based on the Spotpear V2 LVGL configuration from the espHome_LVGL repository.

## License

This configuration is part of the espHome_LVGL repository.

---

**Created:** October 2025  
**ESPHome Version:** 2025.5.0+  
**Status:** Ready for Testing
