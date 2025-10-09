# ESPHome LVGL Projects

Professional ESPHome configurations using LVGL (Light and Versatile Graphics Library) for ESP32-based smart home devices with touchscreen displays.

[![ESPHome](https://img.shields.io/badge/ESPHome-2025.5.0+-blue.svg)](https://esphome.io)
[![Home Assistant](https://img.shields.io/badge/Home%20Assistant-Compatible-green.svg)](https://www.home-assistant.io)
[![LVGL](https://img.shields.io/badge/LVGL-8.4-orange.svg)](https://lvgl.io)

---

## 🌟 Featured Projects

### 🎯 Ball V5.3 - Complete Smart Home Control ⭐ **LATEST**
> **Status:** ✅ Active | **Last Updated:** January 2025 | **Hardware:** Xiaozhi Ball V2 (ESP32-S3)

Advanced voice assistant with LVGL interface featuring **live album art**, smart home controls, and multi-page navigation.

**✨ Key Features:**
- 🎵 **Live Album Art Display** - Updates automatically with media playback
- 💡 **Light Control** - Brightness slider (0-100%) and toggle button
- 🌤️ **Weather Display** - Current conditions and forecast
- 🎤 **Voice Assistant** - Full Home Assistant integration
- 🔧 **Layout Fixes** - Button overlap resolved, optimized touch zones
- 📱 **240x240 Round Display** - GC9A01A with CST816 touch
- 🔋 **Battery Monitoring** - Real-time battery percentage

**📚 Documentation:** [Ball_v5.3/README.md](Xiaozhi%20Ball%20V2/Ball_v5.3/README.md) | [Quick Start](Xiaozhi%20Ball%20V2/Ball_v5.3/QUICK_START.md) | [Installation Guide](Xiaozhi%20Ball%20V2/Ball_v5.3/INSTALLATION.md)

---

### 🎯 SMARTRING V1 - High-Resolution AMOLED Port 🆕
> **Status:** ⚠️ Beta/Experimental | **Last Updated:** October 2024 | **Hardware:** VIEWE SMARTRING (ESP32-S3)

Port of Ball V5.3 software to SMARTRING hardware with 466x466 QSPI AMOLED display.

**✨ Key Features:**
- 📱 **High Resolution** - 1.75" AMOLED 466x466 display (CO5300 driver)
- ✅ **Display Working** - QSPI support via mipi_spi platform
- ✅ **Touch Working** - CST820 compatible with cst816 driver
- ⚠️ **Audio Experimental** - Voice assistant configuration needs testing
- 🎨 **LVGL Interface** - Adapted from Ball V5.3
- 💪 **ESP32-S3-R8** - 8M PSRAM, 16M Flash

**📚 Documentation:** [SMARTRING_V1/README.md](SMARTRING/SMARTRING_V1/README.md) | [Hardware Comparison](SMARTRING/SMARTRING_V1/HARDWARE_COMPARISON.md)

---

### 📦 Other Projects

| Project | Status | Description |
|---------|--------|-------------|
| **WS-P4-Box** | ⚙️ Maintenance | WaveShare ESP32-P4 Smart 86 Box configuration |
| **Ball v5.2** | 📦 Legacy | Previous version (use v5.3 instead) |
| **Ball v5** | 📦 Legacy | Older version (use v5.3 instead) |
| **Ball v4** | 📦 Legacy | Older version (use v5.3 instead) |
| **Ball v3** | 📦 Legacy | Older version (use v5.3 instead) |

---

## 🚀 Quick Start (Ball V5.3)

### Prerequisites
- ESPHome 2025.5.0 or newer
- Home Assistant (any recent version)
- Xiaozhi Ball V2 hardware (or compatible ESP32-S3 device)

### Installation

```bash
# 1. Clone repository
git clone https://github.com/Fear2Die/ESPHome-Projects.git
cd ESPHome-Projects/"Xiaozhi Ball V2"/Ball_v5.3

# 2. Copy and configure secrets
cp secrets.yaml.example secrets.yaml
# Edit secrets.yaml with your WiFi and Home Assistant credentials

# 3. Configure entity IDs (in Ball_v5.3.yaml, around line 20)
# Replace:
#   light.YOUR_LIGHT_ENTITY
#   media_player.YOUR_MEDIA_PLAYER_ENTITY
#   weather.YOUR_WEATHER_ENTITY

# 4. Flash to device
esphome run Ball_v5.3.yaml

# 5. Enable Home Assistant actions (REQUIRED)
# Settings → Devices & Services → ESPHome → Ball V5.3 → Configure
# ✓ Check "Allow the device to perform Home Assistant actions"
```

**📖 Detailed Guide:** [Xiaozhi Ball V2/Ball_v5.3/QUICK_START.md](Xiaozhi%20Ball%20V2/Ball_v5.3/QUICK_START.md)

---

## 📊 Project Comparison

| Feature | Ball V5.3 | SMARTRING V1 | WS-P4-Box |
|---------|-----------|--------------|-----------|
| **Status** | ✅ Active | ⚠️ Beta | ⚙️ Maintenance |
| **Voice Assistant** | ✅ | ⚠️ | ✅ |
| **Light Control** | ✅ | ✅ | ✅ |
| **Media Player** | ✅ | ✅ | ❌ |
| **Album Art** | ✅ Live | ✅ Live | ❌ |
| **Weather** | ✅ | ✅ | ❌ |
| **Display Size** | 240x240 | 466x466 | - |
| **Display Type** | LCD | AMOLED | - |
| **Touch** | ✅ | ✅ | ✅ |
| **Battery Monitor** | ✅ | ✅ | ❌ |
| **Documentation** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐ |

---

## 🎯 Choosing the Right Project

### Use Ball V5.3 if you want:
- ✅ Most stable and feature-complete configuration
- ✅ Comprehensive documentation
- ✅ Complete smart home control (lights, media, weather)
- ✅ Live album art from media players
- ✅ Easy entity configuration

### Use SMARTRING V1 if you want:
- ⚠️ Higher resolution AMOLED display
- ⚠️ Newer hardware with more resources
- ⚠️ Don't mind experimental/testing phase
- ⚠️ Can help with audio configuration testing

### Use WS-P4-Box if you want:
- ⚙️ WaveShare ESP32-P4 Smart 86 Box hardware support
- ⚙️ Community-maintained configuration

---

## 📁 Repository Structure

```
ESPHome-Projects/
├── Xiaozhi Ball V2/      🎯 Xiaozhi Ball Projects
│   ├── Ball_v5.3/        ⭐ RECOMMENDED - Latest version
│   │   ├── Ball_v5.3.yaml
│   │   ├── README.md
│   │   ├── QUICK_START.md
│   │   ├── INSTALLATION.md
│   │   ├── QUICK_REFERENCE.md
│   │   ├── INDEX.md      # Documentation navigator
│   │   └── secrets.yaml.example
│   └── Older_Versions/   📦 LEGACY versions (v5.2, v5, v4, v3)
│
├── SMARTRING/            🔴 SMARTRING Projects
│   ├── SMARTRING_V1/     🆕 NEW HARDWARE PORT
│   │   ├── SMARTRING_V1.yaml
│   │   ├── README.md
│   │   ├── HARDWARE_COMPARISON.md
│   │   └── secrets.yaml.example
│   └── VIEWE-SMARTRING/  📚 Original hardware documentation
│
└── WS-P4-Box/            ⚙️ MAINTENANCE MODE
    └── WS-P4-Box/        WaveShare ESP32-P4 configurations
```

---

## 🛠️ Technologies Used

| Technology | Purpose | Version |
|------------|---------|---------|
| **ESPHome** | Device firmware framework | 2025.5.0+ |
| **LVGL** | Graphics library | 8.4 |
| **Home Assistant** | Home automation platform | Latest |
| **ESP-IDF** | ESP32 development framework | 5.x |
| **Python** | Build scripts | 3.8+ |

---

## 📚 Documentation

### Ball V5.3 Complete Documentation
- **[README.md](Xiaozhi%20Ball%20V2/Ball_v5.3/README.md)** - Main documentation and features
- **[QUICK_START.md](Xiaozhi%20Ball%20V2/Ball_v5.3/QUICK_START.md)** - 3-minute setup guide
- **[INSTALLATION.md](Xiaozhi%20Ball%20V2/Ball_v5.3/INSTALLATION.md)** - Step-by-step installation
- **[QUICK_REFERENCE.md](Xiaozhi%20Ball%20V2/Ball_v5.3/QUICK_REFERENCE.md)** - One-page cheat sheet
- **[INDEX.md](Xiaozhi%20Ball%20V2/Ball_v5.3/INDEX.md)** - Documentation navigator
- **[CHANGES_V5.3.md](Xiaozhi%20Ball%20V2/Ball_v5.3/CHANGES_V5.3.md)** - Version 5.3 changelog
- **[LAYOUT.md](Xiaozhi%20Ball%20V2/Ball_v5.3/LAYOUT.md)** - UI layout and customization
- **[COMPARISON.md](Xiaozhi%20Ball%20V2/Ball_v5.3/COMPARISON.md)** - Version comparison

### SMARTRING V1 Documentation
- **[README.md](SMARTRING/SMARTRING_V1/README.md)** - Setup and compatibility info
- **[HARDWARE_COMPARISON.md](SMARTRING/SMARTRING_V1/HARDWARE_COMPARISON.md)** - Hardware details

---

## 🔧 Requirements

### Software
- **ESPHome:** Version 2025.5.0 or newer required
- **Home Assistant:** Any recent version compatible
- **Python:** 3.8+ (for ESPHome)

### Hardware (Ball V5.3)
- **MCU:** ESP32-S3
- **Display:** GC9A01A 240x240 round LCD
- **Touch:** CST816 capacitive touch controller
- **Audio:** ES8311 DAC with I2S
- **LED:** WS2812 RGB
- **Battery:** LiPo with monitoring

### Permissions
- **Home Assistant Actions:** Must be enabled for light/media control
- **API Access:** Required for entity state synchronization

---

## 🆘 Support & Troubleshooting

### Common Issues

1. **"Allow device to perform Home Assistant actions" not enabled**
   - Go to Settings → Devices & Services → ESPHome
   - Find your device → Configure
   - Enable the checkbox

2. **Entities not updating**
   - Check entity IDs match exactly (case-sensitive)
   - Verify entities exist in Home Assistant
   - Check API connection is working

3. **Display issues**
   - Verify correct ESPHome version (2025.5.0+)
   - Check display pins in configuration
   - Review logs for errors

### Getting Help
- 📖 Check project-specific documentation
- 🐛 [Open an issue](https://github.com/Fear2Die/ESPHome-Projects/issues)
- 💬 ESPHome Discord community
- 🏠 Home Assistant community forums

---

## 🤝 Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Test thoroughly
4. Submit a pull request

---

## 📄 License

This project is open source. Individual configurations may have their own licenses.

---

## 🙏 Credits

### Original Hardware Repositories
- **Xiaozhi Ball** - Based on [RealDeco/xiaozhi-esphome](https://github.com/RealDeco/xiaozhi-esphome)
- **SMARTRING** - Hardware and documentation from [VIEWESMART/VIEWE-SMARTRING](https://github.com/VIEWESMART/VIEWE-SMARTRING)
- **WS-P4-Box** - Based on [nishad2m8/WaveShare-ESP32-P4-Smart-86-Box](https://github.com/nishad2m8/WaveShare-ESP32-P4-Smart-86-Box)

### Community & Framework
- **ESPHome Community** - Framework and support
- **LVGL Developers** - Graphics library
- **Home Assistant Community** - Integration and automation
- **Device Manufacturers** - Xiaozhi Ball V2, VIEWE SMARTRING, WaveShare
- **Contributors** - All project contributors

---

## 📅 Version History

| Version | Date | Highlights |
|---------|------|------------|
| **Ball V5.3** | January 2025 | Live album art, layout fixes, button overlap resolved |
| **SMARTRING V1** | October 2024 | AMOLED port, 466x466 display |
| **Ball V5.2** | 2024 | Easy configuration, camera page |
| **Ball V5** | 2024 | Multi-page interface |

---

**⭐ Recommended:** Start with [Xiaozhi Ball V2/Ball_v5.3](Xiaozhi%20Ball%20V2/Ball_v5.3/README.md) for the best experience!

**Last Updated:** January 2025