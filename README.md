# espHome_LVGL

ESPHome configurations using LVGL (Light and Versatile Graphics Library) for ESP32-based smart home devices with displays.

## Devices

### Ball V2 - Xiaozhi Ball V2 with Light Control ⭐ NEW
ESP32-S3 based voice assistant with LVGL display and **on-screen Home Assistant light control**.

**Features:**
- 🎤 Full Home Assistant Voice Assistant integration
- 🎨 LVGL-based UI with color-coded states
- 💡 **On-screen light brightness slider (0-255)**
- 🔘 **On-screen light toggle button**
- 🔄 **Automatic sync with Home Assistant light state**
- 🔢 Optional HA number entity for percentage control
- 🔋 Battery monitoring with display
- 📱 CST816 capacitive touch screen
- 🌈 WS2812 RGB LED
- 🔊 ES8311 audio DAC with I2S

**Display:** GC9A01A 240x240 round display

**Documentation:** [Ball_v2/README.md](Ball_v2/README.md)

---

### Spotpear V2 - LVGL Voice Assistant
ESP32-S3 based voice assistant with LVGL display (no light control).

**Features:**
- 🎤 Home Assistant Voice Assistant
- 🎨 LVGL-based UI
- 🔋 Battery monitoring
- 📱 Touch screen support
- 🔊 Audio DAC with speaker

**Display:** GC9A01A 240x240 round display

**Documentation:** [Spotpear-v2/README.md](Spotpear-v2/README.md)

---

### Mix V1
ESP32 configuration for Mix V1 device.

**Documentation:** [Mix_V1/Mix_V1.yaml](Mix_V1/Mix_V1.yaml)

---

### WS-P4-Box
Waveshare P4 Panel configuration.

**Documentation:** [WS-P4-Box/README.md](WS-P4-Box/)

---

## Quick Start

### Ball V2 with Light Control

1. **Clone and configure:**
   ```bash
   git clone https://github.com/Fear2Die/espHome_LVGL.git
   cd espHome_LVGL/Ball_v2
   cp secrets.yaml.example secrets.yaml
   # Edit secrets.yaml with your WiFi credentials
   ```

2. **Configure light entity:**
   Edit `Ball_v2.yaml` and replace `light.YOUR_LIGHT_ENTITY` with your actual Home Assistant light entity ID (in 4 places).

3. **Flash the device:**
   ```bash
   esphome run Ball_v2.yaml
   ```

4. **Enable HA actions (REQUIRED):**
   - Go to Settings → Devices & Services → ESPHome in Home Assistant
   - Find Ball V2 device and click Configure
   - Check "Allow the device to perform Home Assistant actions"
   - Click Submit

5. **Reboot and enjoy!**

### Spotpear V2

1. **Clone and configure:**
   ```bash
   git clone https://github.com/Fear2Die/espHome_LVGL.git
   cd espHome_LVGL/Spotpear-v2
   cp secrets.yaml.example secrets.yaml
   # Edit secrets.yaml with your WiFi credentials
   ```

2. **Flash the device:**
   ```bash
   esphome run Spotpear_v2.yaml
   ```

## Features Comparison

| Feature | Ball V2 | Spotpear V2 |
|---------|---------|-------------|
| Voice Assistant | ✅ | ✅ |
| LVGL Display | ✅ | ✅ |
| Touch Screen | ✅ | ✅ |
| Battery Monitor | ✅ | ✅ |
| Light Control Slider | ✅ ⭐ | ❌ |
| Light Toggle Button | ✅ ⭐ | ❌ |
| HA Brightness Sync | ✅ ⭐ | ❌ |
| Number Entity | ✅ ⭐ | ❌ |

## Requirements

- **ESPHome:** 2025.5.0 or newer
- **Home Assistant:** Any recent version
- **Hardware:** ESP32-S3 based device with display
- **For Light Control:** HA device must have "Allow device to perform Home Assistant actions" enabled

## Repository Structure

```
espHome_LVGL/
├── Ball_v2/              # NEW: Ball V2 with light control
│   ├── Ball_v2.yaml
│   ├── README.md
│   ├── CHANGES.md
│   ├── SUMMARY.md
│   └── secrets.yaml.example
├── Spotpear-v2/          # Spotpear V2 voice assistant
│   ├── Spotpear_v2.yaml
│   ├── README.md
│   └── ...
├── Mix_V1/               # Mix V1 device
└── WS-P4-Box/            # Waveshare P4 panel
```

## Technologies

- **ESPHome:** Open-source system for ESP32/ESP8266 devices
- **LVGL:** Light and Versatile Graphics Library for embedded displays
- **Home Assistant:** Open-source home automation platform
- **ESP-IDF:** Espressif IoT Development Framework

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## License

This project is open source. Individual configurations may have their own licenses.

## Credits

- ESPHome community
- LVGL developers
- Home Assistant community
- Original device manufacturers

---

**Latest Addition:** Ball V2 with LVGL light control (October 2025)