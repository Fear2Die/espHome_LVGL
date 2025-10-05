# SMARTRING V1 Validation Checklist

## ⚠️ PRE-TESTING WARNING

This configuration has CRITICAL hardware incompatibilities with ESPHome. Most features will NOT work without custom development. Use this checklist to systematically test what does and doesn't work.

---

## Phase 1: Configuration Validation

### YAML Syntax Check
```bash
esphome config SMARTRING_V1.yaml
```

**Expected Results**:
- [ ] ✅ Configuration validates successfully
- [ ] ⚠️ Warnings about unknown display driver (expected)
- [ ] ⚠️ Warnings about pin configurations (expected)

**If Failed**:
- Check YAML indentation
- Verify all substitutions are defined
- Check for typos in component names

---

## Phase 2: Compilation Test

### Compile Firmware
```bash
esphome compile SMARTRING_V1.yaml
```

**Expected Results**:
- [ ] ⚠️ Compilation completes (unlikely due to display driver issues)
- [ ] 🔴 Compilation fails with display initialization errors (likely)
- [ ] 🔴 Errors about missing display driver support (likely)

**Common Errors**:
- `Display driver 'GC9A01A' does not support QSPI`
- `Unknown display model`
- `Pin configuration invalid for display type`

**If Compilation Fails**:
- Expected behavior - display driver not supported
- Document specific error messages
- Consider developing custom component
- Consider switching to Arduino framework

**If Compilation Succeeds** (unlikely):
- Proceed to Phase 3
- Be prepared for runtime errors

---

## Phase 3: Upload Test (Only if compilation succeeded)

### Flash Firmware
```bash
esphome upload SMARTRING_V1.yaml
```

**Expected Results**:
- [ ] ⚠️ Upload completes
- [ ] ⚠️ Device reboots
- [ ] 🔴 Display does not initialize (expected)

**Watch for**:
- Upload progress bar completes 100%
- Serial output shows reboot message
- Device LED activity

---

## Phase 4: Basic Connectivity Tests

### Test 1: Serial Output
```bash
esphome logs SMARTRING_V1.yaml --device /dev/ttyUSB0
```

**Check for**:
- [ ] Boot messages appear
- [ ] ESP32-S3 initialization
- [ ] PSRAM detection (should show 8MB)
- [ ] WiFi connection attempt

**Expected Boot Sequence**:
```
[I][app:029] Running through setup()...
[I][psram:020] PSRAM: 8MB available
[W][display:xxx] Display initialization failed
[I][wifi:xxx] Connecting to WiFi...
```

### Test 2: WiFi Connection
**Check for**:
- [ ] ✅ WiFi connects successfully
- [ ] ✅ IP address obtained
- [ ] ⚠️ Home Assistant discovery attempt

**Serial Output Should Show**:
```
[I][wifi:xxx] WiFi Connected
[I][wifi:xxx] IP: 192.168.x.x
```

**If WiFi Fails**:
- Verify secrets.yaml credentials
- Check WiFi signal strength
- Try static IP configuration
- Check router MAC filtering

### Test 3: Home Assistant API
**Check for**:
- [ ] ✅ API connection established
- [ ] ✅ Device appears in Home Assistant
- [ ] ⚠️ Entities available (even if not functional)

**Serial Output Should Show**:
```
[I][api:xxx] Client connected
[I][api:xxx] Home Assistant API connected
```

---

## Phase 5: Component-by-Component Testing

### 🟢 Component 1: LED (Should Work)
**Test Procedure**:
1. Find "LED Ring" entity in Home Assistant
2. Turn on LED
3. Change color to red, green, blue
4. Test effects (pulse)

**Validation**:
- [ ] ✅ LED turns on/off
- [ ] ✅ Color changes work
- [ ] ✅ Brightness control works
- [ ] ✅ Effects work (pulse)

**If Failed**:
- Check GPIO39 connection
- Verify LED is WS2812
- Check power supply to LED
- Review serial output for errors

---

### 🟢 Component 2: Button (Should Work)
**Test Procedure**:
1. Press button GPIO0
2. Check serial output
3. Short press (single click)
4. Long press (>2 seconds)

**Validation**:
- [ ] ✅ Button press detected in logs
- [ ] ✅ Single click triggers voice assistant
- [ ] ✅ Long press toggles mute

**Serial Output Should Show**:
```
[D][button:xxx] Single click detected
[D][button:xxx] Long press detected
```

**If Failed**:
- GPIO0 may need different pull configuration
- Check button hardware connection
- Try different timing values

---

### 🔴 Component 3: Display (Will Fail)
**Test Procedure**:
1. Power on device
2. Check for any display activity
3. Monitor serial output

**Expected Result**:
- [ ] 🔴 Display does NOT initialize (confirmed)
- [ ] 🔴 No image appears on screen
- [ ] 🔴 Backlight may or may not turn on

**Serial Output Will Show**:
```
[E][display:xxx] Display initialization failed
[E][display:xxx] QSPI not supported
[E][display:xxx] CO5300 driver not found
```

**This is EXPECTED** - ESPHome does not support QSPI displays

**Troubleshooting Steps** (won't fix issue):
- ❌ Changing pin configuration (won't help - protocol issue)
- ❌ Different display model selection (CO5300 not available)
- ✅ Document error messages for custom component development
- ✅ Test backlight separately if possible

---

### 🟡 Component 4: Touch Screen (Uncertain)
**Test Procedure**:
1. Check if touch controller is detected
2. Try touching screen
3. Monitor serial output

**Validation**:
- [ ] ⚠️ I2C scan detects device at address (check logs)
- [ ] ⚠️ Touch coordinates appear in logs
- [ ] 🔴 Touch events not detected (likely)

**Serial Output**:
```
[I][i2c:xxx] I2C scan found device at address 0xXX
[D][touch:xxx] Touch detected at x=XX y=YY
```
OR
```
[W][i2c:xxx] No device found at expected address
[E][touch:xxx] CST9217 not compatible with CST816 driver
```

**If Touch Works**:
- Excellent! CST9217 is compatible with CST816 driver
- Document this finding
- Test touch accuracy

**If Touch Fails**:
- Check I2C pin connections (GPIO41, GPIO45)
- Verify touch reset pin (GPIO46)
- Check I2C scan results in logs
- May need custom touch driver

---

### 🟡 Component 5: Audio Output (Uncertain)
**Test Procedure**:
1. Try playing startup sound
2. Test media player
3. Listen for any audio

**Validation**:
- [ ] ⚠️ I2S initializes without errors
- [ ] ⚠️ Audio data sent to I2S
- [ ] 🔴 No sound output (uncertain)

**Serial Output Should Show**:
```
[I][i2s:xxx] I2S audio initialized
[I][speaker:xxx] Playing audio
```
OR
```
[E][i2s:xxx] I2S initialization failed
[E][speaker:xxx] Speaker not available
```

**If Audio Fails**:
- Verify I2S pin configuration
- Check if speaker exists and is connected
- Verify speaker enable pin (may not exist)
- Check if DAC chip is ES8311 or different

---

### 🟡 Component 6: Microphone (Uncertain)
**Test Procedure**:
1. Try activating voice assistant
2. Speak into device
3. Monitor serial output

**Validation**:
- [ ] ⚠️ Microphone initializes
- [ ] ⚠️ Audio input detected
- [ ] 🔴 Voice assistant doesn't respond (uncertain)

**Serial Output Should Show**:
```
[I][micro_wake_word:xxx] Wake word engine started
[I][voice_assistant:xxx] Listening...
```
OR
```
[E][microphone:xxx] No audio input detected
```

**If Microphone Fails**:
- Check if microphone exists on SMARTRING
- Verify I2S DIN pin (GPIO17 uncertain)
- May need different pin or be combined with speaker

---

## Phase 6: Integration Tests

### Test 1: Voice Assistant Flow
**Prerequisites**: WiFi, API, and Audio working

**Test Procedure**:
1. Ensure device is not muted
2. Say wake word ("Hey Jarvis" or "Okay Nabu")
3. Give voice command
4. Listen for response

**Validation**:
- [ ] Wake word detected
- [ ] Listening state activates (blue in logs)
- [ ] Command transcribed
- [ ] Response played
- [ ] Returns to idle state

**This will likely FAIL due to display, audio, or microphone issues**

---

### Test 2: Light Control
**Prerequisites**: WiFi and API working

**Test Procedure**:
1. View device in Home Assistant
2. Try brightness slider (on idle page - won't display)
3. Try toggle button
4. Use Home Assistant to change light
5. Check if slider updates (won't see it)

**Validation**:
- [ ] Commands sent to Home Assistant
- [ ] Light responds to commands
- [ ] State updates received (check logs)
- [ ] 🔴 Display doesn't show changes (expected)

---

### Test 3: Media Player
**Prerequisites**: WiFi and API working

**Test Procedure**:
1. Play media on configured media player
2. Check logs for state updates
3. Try media controls via Home Assistant

**Validation**:
- [ ] Media state updates received
- [ ] Album art URL retrieved
- [ ] 🔴 Nothing displayed (expected)

---

## Phase 7: Performance Monitoring

### Check 1: Memory Usage
**Monitor for**:
- [ ] Free heap memory (should be >100KB)
- [ ] PSRAM usage
- [ ] No memory leaks over time

**Serial Output**:
```
[D][app:xxx] Free heap: XXXXX bytes
```

### Check 2: CPU Usage
**Monitor for**:
- [ ] No excessive CPU usage
- [ ] Responsive to commands
- [ ] No watchdog resets

### Check 3: WiFi Stability
**Monitor for**:
- [ ] Stable WiFi connection over hours
- [ ] No frequent disconnections
- [ ] Good signal strength

---

## Summary Expectations

### 🟢 Will Likely Work:
- ✅ WiFi connectivity
- ✅ Home Assistant API
- ✅ LED control
- ✅ Button detection
- ✅ Configuration loading

### 🟡 May Work (Testing Required):
- ⚠️ Touch input (CST9217 compatibility)
- ⚠️ Audio output (pin configuration)
- ⚠️ Microphone input (hardware existence)

### 🔴 Will NOT Work:
- ❌ Display output (QSPI not supported)
- ❌ LVGL UI rendering (no display)
- ❌ Visual feedback (no display)
- ❌ Full voice assistant (needs display + audio)

---

## Decision Tree After Testing

### If Display Fails (Expected):

**Option A: Develop Custom Component**
- Learn ESPHome custom component development
- Implement QSPI bus support
- Implement CO5300 driver
- Contribute back to ESPHome

**Option B: Switch to Arduino**
- Use VIEWE-SMARTRING Arduino examples
- ESP32_Display_Panel library has full support
- LVGL integration available
- Working code exists

**Option C: Use ESP-IDF**
- Use VIEWE-SMARTRING ESP-IDF examples
- Complete hardware support
- LVGL integration available
- More low-level control

**Recommendation**: Option B (Arduino) for fastest working solution

---

## Reporting Results

### Create a Test Report

Document your findings:

```markdown
## SMARTRING V1 Test Results

**Date**: YYYY-MM-DD
**Firmware Version**: ESPHome 2025.X.X

### Components Tested

| Component | Status | Notes |
|-----------|--------|-------|
| WiFi | ✅/❌ | Details |
| LED | ✅/❌ | Details |
| Button | ✅/❌ | Details |
| Display | ❌ | QSPI not supported (expected) |
| Touch | ⚠️/❌ | Details |
| Audio Out | ⚠️/❌ | Details |
| Microphone | ⚠️/❌ | Details |

### Recommendations
Based on testing, recommend...
```

---

## Next Steps

Based on test results:

1. **Document all findings** in test report
2. **Update SMARTRING_V1.yaml** with any corrections
3. **Update README.md** with actual test results
4. **Decide on path forward**:
   - Custom component development
   - Arduino framework switch
   - ESP-IDF framework switch
   - Wait for ESPHome QSPI support

---

## Safety Notes

- ⚠️ Do not leave device unattended during testing
- ⚠️ Monitor for excessive heat
- ⚠️ Disconnect if any smoke or unusual smells
- ⚠️ Use appropriate power supply (USB-C)
- ⚠️ Do not short GPIO pins

---

**Remember**: This configuration is expected to have limited functionality due to hardware limitations. The goal of this testing is to document what works and what doesn't, not to achieve full functionality.
