# SMARTRING V1 - Quick Reference Guide

## ⚠️ Status: INCOMPLETE - Hardware Not Fully Supported

This is a quick reference for the SMARTRING V1 configuration. For complete details, see README.md and HARDWARE_COMPARISON.md.

---

## Critical Limitations

| Component | Status | Impact |
|-----------|--------|--------|
| Display (QSPI) | 🔴 NOT SUPPORTED | No visual output |
| Touch (CST9217) | 🟡 UNCERTAIN | Touch may not work |
| Audio | 🟡 UNCERTAIN | Voice assistant may not work |
| WiFi/API | 🟢 SUPPORTED | Should work |
| LED/Button | 🟢 SUPPORTED | Should work |

---

## Pin Quick Reference

### Display (QSPI - Not Working)
```
CS:  GPIO7    SCK: GPIO13   RST: GPIO11
D0:  GPIO12   D1:  GPIO8    TE:  GPIO10
D2:  GPIO14   D3:  GPIO9    BL:  GPIO40
```

### Touch (I2C)
```
SDA: GPIO41   SCL: GPIO45
RST: GPIO46   INT: GPIO42
```

### Audio (I2S)
```
LRCLK: GPIO16   BCLK: GPIO18
DIN:   GPIO17   (MCLK: N/A)
```

### Other
```
LED: GPIO39   Button: GPIO0
```

---

## File Structure

```
SMARTRING_V1/
├── SMARTRING_V1.yaml         # Main config (won't work fully)
├── README.md                 # Full documentation
├── HARDWARE_COMPARISON.md    # Detailed hardware analysis
├── VALIDATION_CHECKLIST.md   # Testing procedures
├── QUICK_REFERENCE.md        # This file
├── secrets.yaml.example      # WiFi template
└── .gitignore               # Git exclusions
```

---

## Quick Start (For Testing Only)

### 1. Copy secrets file
```bash
cd SMARTRING_V1
cp secrets.yaml.example secrets.yaml
nano secrets.yaml  # Edit with your WiFi credentials
```

### 2. Edit entities in SMARTRING_V1.yaml
```yaml
light_entity: "light.your_light"
media_player_entity: "media_player.your_speaker"  
weather_entity: "weather.your_location"
```

### 3. Try to validate
```bash
esphome config SMARTRING_V1.yaml
```

### 4. Try to compile (will likely fail)
```bash
esphome compile SMARTRING_V1.yaml
```

### 5. Monitor logs (if it somehow worked)
```bash
esphome logs SMARTRING_V1.yaml
```

---

## Expected Test Results

### Will Work ✅
- WiFi connection
- Home Assistant API
- LED control (GPIO39)
- Button detection (GPIO0)

### Uncertain 🟡
- Touch input (CST9217 vs CST816 driver)
- Audio output (different pins, unknown hardware)
- Microphone input (pin uncertain, may not exist)

### Won't Work 🔴
- Display output (QSPI not supported by ESPHome)
- LVGL interface (no display)
- Visual feedback (no display)
- Full voice assistant (needs display + working audio)

---

## Hardware vs Ball V2

| Feature | Ball V2 | SMARTRING | Compatible? |
|---------|---------|-----------|-------------|
| Display | 240x240 SPI GC9A01A | 466x466 QSPI CO5300 | ❌ No |
| Touch | CST816 I2C | CST9217 I2C | ⚠️ Maybe |
| Audio | I2S + ES8311 | I2S + ?? | ⚠️ Maybe |
| LED | GPIO48 | GPIO39 | ✅ Yes |
| Button | GPIO0 | GPIO0 | ✅ Yes |
| Battery | GPIO1 ADC | Unknown | ❌ No |
| MCU | ESP32-S3 8MB PSRAM | ESP32-S3-R8 8MB PSRAM | ✅ Yes |

---

## Common Errors

### "Display initialization failed"
**Cause**: QSPI not supported by ESPHome  
**Fix**: No fix available in ESPHome - need custom component or different framework  
**Expected**: This error is normal and expected

### "Touch controller not found"
**Cause**: CST9217 may not be compatible with CST816 driver  
**Fix**: Test with actual hardware, may need custom component  
**Workaround**: None available

### "No audio output"
**Cause**: Pin configuration may be incorrect  
**Fix**: Hardware testing to verify pins  
**Workaround**: Try different pin assignments

### "Configuration validation failed"
**Cause**: YAML syntax error or missing component  
**Fix**: Check YAML indentation and component definitions  
**Common Issues**: Missing spaces, wrong pin numbers

---

## Alternatives to ESPHome

### Arduino Framework (Recommended)
**Pros**:
- ✅ Complete SMARTRING support
- ✅ Working examples in repository
- ✅ ESP32_Display_Panel library
- ✅ LVGL integration

**Cons**:
- ❌ No Home Assistant ESPHome integration
- ❌ Different programming model
- ❌ Manual HA integration needed

**Files**: `VIEWE-SMARTRING-og/examples/arduino/`

### ESP-IDF Framework
**Pros**:
- ✅ Complete hardware support
- ✅ Working examples
- ✅ Maximum control

**Cons**:
- ❌ More complex
- ❌ Steeper learning curve
- ❌ No ESPHome features

**Files**: `VIEWE-SMARTRING-og/examples/esp-idf/`

---

## Key Decisions

### If Display Works (Unlikely):
- Continue with ESPHome
- Document success
- Share custom components if developed

### If Display Fails (Expected):
**Option A**: Develop custom QSPI component for ESPHome  
**Option B**: Switch to Arduino (fastest path to working device)  
**Option C**: Use ESP-IDF examples  
**Option D**: Wait for ESPHome to add QSPI support  

**Recommended**: Option B (Arduino)

---

## Entity Configuration

### Minimal Required
```yaml
substitutions:
  light_entity: "light.your_light"
  media_player_entity: "media_player.your_speaker"
  weather_entity: "weather.your_location"
```

### Optional Multiple Lights
```yaml
  light_entity_2: "light.bedroom"
  light_entity_3: "light.kitchen"
```

---

## Debugging Commands

### Check YAML syntax
```bash
esphome config SMARTRING_V1.yaml
```

### Compile firmware
```bash
esphome compile SMARTRING_V1.yaml
```

### Upload to device
```bash
esphome upload SMARTRING_V1.yaml
```

### View logs
```bash
esphome logs SMARTRING_V1.yaml
```

### Clean build files
```bash
esphome clean SMARTRING_V1.yaml
```

---

## Important Files

### Must Edit
- `secrets.yaml` - WiFi credentials
- `SMARTRING_V1.yaml` (top) - Entity IDs

### Documentation
- `README.md` - Full documentation
- `HARDWARE_COMPARISON.md` - Hardware analysis
- `VALIDATION_CHECKLIST.md` - Testing guide

### Reference
- `VIEWE-SMARTRING-og/README.md` - Hardware docs
- `VIEWE-SMARTRING-og/examples/` - Working code
- `Ball_v5.3/` - Original software base

---

## Home Assistant Setup

### Required Settings
1. Go to Settings → Devices & Services → ESPHome
2. Find SMARTRING V1 device
3. Click Configure
4. Enable: "Allow device to perform Home Assistant actions"
5. Click Submit

**Note**: Even with proper setup, display limitations prevent full functionality

---

## Testing Priority

1. **WiFi/API** (should work)
2. **LED** (should work)
3. **Button** (should work)
4. **Touch** (uncertain - test carefully)
5. **Audio** (uncertain - test carefully)
6. **Display** (will fail - document errors)

---

## Support Resources

### Documentation
- This folder's README.md
- HARDWARE_COMPARISON.md
- VALIDATION_CHECKLIST.md

### Hardware Docs
- VIEWE-SMARTRING-og/README.md
- VIEWE-SMARTRING-og/datasheet/
- VIEWE-SMARTRING-og/schematic/

### Working Examples
- VIEWE-SMARTRING-og/examples/arduino/
- VIEWE-SMARTRING-og/examples/esp-idf/

### Original Software
- Ball_v5.3/Ball_v5.3.yaml
- Ball_v5.3/README.md

---

## Version Info

**Configuration Version**: V1.0  
**Based On**: Ball V5.3  
**Hardware**: VIEWE SMARTRING (ESP32-S3-R8)  
**Status**: ⚠️ INCOMPLETE - Display not supported  
**Date**: 2025  

---

## Quick Decision Flowchart

```
Do you have SMARTRING hardware?
│
├─ No → Use Ball V5.3 with Ball V2 hardware
│
└─ Yes → Want to use ESPHome?
    │
    ├─ Yes → This config (expect display issues)
    │   │
    │   └─ Can you develop custom components?
    │       │
    │       ├─ Yes → Start with this, add QSPI support
    │       │
    │       └─ No → Try Arduino framework instead
    │
    └─ No → Use Arduino examples (recommended)
        └─ See VIEWE-SMARTRING-og/examples/
```

---

## Disclaimer

This configuration is **INCOMPLETE** due to ESPHome not supporting QSPI displays. It serves as:
- ✅ Pin mapping reference
- ✅ Framework structure
- ✅ Documentation of hardware
- ❌ NOT a working voice assistant solution

For a working SMARTRING device, use Arduino framework with provided examples.
