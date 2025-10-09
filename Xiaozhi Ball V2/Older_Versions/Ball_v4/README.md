# ESPHome Xiaozhi Ball V4 - LVGL with Enhanced Light Control

Ball V4 is an enhanced version of Ball V3 with improved light control features and better user experience.

## What's New in Ball V4

### Enhanced Light Control
- **Instant Brightness Updates**: Brightness changes as you move the slider (no need to release)
- **Percentage-Based Brightness**: Slider now uses 0-100% instead of 0-255 for easier understanding
- **Live Feedback**: Brightness percentage updates in real-time as you adjust the slider

### Improved Voice Assistant
- **Touch Screen Doesn't Activate Assistant**: Touching the screen no longer triggers voice assistant
- **Button-Only Activation**: Use the physical button to activate voice assistant
- **Prevents Accidental Activation**: No more unwanted assistant triggers when using controls

### Better Screen Layout
- **Optimized for 240x240**: All controls fit within the screen without scrolling
- **Time Display**: Shows current time in HH:MM format in top-left corner
- **Compact Layout**: Controls are better positioned for single-screen view

## Features

### Voice Assistant
- **LVGL Display System**: Clean, modern UI with colored pages for different states
- **Home Assistant Voice Assistant**: Full voice assistant integration with wake word detection
- **Physical Button Activation**: Press the button to activate (screen touch no longer activates)
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

### Enhanced Light Control
- **Instant Brightness Slider**: On-screen slider (0-100%) with real-time updates
- **Toggle Button**: Checkable button to toggle the light on/off
- **External Sync**: Slider automatically updates when the light changes externally (via HA app, voice commands, etc.)
- **HA Number Entity**: Percentage-based (0-100%) control visible in Home Assistant UI
- **Live Brightness Display**: Shows current brightness percentage as you adjust

### Display Features
- **Time Display**: Current time in HH:MM format (top-left)
- **Battery Indicator**: Battery percentage (top-right, toggle with long press)
- **Status Label**: Shows current state (top-center)
- **No Scrolling**: All controls fit within 240x240 screen

## Hardware

This configuration is designed for the **Xiaozhi Ball V2** device with:
- ESP32-S3 microcontroller
- GC9A01A 240x240 round display
- CST816 touch screen
- I2S microphone and speaker
- WS2812 RGB LED
- Battery monitoring

## Configuration

### 1. Clone and Setup

```bash
git clone https://github.com/Fear2Die/espHome_LVGL.git
cd espHome_LVGL/Ball_v4
```

### 2. Configure WiFi Credentials

Copy the secrets example file and edit it:

```bash
cp secrets.yaml.example secrets.yaml
# Edit secrets.yaml with your WiFi credentials
```

### 3. Configure your light entity

**IMPORTANT:** Before flashing, replace `light.YOUR_LIGHT_ENTITY` with your actual Home Assistant light entity ID in four places in `Ball_v4.yaml`:

1. **Home Assistant sensor** (around line 213):
   ```yaml
   - platform: homeassistant
     id: ha_light_brightness
     entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

2. **Slider on_value action on Ready page** (around line 1070):
   ```yaml
   on_value:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

3. **Button on_click action on Ready page** (around line 1108):
   ```yaml
   on_click:
     - homeassistant.action:
         action: light.toggle
         data:
           entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

4. **Number entity** (around line 873):
   ```yaml
   set_action:
     - homeassistant.action:
         action: light.turn_on
         data:
           entity_id: light.YOUR_LIGHT_ENTITY  # ← Change this
   ```

Example: If your light is `light.living_room_lamp`, replace all instances of `light.YOUR_LIGHT_ENTITY` with `light.living_room_lamp`.

### 4. Flash the device

```bash
esphome run Ball_v4.yaml
```

### 5. Enable Home Assistant actions (REQUIRED)

**This step is mandatory** - without it, the light control will not work!

1. Go to **Settings → Devices & Services → ESPHome** in Home Assistant
2. Find your **Ball V4** device and click **Configure**
3. Check the box: **"Allow the device to perform Home Assistant actions"**
4. Click **Submit**

This allows the ESP device to call Home Assistant services from its automations.

### 6. Reboot the device

After enabling HA actions, reboot your Ball V4 device for changes to take effect.

## Usage

### Using the Light Control

The light control widgets (brightness slider and toggle button) are integrated directly into the **Ready page** (`idle_page`), which is the default display when the device is idle and ready for voice commands.

1. **Brightness Slider**: 
   - Touch and drag the slider to adjust brightness (0-100%)
   - Brightness changes **instantly** as you move the slider
   - The percentage updates in real-time below the slider
   - The slider automatically updates if the light is changed elsewhere

2. **Toggle Button**: 
   - Tap to toggle the light on/off
   - Works with any light state

3. **Number Entity** (optional):
   - Visible in Home Assistant as "Ball V4 Light Brightness"
   - Uses percentage (0-100%) for easier control
   - Useful for automations and quick adjustments from HA dashboard

### Using the Voice Assistant

- **Physical Button**: Press the button to activate voice assistant
- **Screen Touch**: Touching the screen will NOT activate voice assistant (only controls)
- **Wake Word**: Say your configured wake word (default: "Alexa", "Hey Jarvis", or "Okay Nabu")

### Time Display

- **Location**: Top-left corner of Ready page
- **Format**: HH:MM (24-hour format)
- **Updates**: Every minute automatically

### Battery Display

- **Location**: Top-right corner
- **Toggle**: Long-press (1+ second) on the screen to show/hide
- **Display**: Shows percentage when enabled

## Troubleshooting

### Light control not working

1. **Check HA permissions**: Settings → Devices & Services → ESPHome → Ball V4 → Configure → Enable "Allow the device to perform Home Assistant actions"
2. **Verify entity ID**: Make sure you replaced `light.YOUR_LIGHT_ENTITY` with your actual light entity ID in all four locations
3. **Check network**: Ensure Ball V4 is connected to WiFi and Home Assistant
4. **Reboot**: Try rebooting the device after configuration changes

### Slider not updating from external changes

1. **Check HA connection**: Verify device shows as "Online" in ESPHome integration
2. **Verify entity ID**: Ensure the entity ID in the sensor section matches your light
3. **Check attribute**: Some lights may not have a `brightness` attribute when off

### Time not displaying

1. **Check HA connection**: Time sensor requires Home Assistant connection
2. **Wait a moment**: Time updates at the start of each minute
3. **Reboot**: Try rebooting the device

### Voice assistant activating on touch

This issue should be fixed in Ball V4. If it still occurs:
1. **Verify you're using Ball_v4.yaml**: Check the file is Ball V4 configuration
2. **Reflash**: Make sure the latest configuration is flashed

## Differences from Ball V3

### Key Improvements
1. ✅ **Instant brightness updates** (on_value vs on_release)
2. ✅ **Percentage-based brightness** (0-100% vs 0-255)
3. ✅ **Touch doesn't activate assistant** (button only)
4. ✅ **Better screen layout** (no scrolling needed)
5. ✅ **Time display added** (HH:MM format)
6. ✅ **Live brightness feedback** (updates as you slide)

### What's the Same
- ✅ Full voice assistant functionality
- ✅ Wake word detection
- ✅ Battery monitoring
- ✅ Touch screen support
- ✅ Timer functionality
- ✅ Media player integration
- ✅ All switches and configuration options
- ✅ Startup sound
- ✅ Mute functionality

## Files

- `Ball_v4.yaml` - Main configuration file
- `secrets.yaml.example` - Template for WiFi credentials
- `README.md` - This file

## Credits

Based on:
- Original Spotpear V2 configuration
- Ball V3 with light control
- Enhanced with community feedback

## Support

For issues, questions, or contributions:
- GitHub: [Fear2Die/espHome_LVGL](https://github.com/Fear2Die/espHome_LVGL)
- Create an issue or pull request

## License

This project follows the same license as the parent repository.
