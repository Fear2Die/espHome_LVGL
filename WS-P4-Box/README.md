# WaveShare ESP32-P4 Smart 86 Box

ESPHome configuration for the WaveShare ESP32-P4 Smart 86 Box with LVGL interface.

## ⚙️ Status: Maintenance Mode

This configuration is in maintenance mode. Updates are made on an as-needed basis.

## Hardware

- **MCU**: ESP32-P4
- **Display**: MIPI DSI interface
- **Network**: Ethernet support (IP101)
- **Additional**: Audio support

## Configuration Files

```
WS-P4-Box/
├── waveshare-p4-panel.yaml    # Main configuration
├── WS-P4-Box/
│   ├── pages/
│   │   ├── main.yaml          # Main UI page
│   │   └── weather_icons.yaml # Weather icon definitions
│   └── services/
│       └── audio.yaml         # Audio configuration
└── README.md                  # This file
```

## Quick Start

### Prerequisites
- ESPHome with ESP-IDF framework support
- WaveShare ESP32-P4 Smart 86 Box hardware

### Installation

```bash
# Navigate to the WS-P4-Box directory
cd WS-P4-Box

# Flash to device
esphome run waveshare-p4-panel.yaml
```

## Features

- 🖥️ **MIPI DSI Display** - High-resolution display interface
- 🌐 **Ethernet Support** - Wired network connectivity
- 🔊 **Audio Integration** - Audio playback capability
- 🎨 **LVGL Interface** - Touch-friendly user interface
- 🌤️ **Weather Display** - Weather information with icons

## Technical Details

### Hardware Configuration
- **Board**: esp32-p4-evboard
- **Flash Size**: 32MB
- **CPU Frequency**: 400MHz
- **PSRAM Speed**: 200MHz
- **Framework**: ESP-IDF 5.4.x

### Display
- MIPI DSI interface with LDO voltage regulation
- Hardware LVGL acceleration support

### Network
- Ethernet via IP101 PHY
- Optional WiFi support

## Requirements

### Software
- **ESPHome**: Latest version with ESP-IDF support
- **ESP-IDF**: 5.4.x framework
- **Platform**: espressif32 54.03.21 or newer

### Hardware
- **Device**: WaveShare ESP32-P4 Smart 86 Box
- **Network**: Ethernet connection (recommended)

## Credits

### Original Repository
- **Original Repository**: [nishad2m8/WaveShare-ESP32-P4-Smart-86-Box](https://github.com/nishad2m8/WaveShare-ESP32-P4-Smart-86-Box) - Base configuration and hardware implementation
- **Also based on**: [alaltitov/Waveshare-ESP32-P4-86-Panel-ETH-2RO](https://github.com/alaltitov/Waveshare-ESP32-P4-86-Panel-ETH-2RO) (referenced in configuration)

### Hardware
- **Manufacturer**: WaveShare Electronics

## Support

For issues and questions:
1. Check the [original repository](https://github.com/nishad2m8/WaveShare-ESP32-P4-Smart-86-Box) for hardware-specific information
2. Consult ESPHome documentation for ESP32-P4 support
3. Review configuration files for customization options

## License

This configuration follows the license of the parent repository.

---

**Last Updated**: January 2025  
**ESPHome Framework**: ESP-IDF  
**Status**: ⚙️ Maintenance Mode
