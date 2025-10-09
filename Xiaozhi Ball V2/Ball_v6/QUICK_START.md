# Ball V6 Quick Start Guide

Get up and running with Ball V6 in minutes!

---

## Prerequisites

- Xiaozhi Ball device (ESP32-S3 with circular display)
- Home Assistant instance
- ESPHome 2025.5.0 or later
- WiFi network

---

## 3-Minute Setup

### Step 1: Configure Entities (1 minute)

Edit `Ball_v6.yaml` at the top (around line 20):

```yaml
substitutions:
  # Replace with your actual entities
  light_entity: "light.living_room"
  media_player_entity: "media_player.spotify"
  weather_entity: "weather.home"
```

---

### Step 2: Set WiFi Credentials (1 minute)

Copy the example secrets file:

```bash
cp secrets.yaml.example secrets.yaml
```

Edit `secrets.yaml`:

```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
api_key: "your-32-character-api-key"
```

---

### Step 3: Flash Device

```bash
esphome run Ball_v6.yaml
```

Follow prompts to flash via USB or OTA.

---

## First Use

### 1. Test Basic Functions

- **Touch the arc** around center → Brightness changes
- **Tap Media button** (♫) → Opens media page
- **Tap Weather button** (☀) → Opens weather page
- **Tap "< Back"** → Returns to home

### 2. Try Swipe Gestures

- **Swipe left** from home → Goes to media page
- **Swipe left** from media → Goes to weather page
- **Swipe right** → Goes back one page

### 3. Change Theme

In Home Assistant:
1. Go to your Ball V6 device page
2. Click on **Configuration** tab
3. Find **Color Theme** selector
4. Select a theme: blue, purple, green, or orange
5. Watch colors change instantly!

### 4. Control Media

On media page:
- **Drag volume arc** at bottom → Adjust volume
- **Tap play/pause** button → Control playback
- **Tap << or >>** → Skip tracks

---

## Troubleshooting

### Theme selector not appearing

**Problem**: Can't find the Color Theme selector

**Solution**: 
1. Check that device is online in Home Assistant
2. Go to device page → Configuration tab
3. The "Color Theme" dropdown should be visible there
4. If not visible, restart the device

### Swipe not working

**Problem**: Swipes don't change pages

**Solution**:
1. Swipe distance must be >50 pixels
2. Must be horizontal (not diagonal)
3. Try faster swipes
4. Check touch screen is responsive

### Arc controls not responding

**Problem**: Can't adjust brightness/volume with arcs

**Solution**:
1. Check ESPHome version (need 2025.5.0+)
2. Verify LVGL supports arc widgets
3. Try tapping center of arc first
4. Use backup slider controls if needed

### Colors look wrong

**Problem**: Theme colors don't match

**Solution**:
1. Select "dark" theme first
2. Try other themes one by one
3. Check display brightness setting
4. Verify accent colors in YAML

---

## Quick Tips

### 🎨 Best Themes for Different Situations

- **Dark**: Low light, nighttime use
- **Blue**: Daytime, office setting
- **Purple**: Evening, ambient lighting
- **Green**: Relaxation, nature-themed rooms
- **Orange**: Warm, cozy atmosphere

### 👆 Gesture Tips

- **Swipe fast** for better detection
- **Start swipe from center** of screen
- **Swipe horizontally** (not diagonally)
- **50+ pixel distance** required

### 🎵 Media Control Tips

- **Volume arc** at bottom easier to reach
- **Double-tap play** if single tap doesn't work
- **Album art** updates automatically
- **Swipe** is fastest way to get to media page

### 💡 Brightness Control Tips

- **Arc control** more intuitive than slider
- **Drag clockwise** to increase
- **Drag counter-clockwise** to decrease
- **Center label** shows current value

---

## Advanced Setup

### Custom Theme Colors

Edit `Ball_v6.yaml` around line 1001 to add custom theme:

```yaml
select:
  - platform: template
    name: Color Theme
    id: color_theme_select
    options:
      - dark
      - blue
      - purple
      - green
      - orange
      - custom  # Add your custom theme
    on_value:
      # Add after the existing themes
      - if:
          condition:
            lambda: 'return x == "custom";'
          then:
            - lvgl.widget.update:
                id: idle_container
                bg_color: 0xYOUR_BG
            - lvgl.widget.update:
                id: brightness_arc
                arc_color: 0xYOUR_ACCENT
            - lvgl.widget.update:
                id: media_volume_arc
                arc_color: 0xYOUR_ACCENT
```

### Multiple Lights

Uncomment in `Ball_v6.yaml`:

```yaml
substitutions:
  light_entity_2: "light.bedroom"
  light_entity_3: "light.kitchen"
```

Add UI controls in LVGL section.

### Adjust Swipe Sensitivity

Edit touchscreen section (around line 340):

```yaml
if (abs(dx) > 50 && abs(dx) > abs(dy) * 1.5) {
  // Change 50 to 30 for easier swipes
  // Change 1.5 to 1.2 for more lenient angle
}
```

---

## Common Entity Examples

### Lights

```yaml
light_entity: "light.living_room"
light_entity: "light.bedroom_lamp"
light_entity: "light.office_ceiling"
```

### Media Players

```yaml
media_player_entity: "media_player.spotify"
media_player_entity: "media_player.living_room_tv"
media_player_entity: "media_player.bedroom_speaker"
```

### Weather

```yaml
weather_entity: "weather.home"
weather_entity: "weather.forecast_home"
weather_entity: "weather.openweathermap"
```

---

## Next Steps

### Explore Features

- Try all 5 color themes
- Practice swipe gestures
- Test arc controls
- Set up voice assistant
- Configure timer/alarm

### Customize

- Adjust arc sizes
- Change button positions
- Add more themes
- Modify colors
- Tweak swipe sensitivity

### Learn More

- Read [README.md](README.md) for full documentation
- Check [LAYOUT.md](LAYOUT.md) for screen layout details
- See [CHANGES.md](CHANGES.md) for what's new from V5.4

---

## Quick Reference Card

### Navigation

| Action | Result |
|--------|--------|
| Swipe Left | Next page |
| Swipe Right | Previous page |
| Tap Media (♫) | Media page |
| Tap Weather (☀) | Weather page |
| Tap < Back | Home page |

### Controls

| Control | Location | Action |
|---------|----------|--------|
| Brightness Arc | Home center | Drag to adjust |
| Toggle Button | Home top | Light on/off |
| Volume Arc | Media bottom | Drag to adjust |
| Play Button | Media center | Play/pause |
| Prev/Next | Media center | Skip tracks |

### Themes

| Theme | Color | Mood |
|-------|-------|------|
| Dark | Yellow | Default |
| Blue | Cyan | Cool |
| Purple | Violet | Royal |
| Green | Green | Calm |
| Orange | Orange | Warm |

---

## Get Help

### Issues?

- Check [Troubleshooting](#troubleshooting) section
- Review [README.md](README.md) for details
- Check ESPHome logs for errors
- Verify Home Assistant connection

### Feature Requests?

Ball V6 implements priority features from SUGGESTED_IMPROVEMENTS.md. See that file for future possibilities!

---

**You're all set! Enjoy Ball V6! 🎉**
