# Spotpear V2 - LVGL Configuration

This configuration has been updated to use LVGL instead of image-based displays.

## Features

- **LVGL Display System**: Clean, modern UI with colored pages for different states
- **Home Assistant Voice Assistant**: Full voice assistant integration with wake word detection
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

## Hardware

- ESP32-S3 Device (Spotpear V2)
- 240x240 GC9A01A Round Display
- ES8311 Audio DAC
- Microphone and Speaker
- Touch Screen (CST816)
- Battery powered with monitoring

## Configuration

1. Create a `secrets.yaml` file with your WiFi credentials:
   ```yaml
   wifi_ssid: "your_ssid"
   wifi_password: "your_password"
   ```

2. Flash the device:
   ```bash
   esphome run Spotpear_v2.yaml
   ```

## Voice Assistant Setup

The device supports:
- On-device wake word detection (Alexa, Hey Jarvis, Okay Nabu)
- Or Home Assistant-based wake word detection
- Configurable wake word engine location in Home Assistant

## Battery Status

Long-press the touch screen to toggle battery percentage display.

## Original Configuration

The original image-based configuration is backed up in `Spotpear_v2_original_backup.yaml`.
