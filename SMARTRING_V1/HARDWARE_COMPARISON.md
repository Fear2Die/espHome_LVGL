# SMARTRING vs Ball V2 Hardware Comparison

## Overview
This document compares the hardware specifications between SMARTRING and Ball V2 (Xiaozhi Ball) to ensure proper pin mapping adaptation.

## MCU Specifications

### SMARTRING
- **Chip**: ESP32-S3-R8
- **PSRAM**: 8M (Octal SPI)
- **FLASH**: 16M
- **Partition**: 16M Flash (3MB APP/9.9MB FATFS)

### Ball V2
- **Chip**: ESP32-S3
- **PSRAM**: 8M (Octal SPI)
- **FLASH**: 16M

**Status**: ✅ Compatible - Same MCU family and memory configuration

---

## Display Specifications

### SMARTRING Display
- **Size**: 1.75-inch AMOLED
- **Resolution**: 466x466 pixels
- **Screen Type**: AMOLED (IPS)
- **Driver Chip**: CO5300
- **Bus Protocol**: QSPI (Quad SPI)
- **Pin Configuration**:
  - GPIO7: LCD_QSPI_CS
  - GPIO13: LCD_QSPI_SCL
  - GPIO12: LCD_QSPI_D0
  - GPIO8: LCD_QSPI_D1
  - GPIO14: LCD_QSPI_D2
  - GPIO9: LCD_QSPI_D3
  - GPIO11: LCD_RST
  - GPIO10: LCD_TE (Tearing Effect)
  - GPIO40: LCD_VCIEN (Backlight/Power)

### Ball V2 Display
- **Size**: 240x240
- **Resolution**: 240x240 pixels
- **Driver Chip**: GC9A01A
- **Bus Protocol**: SPI
- **Pin Configuration**:
  - GPIO5: LCD_CS
  - GPIO4: SPI_CLK
  - GPIO2: SPI_MOSI
  - GPIO47: LCD_DC
  - GPIO38: LCD_RST
  - GPIO42: Backlight

**Status**: ⚠️ MAJOR CHANGES REQUIRED
- Different display protocol (QSPI vs SPI)
- Different resolution (466x466 vs 240x240)
- Different driver chip (CO5300 vs GC9A01A)
- Different pin mappings
- **ESPHome Limitation**: ESPHome may not support QSPI displays or CO5300 driver
- **Recommendation**: This requires investigation of ESPHome display driver support

---

## Touch Screen Specifications

### SMARTRING Touch
- **Touch Chip**: CST9217
- **Bus Protocol**: I2C
- **Pin Configuration**:
  - GPIO45: TP_SCL
  - GPIO41: TP_SDA
  - GPIO46: TP_RST
  - GPIO42: TP_INT

### Ball V2 Touch
- **Touch Chip**: CST816
- **Bus Protocol**: I2C
- **Pin Configuration**:
  - GPIO14: SCL (I2C Bus A)
  - GPIO15: SDA (I2C Bus A)
  - GPIO6: Touch Reset
  - GPIO12: Touch Interrupt

**Status**: ⚠️ CHANGES REQUIRED
- Different touch controller (CST9217 vs CST816)
- Different I2C pins
- **ESPHome Support**: Need to verify if CST9217 is supported by ESPHome

---

## I2S Audio Specifications

### SMARTRING Audio
- **Pin Configuration**:
  - GPIO16: I2S_DAC_LRCK/WS
  - GPIO17: I2S_DAC_DIN
  - GPIO18: I2S_DAC_BCK
  - **Note**: No MCLK pin listed
  - **Note**: No speaker enable pin listed

### Ball V2 Audio
- **Pin Configuration**:
  - GPIO45: I2S_LRCLK (Word Select)
  - GPIO9: I2S_BCLK (Bit Clock)
  - GPIO16: I2S_MCLK (Master Clock)
  - GPIO10: I2S_DIN (Microphone)
  - GPIO8: I2S_DOUT (Speaker)
  - GPIO46: Speaker Enable

**Status**: ⚠️ CHANGES REQUIRED
- Different I2S pin mappings
- No MCLK pin on SMARTRING (may not be required)
- No speaker enable pin (may be always enabled or not present)
- Need to verify if microphone input exists

---

## LED Specifications

### SMARTRING LED
- **Pin**: GPIO39 (RGB_DIN)
- **Type**: Likely WS2812 RGB LED

### Ball V2 LED
- **Pin**: GPIO48 (LED_PIN)
- **Type**: WS2812 RGB LED

**Status**: ✅ Minor change - Different GPIO pin (39 vs 48)

---

## Button Specifications

### SMARTRING Button
- **Pin**: GPIO0 (BOOT)
- **Function**: Boot/User button

### Ball V2 Button
- **Pin**: GPIO0 (Main Button)
- **Function**: Boot/User button

**Status**: ✅ Compatible - Same pin

---

## Additional Hardware

### SMARTRING Specific
- **GPIO21**: IMU_INT1 (Inertial Measurement Unit)
- **GPIO38**: IMU_INT2
- **GPIO1-6**: SDMMC interface (SD Card support)
- **GPIO43/44**: UART0 (RX/TX)
- **GPIO15**: XSMT (Unknown function)

### Ball V2 Specific
- **GPIO1**: Battery ADC (Analog voltage monitoring)
- **I2C Bus B**: GPIO11 (SDA), GPIO7 (SCL) - Secondary I2C

**Status**: ⚠️ DIFFERENCES NOTED
- SMARTRING has IMU (accelerometer/gyroscope)
- SMARTRING has SD card interface
- Ball V2 has battery monitoring
- Need to determine if SMARTRING has battery monitoring capability

---

## Critical Compatibility Issues

### 🔴 BLOCKER: Display Driver
**Issue**: SMARTRING uses QSPI with CO5300 driver, which is likely NOT supported by ESPHome.
- ESPHome typically supports SPI displays with common drivers (ILI9xxx, ST7xxx, GC9A01A)
- QSPI display support in ESPHome is limited or non-existent
- CO5300 driver is not in standard ESPHome display drivers

**Required Action**: 
- Investigate if ESPHome has QSPI display support
- Check if CO5300 driver exists or can be added
- May require custom component development or Arduino framework instead

### 🟡 WARNING: Touch Controller
**Issue**: CST9217 touch controller support in ESPHome needs verification
- Ball V2 uses CST816 which is supported
- CST9217 may require custom component

**Required Action**:
- Check ESPHome documentation for CST9217 support
- May need custom touch component

### 🟢 MANAGEABLE: Pin Remapping
All other pin differences are manageable through configuration changes.

---

## Pin Mapping Summary Table

| Function | Ball V2 Pin | SMARTRING Pin | Status |
|----------|-------------|---------------|--------|
| **Display** | | | |
| LCD CS | GPIO5 | GPIO7 (QSPI) | ⚠️ Different protocol |
| LCD CLK | GPIO4 | GPIO13 (QSPI) | ⚠️ Different protocol |
| LCD MOSI | GPIO2 | GPIO12 (QSPI_D0) | ⚠️ Different protocol |
| LCD DC | GPIO47 | N/A (QSPI) | ⚠️ Different protocol |
| LCD D1 | N/A | GPIO8 (QSPI) | ⚠️ Different protocol |
| LCD D2 | N/A | GPIO14 (QSPI) | ⚠️ Different protocol |
| LCD D3 | N/A | GPIO9 (QSPI) | ⚠️ Different protocol |
| LCD RST | GPIO38 | GPIO11 | ✅ Remappable |
| LCD TE | N/A | GPIO10 | ℹ️ Additional |
| Backlight | GPIO42 | GPIO40 | ✅ Remappable |
| **Touch** | | | |
| Touch SDA | GPIO15 | GPIO41 | ✅ Remappable |
| Touch SCL | GPIO14 | GPIO45 | ✅ Remappable |
| Touch RST | GPIO6 | GPIO46 | ✅ Remappable |
| Touch INT | GPIO12 | GPIO42 | ✅ Remappable |
| **Audio** | | | |
| I2S LRCLK | GPIO45 | GPIO16 | ✅ Remappable |
| I2S BCLK | GPIO9 | GPIO18 | ✅ Remappable |
| I2S MCLK | GPIO16 | N/A? | ⚠️ May not exist |
| I2S DIN (Mic) | GPIO10 | GPIO17? | ⚠️ Unclear |
| I2S DOUT (Spk) | GPIO8 | GPIO17? | ⚠️ Unclear |
| Speaker EN | GPIO46 | N/A? | ⚠️ May not exist |
| **Other** | | | |
| LED | GPIO48 | GPIO39 | ✅ Remappable |
| Button | GPIO0 | GPIO0 | ✅ Same |
| Battery ADC | GPIO1 | Unknown | ⚠️ Unknown |
| I2C Bus B SDA | GPIO11 | N/A | ℹ️ Not used |
| I2C Bus B SCL | GPIO7 | N/A | ℹ️ Not used |

---

## Recommendations

### Immediate Actions Required:
1. ✅ Research ESPHome QSPI display support
2. ✅ Verify CO5300 driver availability
3. ✅ Check CST9217 touch controller support
4. ✅ Determine SMARTRING audio capabilities (mic/speaker)
5. ✅ Identify battery monitoring pin (if exists)

### If ESPHome Cannot Support QSPI/CO5300:
- Consider using Arduino framework with ESP32_Display_Panel library
- Create ESP-IDF based solution instead of ESPHome
- Wait for ESPHome to add support for these components

### If Proceeding with ESPHome:
- Create custom components for unsupported hardware
- Document all limitations clearly
- Test thoroughly with available hardware

---

## Validation Checklist

Before deployment, verify:
- [ ] Display initializes correctly (CRITICAL - likely won't work)
- [ ] Touch responds to input
- [ ] Audio output works
- [ ] Microphone input works (if applicable)
- [ ] LED functions correctly
- [ ] Button press detection works
- [ ] WiFi connectivity stable
- [ ] Voice assistant functionality
- [ ] Battery monitoring (if available)
- [ ] All LVGL pages render correctly
- [ ] No GPIO conflicts
- [ ] Proper power management

---

**IMPORTANT NOTE**: The display hardware difference (QSPI vs SPI, CO5300 vs GC9A01A) is a CRITICAL blocker. ESPHome likely does NOT support this hardware configuration. This adaptation may not be feasible without significant custom component development or switching to a different framework (Arduino/ESP-IDF).
