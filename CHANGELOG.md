# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Repository Updates
- Complete README overhaul with professional structure
- Added project status indicators (Active/Beta/Legacy/Maintenance)
- Created DEPRECATED.md for legacy versions
- Added CONTRIBUTING.md with contribution guidelines
- Updated .gitignore for better maintenance
- Removed backup files and cleanup

---

## Projects

### Ball V5.3 - [2025-01-XX]

#### Added
- Live album art display from media players
- Automatic album artwork updates
- Better volume control interface
- Fixed button glyph characters

#### Fixed
- Button overlap issue (navigation buttons repositioned to y=-10)
- Touch accuracy on circular display
- 'None' error in light brightness sensor
- Missing Unicode characters in font

#### Changed
- Removed non-functional camera page
- Simplified navigation (Media and Weather only)
- Updated to ESPHome 2025.5.0+ requirement

#### Documentation
- Comprehensive 8-file documentation set
- Quick start guide (3 minutes)
- Installation guide with troubleshooting
- Quick reference cheat sheet
- Layout customization guide
- Version comparison guide
- Complete index/navigator

**Full Details:** [Xiaozhi Ball V2/Ball_v5.3/CHANGES_V5.3.md](Xiaozhi%20Ball%20V2/Ball_v5.3/CHANGES_V5.3.md)

---

### SMARTRING V1 - [2024-10-XX]

#### Added
- Initial hardware port of Ball V5.3 to SMARTRING hardware
- Support for 466x466 QSPI AMOLED display (CO5300 driver)
- CST820 touch controller support
- Pin mapping documentation
- Hardware comparison documentation

#### Status
- ⚠️ Beta/Experimental
- ✅ Display working via mipi_spi platform
- ✅ Touch working via cst816 driver compatibility
- ⚠️ Audio configuration needs testing

#### Known Issues
- Voice assistant functionality not fully tested
- Audio pin configuration requires verification
- Microphone input needs hardware testing

**Full Details:** [SMARTRING/SMARTRING_V1/README.md](SMARTRING/SMARTRING_V1/README.md)

---

### Ball V5.2 - [2024-XX-XX] - LEGACY

#### Added
- Easy entity configuration at top of YAML
- Camera page integration
- Fixed glyph rendering issues
- Multiple substitutions support

#### Status
- 📦 **DEPRECATED** - Use Ball V5.3 instead
- Known button overlap issue (fixed in V5.3)
- No album art support (added in V5.3)

**Migration Path:** [Xiaozhi Ball V2/Ball_v5.3/CHANGES_V5.3.md](Xiaozhi%20Ball%20V2/Ball_v5.3/CHANGES_V5.3.md)

---

### Ball V5 - [2024-XX-XX] - LEGACY

#### Added
- Multi-page interface
- Media player page
- Weather display page
- Fixed slider flickering issues

#### Status
- 📦 **DEPRECATED** - Use Ball V5.3 instead

---

### Ball V4 - [2024-XX-XX] - LEGACY

#### Added
- Instant brightness updates
- Improved light control response
- Enhanced UI feedback

#### Status
- 📦 **DEPRECATED** - Use Ball V5.3 instead

---

### Ball V3 - [2024-XX-XX] - LEGACY

#### Added
- Basic light control interface
- LVGL integration
- Touch screen support

#### Status
- 📦 **DEPRECATED** - Use Ball V5.3 instead

---

### WS-P4-Box - MAINTENANCE MODE

#### Status
- ⚙️ Maintenance mode
- WaveShare ESP32-P4 Smart 86 Box configuration
- Minimal updates only

#### Credits
- Based on [nishad2m8/WaveShare-ESP32-P4-Smart-86-Box](https://github.com/nishad2m8/WaveShare-ESP32-P4-Smart-86-Box)

**Full Details:** [WS-P4-Box/README.md](WS-P4-Box/README.md)

---

## Version Comparison Summary

| Version | Status | Display | Features | Recommended |
|---------|--------|---------|----------|-------------|
| Ball V5.3 | ✅ Active | 240x240 | Full (Album Art) | ⭐ **YES** |
| SMARTRING V1 | ⚠️ Beta | 466x466 | Full (Testing) | If you have hardware |
| WS-P4-Box | ⚙️ Maintenance | - | Voice & Control | If you have hardware |
| Ball V5.2 | 📦 Legacy | 240x240 | Partial | No - use V5.3 |
| Ball V5 | 📦 Legacy | 240x240 | Basic | No - use V5.3 |
| Ball V4 | 📦 Legacy | 240x240 | Basic | No - use V5.3 |
| Ball V3 | 📦 Legacy | 240x240 | Basic | No - use V5.3 |

---

## Migration Guides

### From Ball V5.2 to V5.3
See [Xiaozhi Ball V2/Ball_v5.3/CHANGES_V5.3.md](Xiaozhi%20Ball%20V2/Ball_v5.3/CHANGES_V5.3.md)

**Key Changes:**
- Remove camera_entity from substitutions
- Replace YAML file
- Flash device
- Album art works automatically

### From Ball V5.x to V5.3
**Recommendation:** Fresh configuration recommended

**Steps:**
1. Backup current configuration
2. Use Ball V5.3 as base
3. Copy your secrets.yaml
4. Update entity IDs at top of file
5. Flash and test

---

## Deprecation Notices

### Ball V5.2 and Earlier
**Deprecated:** January 2025  
**Reason:** Superseded by Ball V5.3  
**Action:** Migrate to Ball V5.3 for new projects  
**Support:** Legacy versions kept for reference only

---

## Links

- **Repository:** https://github.com/Fear2Die/ESPHome-Projects
- **Issues:** https://github.com/Fear2Die/ESPHome-Projects/issues
- **ESPHome:** https://esphome.io
- **Home Assistant:** https://www.home-assistant.io
- **LVGL:** https://lvgl.io

---

**Note:** Individual project folders contain their own detailed CHANGES.md files with specific version history.
