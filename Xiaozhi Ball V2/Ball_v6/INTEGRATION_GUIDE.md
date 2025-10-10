# Ball V6 Integration Guide

## Overview

This guide explains how to integrate the Ball V6 UI (screens.c) into an ESPHome project for the Xiaozhi Ball hardware.

## Prerequisites

### Hardware Requirements
- Xiaozhi Ball V2 hardware
- ESP32-S3 with PSRAM
- GC9A01A circular display (240x240)
- CST816 touch controller
- Audio components (I2S speaker and microphone)

### Software Requirements
- ESPHome 2024.5.0 or newer
- LVGL 8.3.x support in ESPHome
- C compiler with C99 support

## File Structure

```
your-esphome-project/
├── ball_v6.yaml              # Main ESPHome configuration
├── screens.c                 # Ball V6 UI implementation
├── screens.h                 # Screen object declarations
├── ui.h                      # UI helper functions
├── vars.h                    # Variable definitions
├── actions.h                 # Action handlers
├── styles.h                  # LVGL style definitions
├── fonts.h                   # Font definitions
└── images.h                  # Image assets
```

## Step-by-Step Integration

### 1. Copy Required Files

Copy the following files to your ESPHome project directory:
```bash
cp Ball_v6/screens.c your-project/
# Also ensure you have the header files needed
```

### 2. Create Header Files

If you don't have the header files, create minimal versions:

#### `screens.h`
```c
#ifndef SCREENS_H
#define SCREENS_H

#include "lvgl.h"

typedef enum {
    SCREEN_MAIN = 1,
    SCREEN_MEDIA = 2,
    SCREEN_WEATHER = 3
} ScreensEnum;

typedef struct {
    lv_obj_t *main;
    lv_obj_t *media;
    lv_obj_t *weather;
    
    // Main screen widgets
    lv_obj_t *obj0;              // Light switch
    lv_obj_t *obj1;              // Brightness slider
    lv_obj_t *date;              // Date/time label
    lv_obj_t *battery;           // Battery label
    lv_obj_t *brightness_label;  // Brightness label
    lv_obj_t *light_status;      // Light status label
    
    // Media screen widgets
    lv_obj_t *back;              // Previous button
    lv_obj_t *forward;           // Next button
    lv_obj_t *pause;             // Play/pause button
    lv_obj_t *label_back;        // Previous label
    lv_obj_t *label_forward;     // Next label
    lv_obj_t *label_pause;       // Play label
    lv_obj_t *media_img;         // Album art
    lv_obj_t *media_arc;         // Progress arc
    lv_obj_t *media_title;       // Song title
    lv_obj_t *media_artist;      // Artist name
    
    // Weather screen widgets
    lv_obj_t *temp;              // Temperature
    lv_obj_t *humidity_insert;   // Humidity value
    lv_obj_t *humidity_label;    // Humidity label
    lv_obj_t *weather_title;     // Weather title
    lv_obj_t *weather_condition; // Weather condition
} objects_t;

extern objects_t objects;

void create_screens(void);
void create_screen_main(void);
void create_screen_media(void);
void create_screen_weather(void);
void tick_screen_main(void);
void tick_screen_media(void);
void tick_screen_weather(void);

#endif // SCREENS_H
```

#### `ui.h`
```c
#ifndef UI_H
#define UI_H

// Placeholder - add your UI helper functions here

#endif // UI_H
```

#### `vars.h`
```c
#ifndef VARS_H
#define VARS_H

// Add your global variables here

#endif // VARS_H
```

#### `actions.h`
```c
#ifndef ACTIONS_H
#define ACTIONS_H

// Add your action handlers here

#endif // ACTIONS_H
```

#### `styles.h`
```c
#ifndef STYLES_H
#define STYLES_H

// Add your custom styles here

#endif // STYLES_H
```

#### `fonts.h`
```c
#ifndef FONTS_H
#define FONTS_H

// Fonts are typically defined in LVGL
// This file can be empty or contain custom font declarations

#endif // FONTS_H
```

#### `images.h`
```c
#ifndef IMAGES_H
#define IMAGES_H

// Add your image declarations here

#endif // IMAGES_H
```

### 3. ESPHome Configuration

Create or update your `ball_v6.yaml`:

```yaml
substitutions:
  name: ball_v6
  friendly_name: "Ball V6"

esphome:
  name: ${name}
  friendly_name: ${friendly_name}
  platformio_options:
    build_flags:
      - -DBOARD_HAS_PSRAM
      - -DLVGL_MEM_POOL_SIZE=1024*1024
    
  includes:
    - screens.c
    - screens.h
    - ui.h
    - vars.h
    - actions.h
    - styles.h
    - fonts.h
    - images.h

esp32:
  board: esp32-s3-devkitc-1
  framework:
    type: esp-idf
  flash_size: 16MB

psram:
  mode: octal
  speed: 80MHz

# Display configuration
spi:
  clk_pin: GPIO4
  mosi_pin: GPIO2

display:
  - platform: ili9xxx
    model: GC9A01A
    cs_pin: GPIO5
    dc_pin: GPIO47
    reset_pin: GPIO38
    invert_colors: true
    dimensions:
      width: 240
      height: 240
    lambda: |-
      // LVGL display rendering happens automatically

# Touch configuration
touchscreen:
  - platform: cst816
    id: touch_screen
    i2c_id: bus_a
    interrupt_pin: GPIO12
    reset_pin: GPIO6
    on_touch:
      - lambda: |-
          // Touch handling is done by LVGL

# LVGL configuration
lvgl:
  log_level: WARN
  color_depth: 16
  bg_color: 0x000000
  text_color: 0xFFFFFF
  
  # Enable gesture detection
  touchscreens:
    - touchscreen_id: touch_screen
      gesture_support: true
  
  on_idle:
    timeout: 30s
    then:
      - logger.log: "Screen idle"
  
  # Initialize screens
  setup_priority: 100
  on_setup:
    - lambda: |-
        create_screens();

# WiFi and API
wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

api:
  encryption:
    key: !secret api_key

ota:
  - platform: esphome
```

### 4. Enable Required LVGL Features

Make sure your `lv_conf.h` or ESPHome LVGL configuration includes:

```c
// Enable required widgets
#define LV_USE_SWITCH 1
#define LV_USE_SLIDER 1
#define LV_USE_BTN 1
#define LV_USE_LABEL 1
#define LV_USE_IMG 1
#define LV_USE_ARC 1

// Enable animations
#define LV_USE_ANIMATION 1

// Enable gesture support
#define LV_USE_GESTURE 1

// Enable required fonts
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_22 1
#define LV_FONT_MONTSERRAT_48 1

// Gesture thresholds
#define LV_INDEV_DEF_GESTURE_LIMIT 50
#define LV_INDEV_DEF_GESTURE_MIN_VELOCITY 3
```

## Connecting to Home Assistant

### Add Entities

Update your ESPHome YAML to connect widgets to Home Assistant entities:

```yaml
# Light control
light:
  - platform: homeassistant
    id: controlled_light
    entity_id: light.living_room

# Media player
media_player:
  - platform: homeassistant
    id: media_player
    entity_id: media_player.spotify

# Weather
sensor:
  - platform: homeassistant
    id: weather_temp
    entity_id: sensor.temperature
  
  - platform: homeassistant
    id: weather_humidity
    entity_id: sensor.humidity

text_sensor:
  - platform: homeassistant
    id: weather_condition
    entity_id: weather.home
```

### Update Widget Values

Add lambdas to update the UI based on Home Assistant state:

```yaml
interval:
  - interval: 1s
    then:
      - lambda: |-
          // Update time
          auto time = id(sntp_time).now();
          lv_label_set_text_fmt(objects.date, "%02d:%02d", time.hour, time.minute);
          
          // Update battery
          lv_label_set_text_fmt(objects.battery, "%d%%", (int)id(battery_percent).state);
          
          // Update light state
          if (id(controlled_light).current_values.is_on()) {
            lv_obj_add_state(objects.obj0, LV_STATE_CHECKED);
            lv_slider_set_value(objects.obj1, 
              id(controlled_light).current_values.get_brightness() * 100, 
              LV_ANIM_OFF);
          } else {
            lv_obj_clear_state(objects.obj0, LV_STATE_CHECKED);
          }
          
          // Update media info
          if (id(media_player).state == media_player::MEDIA_PLAYER_STATE_PLAYING) {
            lv_label_set_text(objects.label_pause, "||");
          } else {
            lv_label_set_text(objects.label_pause, ">");
          }
          lv_label_set_text(objects.media_title, id(media_player).current_track.c_str());
          lv_label_set_text(objects.media_artist, id(media_player).current_artist.c_str());
          
          // Update weather
          lv_label_set_text_fmt(objects.temp, "%.0f°", id(weather_temp).state);
          lv_label_set_text_fmt(objects.humidity_insert, "%.0f%%", id(weather_humidity).state);
```

### Add Button Actions

Connect button presses to Home Assistant actions:

```yaml
# In your screens.c or add event callbacks
# Add this to the button creation:

// Light switch callback
lv_obj_add_event_cb(objects.obj0, [](lv_event_t *e) {
  if (lv_obj_has_state(objects.obj0, LV_STATE_CHECKED)) {
    id(controlled_light).turn_on().perform();
  } else {
    id(controlled_light).turn_off().perform();
  }
}, LV_EVENT_VALUE_CHANGED, NULL);

// Brightness slider callback
lv_obj_add_event_cb(objects.obj1, [](lv_event_t *e) {
  int brightness = lv_slider_get_value(objects.obj1);
  auto call = id(controlled_light).turn_on();
  call.set_brightness(brightness / 100.0f);
  call.perform();
}, LV_EVENT_VALUE_CHANGED, NULL);

// Media previous button
lv_obj_add_event_cb(objects.back, [](lv_event_t *e) {
  id(media_player).make_call().set_command(media_player::MEDIA_PLAYER_COMMAND_PREVIOUS_TRACK).perform();
}, LV_EVENT_CLICKED, NULL);

// Media play/pause button
lv_obj_add_event_cb(objects.pause, [](lv_event_t *e) {
  if (id(media_player).state == media_player::MEDIA_PLAYER_STATE_PLAYING) {
    id(media_player).make_call().set_command(media_player::MEDIA_PLAYER_COMMAND_PAUSE).perform();
  } else {
    id(media_player).make_call().set_command(media_player::MEDIA_PLAYER_COMMAND_PLAY).perform();
  }
}, LV_EVENT_CLICKED, NULL);

// Media next button
lv_obj_add_event_cb(objects.forward, [](lv_event_t *e) {
  id(media_player).make_call().set_command(media_player::MEDIA_PLAYER_COMMAND_NEXT_TRACK).perform();
}, LV_EVENT_CLICKED, NULL);
```

## Testing

### 1. Compile and Upload

```bash
esphome compile ball_v6.yaml
esphome upload ball_v6.yaml
```

### 2. Test Gestures

- Swipe left to navigate: Main → Media → Weather → Main
- Swipe right to navigate: Main → Weather → Media → Main
- Verify smooth 250ms animations

### 3. Test Widgets

#### Main Screen
- Toggle light switch on/off
- Drag brightness slider
- Verify light responds in Home Assistant

#### Media Screen
- Press previous/next to change tracks
- Press play/pause to control playback
- Verify media player responds

#### Weather Screen
- Verify temperature and humidity display
- Check for live updates from Home Assistant

## Troubleshooting

### Gestures Not Working
1. Check touchscreen is enabled in config
2. Verify `gesture_support: true` in LVGL config
3. Check CST816 wiring and I2C communication
4. Monitor logs for touch events

### Display Issues
1. Verify SPI pins are correct
2. Check display power and backlight
3. Ensure `invert_colors: true` for GC9A01A
4. Monitor LVGL memory usage

### Compilation Errors
1. Ensure all header files are present
2. Check for missing font definitions
3. Verify LVGL version compatibility
4. Check PlatformIO build flags

### Performance Issues
1. Increase PSRAM allocation
2. Reduce animation frequency
3. Optimize update intervals
4. Check CPU frequency (240MHz)

## Advanced Configuration

### Custom Animations

Modify animation speed in `navigate_to_screen()`:
```c
lv_scr_load_anim(target_screen, anim_type, 250, 0, false);
//                                          ^^^ Duration in ms
```

### Custom Colors

Edit color hex values throughout `screens.c`:
```c
lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), ...);
//                                          ^^^^^^^^^^
```

### Add New Screens

1. Create screen in `screens.c`:
```c
void create_screen_new() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.new_screen = obj;
    // ... add widgets
    lv_obj_add_event_cb(obj, screen_gesture_event_cb, LV_EVENT_GESTURE, NULL);
}
```

2. Update `SCREEN_COUNT` and navigation array
3. Add to `create_screens()` function

## Best Practices

1. **Memory Management**
   - Pre-create all screens
   - Don't create/destroy repeatedly
   - Monitor PSRAM usage

2. **Update Frequency**
   - Use intervals for periodic updates
   - Update on state change for user actions
   - Batch multiple updates together

3. **Error Handling**
   - Check entity states before use
   - Handle missing data gracefully
   - Provide fallback values

4. **Performance**
   - Minimize screen redraws
   - Use LVGL caching
   - Optimize lambda execution time

## Support and Resources

- **ESPHome**: https://esphome.io/
- **LVGL**: https://lvgl.io/
- **Project Repository**: https://github.com/Fear2Die/ESPHome-Projects
- **Ball V6 README**: See README.md in this directory
- **Layout Documentation**: See LAYOUT.md in this directory

## License

This integration guide is part of the ESPHome-Projects repository. Please refer to the main repository for licensing information.

---

**Guide Version**: 1.0
**Last Updated**: 2025-10-10
**For**: Ball V6
