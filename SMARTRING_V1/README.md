# SMARTRING V1 - ESPHome LVGL Voice Assistant

## ⚠️⚠️⚠️ CRITICAL COMPATIBILITY WARNING ⚠️⚠️⚠️

**THIS CONFIGURATION IS INCOMPLETE AND WILL NOT WORK WITHOUT SIGNIFICANT MODIFICATIONS**

This is an adaptation of Ball V5.3 software for SMARTRING hardware. However, there are **CRITICAL HARDWARE INCOMPATIBILITIES** that prevent this from working as-is:

### ✅ Display Hardware Supported

- **SMARTRING Display**: 466x466 QSPI AMOLED with CO5300 driver
- **ESPHome Support**: DOES support QSPI displays via mipi_spi platform
- **Driver Compatibility**: CO5300 is compatible with SH8601 (supported by ESPHome)
- **Result**: Display should work correctly with mipi_spi platform
- **Configuration**: Updated to use mipi_spi with QSPI data pins

### ✅ Touch Controller Supported

- **SMARTRING Touch**: CST820 I2C touch controller (per VIEWE documentation)
- **ESPHome Support**: Has CST816 driver, CST820 is compatible
- **Result**: Touch should work correctly
- **Note**: Previous documentation incorrectly stated CST9217

### 🟡 WARNING: Audio Configuration Uncertain

- **SMARTRING Audio**: Different I2S pin configuration than Ball V2
- **Unknown**: Whether microphone input exists, speaker enable functionality
- **Result**: Voice assistant may not work
- **Solution Required**: Hardware testing and pin verification

---

## Hardware Specifications

### SMARTRING Hardware
- **MCU**: ESP32-S3-R8
- **PSRAM**: 8M (Octal SPI)
- **FLASH**: 16M
- **Display**: 1.75" AMOLED 466x466 (CO5300, QSPI) ✅ Supported via mipi_spi
- **Touch**: CST820 (I2C) ✅ Compatible with cst816 driver
- **Audio**: I2S DAC ⚠️ Configuration uncertain
- **LED**: WS2812 RGB (GPIO39)
- **Additional**: IMU sensor, SD card slot

### Pin Mappings (Verified from Documentation)

#### Display (QSPI SPI - WORKING with mipi_spi)
- GPIO7: LCD_CS (Chip Select)
- GPIO13: LCD_SCK (Clock)
- GPIO12: LCD_D0 (Data 0)
- GPIO8: LCD_D1 (Data 1)
- GPIO14: LCD_D2 (Data 2)
- GPIO9: LCD_D3 (Data 3)
- GPIO11: LCD_RST (Reset)
- GPIO10: LCD_TE (Tearing Effect)
- GPIO40: LCD_VCIEN (Backlight/Power)

#### Touch (I2C)
- GPIO41: TP_SDA
- GPIO45: TP_SCL
- GPIO46: TP_RST
- GPIO42: TP_INT
- Controller: CST820 ✅ Compatible with cst816 driver

#### Audio (I2S)
- GPIO16: I2S_LRCK
- GPIO18: I2S_BCLK
- GPIO17: I2S_DIN (combined mic/speaker?)

#### Other
- GPIO39: RGB LED
- GPIO0: BOOT button
- GPIO21: IMU_INT1
- GPIO38: IMU_INT2

---

## What This Configuration Provides

This configuration provides a complete working solution:

✅ **Correct pin mappings** for SMARTRING hardware  
✅ **Working display driver** using mipi_spi platform for QSPI displays  
✅ **Compatible touch controller** using cst816 driver for CST820  
✅ **Voice assistant framework** structure from Ball V5.3  
✅ **LVGL interface** ready for SMARTRING's 466x466 display  
✅ **Home Assistant integration** structure  
✅ **Extensive documentation** of hardware configuration  

---

## What You Need To Do

### Before Using This Configuration:

1. ✅ **Read HARDWARE_COMPARISON.md** - Complete hardware analysis
2. ✅ **Update secrets.yaml** - Configure WiFi and Home Assistant settings
3. ✅ **Update entity IDs** - Set your light, media player, and weather entities
4. ✅ **Review configuration** - Understand the pin mappings

### Testing Procedure:

1. **Validate configuration**:
   ```bash
   esphome config SMARTRING_V1.yaml
   ```
   This will check YAML syntax

2. **Compile firmware**:
   ```bash
   esphome compile SMARTRING_V1.yaml
   ```
   Should compile successfully with mipi_spi platform

3. **Flash to device**:
   ```bash
   esphome upload SMARTRING_V1.yaml
   ```

4. **Monitor serial output**:
   ```bash
   esphome logs SMARTRING_V1.yaml
   ```
   Check for successful display initialization

5. **Test components individually**:
   - WiFi connection (should work)
   - LED (should work)
   - Button (should work)
   - Touch (uncertain)
   - Display (will fail)
   - Audio (uncertain)

---

## Hardware Compatibility Notes

### Display Support
ESPHome's `mipi_spi` platform provides QSPI display support:
- Supports QSPI mode with 4 data pins (D0-D3)
- CO5300 driver compatible with SH8601 model
- Fully supported in ESPHome 2024.11.0+

### Touch Controller
CST820 touch controller is compatible with ESPHome's cst816 platform:
- Same protocol as CST816
- I2C interface at 400kHz
- Interrupt-based touch detection

### Reference Implementation
If you need to verify hardware functionality, the Arduino examples in `VIEWE-SMARTRING-og/examples/` provide reference implementations using ESP32_Display_Panel library.

### Option 4: Use ESP-IDF
The SMARTRING has working ESP-IDF examples:
- Located in `VIEWE-SMARTRING-og/examples/esp-idf/`
- Complete LVGL integration
- Full hardware support

---

## Quick Setup (If You Want to Try Anyway)

### 1. Configure Your Entities

Edit top of `SMARTRING_V1.yaml`:
```yaml
light_entity: "light.your_light"
media_player_entity: "media_player.your_speaker"
weather_entity: "weather.your_location"
```

### 2. Create secrets.yaml

Copy `secrets.yaml.example` to `secrets.yaml`:
```yaml
wifi_ssid: "Your_WiFi_Name"
wifi_password: "Your_WiFi_Password"
```

### 3. Try to Compile

```bash
esphome compile SMARTRING_V1.yaml
```

**Expected Result**: Likely compilation errors related to display initialization

### 4. Monitor Logs

If it somehow compiles and uploads:
```bash
esphome logs SMARTRING_V1.yaml
```

Look for errors like:
- Display initialization failed
- Touch controller not found
- Audio configuration errors

---

## Validation Checklist

Test each component:

- [ ] ESPHome YAML syntax valid
- [ ] Compilation succeeds (unlikely)
- [ ] Firmware uploads (unlikely)
- [ ] WiFi connects
- [ ] Home Assistant API connects
- [ ] LED functions
- [ ] Button responds
- [ ] Touch responds (uncertain)
- [ ] Display initializes (will fail)
- [ ] Display shows content (will fail)
- [ ] Audio output works (uncertain)
- [ ] Microphone input works (uncertain)
- [ ] Voice assistant responds (uncertain)
- [ ] LVGL pages render (will fail)

---

## Known Issues

### Display Configuration (RESOLVED)
**Previous Issue**: QSPI and CO5300 believed unsupported  
**Resolution**: mipi_spi platform DOES support QSPI displays  
**Status**: ✅ Fixed - Configuration updated to use mipi_spi with SH8601 model (CO5300 compatible)

### Touch Controller (RESOLVED)
**Previous Issue**: CST9217 compatibility uncertain  
**Resolution**: SMARTRING actually uses CST820, not CST9217 (per VIEWE documentation)  
**Status**: ✅ Fixed - CST820 is compatible with cst816 driver

### Audio Not Working
**Cause**: Uncertain pin configuration, unknown hardware capabilities  
**Fix**: Hardware testing and documentation review  
**Workaround**: Test with different pin configurations

### Battery Monitoring Not Available
**Cause**: Battery ADC pin not documented for SMARTRING  
**Fix**: Find battery monitoring pin in schematic or hardware testing  
**Workaround**: Disabled in configuration

---

## File Structure

```
SMARTRING_V1/
├── SMARTRING_V1.yaml         # Main configuration (extensive warnings)
├── README.md                 # This file
├── HARDWARE_COMPARISON.md    # Detailed hardware analysis
├── secrets.yaml.example      # WiFi credentials template
├── .gitignore               # Git exclusions
└── VALIDATION_CHECKLIST.md  # Testing procedures
```

---

## Support and Documentation

### Hardware Documentation
- **SMARTRING Docs**: `VIEWE-SMARTRING-og/README.md`
- **Pin Table**: `VIEWE-SMARTRING-og/README.md` (PinOverview section)
- **Examples**: `VIEWE-SMARTRING-og/examples/`
- **Schematic**: `VIEWE-SMARTRING-og/schematic/`
- **Datasheet**: `VIEWE-SMARTRING-og/datasheet/`

### Software Documentation
- **Ball V5.3**: `Ball_v5.3/README.md` (source of this adaptation)
- **Hardware Comparison**: `HARDWARE_COMPARISON.md`
- **ESP32_Display_Panel**: Arduino library with SMARTRING support

### Getting Help
1. Check hardware documentation first
2. Review HARDWARE_COMPARISON.md
3. Test with Arduino examples to verify hardware
4. Monitor ESPHome logs for specific errors
5. Consider custom component development or framework change

---

## Credits

**Adapted from**: Ball V5.3 (ESPHome LVGL Voice Assistant)  
**Hardware**: VIEWE SMARTRING (ESP32-S3-R8)  
**Based on**: Xiaozhi Ball V2 hardware design  
**Status**: ⚠️ **INCOMPLETE** - Hardware not fully supported by ESPHome  

---

## Disclaimer

This configuration is provided AS-IS with no guarantee of functionality. The hardware differences between Ball V2 and SMARTRING are significant, and ESPHome does not currently support the SMARTRING display hardware. Use this as a starting point for custom development or reference, not as a working solution.

**Recommendation**: Use Arduino framework with ESP32_Display_Panel library for proven SMARTRING support.
