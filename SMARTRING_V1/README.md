# SMARTRING V1 - ESPHome LVGL Voice Assistant

## ⚠️⚠️⚠️ CRITICAL COMPATIBILITY WARNING ⚠️⚠️⚠️

**THIS CONFIGURATION IS INCOMPLETE AND WILL NOT WORK WITHOUT SIGNIFICANT MODIFICATIONS**

This is an adaptation of Ball V5.3 software for SMARTRING hardware. However, there are **CRITICAL HARDWARE INCOMPATIBILITIES** that prevent this from working as-is:

### 🔴 BLOCKER: Display Hardware Not Supported

- **SMARTRING Display**: 466x466 QSPI AMOLED with CO5300 driver
- **ESPHome Support**: Does NOT support QSPI displays or CO5300 driver
- **Result**: Display will NOT initialize or show anything
- **Solution Required**: Custom ESPHome component or switch to Arduino framework

### 🟡 WARNING: Touch Controller Compatibility Unknown

- **SMARTRING Touch**: CST9217 I2C touch controller
- **ESPHome Support**: Has CST816 driver, CST9217 compatibility unknown
- **Result**: Touch may not respond
- **Solution Required**: Test and potentially develop custom component

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
- **Display**: 1.75" AMOLED 466x466 (CO5300, QSPI) ⚠️ Not supported
- **Touch**: CST9217 (I2C) ⚠️ Compatibility unknown
- **Audio**: I2S DAC ⚠️ Configuration uncertain
- **LED**: WS2812 RGB (GPIO39)
- **Additional**: IMU sensor, SD card slot

### Pin Mappings (Verified from Documentation)

#### Display (QSPI - NOT WORKING)
- GPIO7: LCD_QSPI_CS
- GPIO13: LCD_QSPI_SCL
- GPIO12: LCD_QSPI_D0
- GPIO8: LCD_QSPI_D1
- GPIO14: LCD_QSPI_D2
- GPIO9: LCD_QSPI_D3
- GPIO11: LCD_RST
- GPIO10: LCD_TE
- GPIO40: LCD_VCIEN (Backlight)

#### Touch (I2C)
- GPIO41: TP_SDA
- GPIO45: TP_SCL
- GPIO46: TP_RST
- GPIO42: TP_INT

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

Despite the hardware incompatibilities, this configuration provides:

✅ **Correct pin mappings** for SMARTRING hardware (where documented)  
✅ **Voice assistant framework** structure from Ball V5.3  
✅ **LVGL interface** framework (won't display without working driver)  
✅ **Home Assistant integration** structure  
✅ **Extensive documentation** of hardware differences  
✅ **Validation checks** throughout the code  

---

## What You Need To Do

### Before Using This Configuration:

1. ✅ **Read HARDWARE_COMPARISON.md** - Complete hardware analysis
2. ✅ **Understand the limitations** - Display will not work as-is
3. ✅ **Be prepared to develop custom components** - Or switch frameworks
4. ✅ **Have backup plan** - Consider Arduino with ESP32_Display_Panel library

### Testing Procedure:

1. **Start with basics**:
   ```bash
   esphome config SMARTRING_V1.yaml
   ```
   This will check YAML syntax (should pass)

2. **Try to compile** (will likely fail at display initialization):
   ```bash
   esphome compile SMARTRING_V1.yaml
   ```

3. **If compile succeeds, flash** (unlikely to work):
   ```bash
   esphome upload SMARTRING_V1.yaml
   ```

4. **Monitor serial output**:
   ```bash
   esphome logs SMARTRING_V1.yaml
   ```
   Look for display initialization errors

5. **Test components individually**:
   - WiFi connection (should work)
   - LED (should work)
   - Button (should work)
   - Touch (uncertain)
   - Display (will fail)
   - Audio (uncertain)

---

## Alternative Approaches

### Option 1: Wait for ESPHome Support
Wait for ESPHome to add QSPI display support and CO5300 driver. This may take time or never happen.

### Option 2: Develop Custom Components
Create custom ESPHome components for:
- QSPI display bus
- CO5300 display driver
- CST9217 touch driver (if needed)

This requires C++ knowledge and ESP-IDF experience.

### Option 3: Use Arduino Framework
The SMARTRING hardware is well-supported by Arduino with ESP32_Display_Panel library:
- Examples exist in `VIEWE-SMARTRING-og/examples/`
- Full QSPI and CO5300 support
- Proven working code

**Recommended**: Start with Arduino examples to verify hardware, then consider porting to ESPHome later if support becomes available.

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

### Display Not Working
**Cause**: QSPI and CO5300 not supported by ESPHome ili9xxx platform  
**Fix**: Requires custom component or different framework  
**Workaround**: None available in ESPHome

### Touch Not Responding
**Cause**: CST9217 may not be compatible with CST816 driver  
**Fix**: Test and potentially develop custom component  
**Workaround**: Try CST816 driver, may work if protocol similar

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
