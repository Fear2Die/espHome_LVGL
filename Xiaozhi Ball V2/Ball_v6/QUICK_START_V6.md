# Ball V6 Quick Start Guide

## 🚀 What's New in V6?

Ball V6 introduces **gesture-based swipe navigation** - no more navigation buttons cluttering your display!

### Key Changes from V5.4:
- ✅ **Swipe Left**: Navigate forward (Main → Media → Weather → Main)
- ✅ **Swipe Right**: Navigate backward (Main → Weather → Media → Main)
- ✅ **No Navigation Buttons**: Clean, modern interface
- ✅ **Smooth Animations**: Professional slide transitions
- ✅ **Modern Styling**: iOS-style switches, rounded corners, shadows
- ✅ **Circular Navigation**: Seamlessly loop through all screens

## 📋 Prerequisites

- Xiaozhi Ball V2 hardware
- ESPHome 2024.5.0 or newer
- Home Assistant with:
  - A light entity (for light control)
  - A media player entity (for music control)
  - A weather entity (for weather display)

## 🔧 Installation Steps

### 1. Configure Your Entities

Edit `Ball_v6.yaml` and update the entity IDs at the top:

```yaml
substitutions:
  # Your Home Assistant entities
  light_entity: "light.YOUR_LIGHT_ENTITY"
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
```

**Example:**
```yaml
substitutions:
  light_entity: "light.living_room_lamp"
  media_player_entity: "media_player.spotify_living_room"
  weather_entity: "weather.home"
```

### 2. Create secrets.yaml

Create a file named `secrets.yaml` in the same directory:

```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
```

### 3. Flash to Device

Using ESPHome Dashboard or CLI:

```bash
esphome run Ball_v6.yaml
```

Or compile and upload via USB:
```bash
esphome compile Ball_v6.yaml
esphome upload Ball_v6.yaml
```

## 📱 Using Ball V6

### Navigation

**Swipe Gestures:**
- **Swipe Left** (←): Move to next screen
- **Swipe Right** (→): Move to previous screen

**Screen Flow:**
```
Main Screen → Media Screen → Weather Screen → Main Screen
     ↑                                            ↓
     └──────────────────────────────────────────┘
```

### Screen Features

#### 🏠 Main Screen (Light Control)
- **Title**: "Light Control"
- **Time**: Top left
- **Battery**: Top right (long-press screen to toggle)
- **Brightness Slider**: Adjust light brightness (0-100%)
- **Light Switch**: iOS-style toggle (green when on)

**How to Use:**
- Slide the brightness slider to adjust brightness
- Tap the switch to toggle light on/off
- Swipe left to go to Media screen

#### 🎵 Media Screen (Music Player)
- **Album Art**: Displays current track's artwork
- **Progress Arc**: Shows playback progress
- **Song Title**: Scrolls if too long
- **Artist Name**: Below title
- **Control Buttons**: Previous, Play/Pause, Next

**How to Use:**
- Tap **<<** to go to previous track
- Tap **>** or **||** to play/pause
- Tap **>>** to go to next track
- Swipe left to go to Weather screen
- Swipe right to go back to Main screen

#### 🌤️ Weather Screen (Weather Display)
- **Weather Condition**: Shows current conditions
- **Large Temperature**: Prominent display in center
- **Humidity Card**: Modern card design at bottom

**Display Only:** No interactive elements
- Swipe left to return to Main screen
- Swipe right to go to Media screen

### Long Press Actions

- **Long press anywhere**: Toggle battery percentage display

### Voice Assistant

The physical button on top of the device activates voice assistant:
- **Single press**: Activate/stop voice assistant
- **10-second press**: Factory reset

## 🎨 Customization

### Change Swipe Sensitivity

Edit the swipe threshold in `Ball_v6.yaml`:

```yaml
# Line ~408 in touchscreen on_release
if (abs(delta_x) > 60 && abs(delta_x) > abs(delta_y) * 2) {
  # Change 60 to a smaller number for more sensitive swipes
  # Change to a larger number for less sensitive swipes
}
```

### Modify Colors

Search for hex color codes in the LVGL section:

```yaml
# Example: Change background color
bg_color: 0x000000  # Black (change to 0x1A1A1A for dark gray)

# Change accent colors
text_color: 0xFFFFFF  # White
border_color: 0x666666  # Gray
```

### Adjust Animation Speed

Currently animations are handled by ESPHome's LVGL page transitions. The speed is controlled by ESPHome's default timing.

## 🔧 Troubleshooting

### Swipes Not Working
1. Check that you're in idle mode (not in voice assistant mode)
2. Ensure swipe is horizontal (not vertical)
3. Try swiping faster or longer distance
4. Check `current_screen_index` global in logs

### Display Not Updating
1. Check Home Assistant connection
2. Verify entity IDs are correct
3. Check ESPHome logs for errors
4. Restart device

### Album Art Not Showing
1. Ensure media player supports `entity_picture` attribute
2. Check Home Assistant URL is reachable
3. Verify `http_request` component is working
4. Album art updates when track changes

### Weather Not Showing
1. Verify weather entity exists in Home Assistant
2. Check entity has `temperature` and `humidity` attributes
3. Ensure weather integration is working

## 📊 Comparison: V5.4 vs V6

| Feature | V5.4 | V6 |
|---------|------|-----|
| Navigation | Buttons | Swipes |
| Screens | 3 + Camera | 3 (Main/Media/Weather) |
| Back Buttons | Yes | No |
| Nav Buttons | Yes (at bottom) | No |
| UI Style | Standard | Modern iOS-style |
| Animations | Page transitions | Smooth slide animations |
| Toggle Switch | Button style | iOS switch style |
| Slider | Basic | Modern with shadows |
| Album Art Size | 60x60 | 100x100 |
| Progress | None | Circular arc |
| Circular Nav | No | Yes (loops) |

## 🎯 Tips for Best Experience

1. **Swipe from center**: Start your swipe from the middle of the screen
2. **Horizontal swipes**: Keep your swipe mostly horizontal
3. **Quick swipes**: Fast swipes work best
4. **Natural flow**: Main → Media → Weather follows natural usage pattern
5. **Battery display**: Long-press to see battery when needed

## 📝 Known Limitations

1. Swipe gestures only work when in idle mode (not during voice assistant)
2. Animation direction is determined by swipe direction
3. Screen index resets to 0 (Main) on device restart
4. Album art may take a moment to load on first play

## 🆘 Getting Help

If you encounter issues:

1. Check ESPHome logs:
   ```bash
   esphome logs Ball_v6.yaml
   ```

2. Verify entities in Home Assistant Developer Tools → States

3. Check GitHub repository for updates and issues:
   https://github.com/Fear2Die/ESPHome-Projects

4. Compare with working Ball V5.4 configuration if migration issues

## 🎉 Enjoy Your Ball V6!

Experience the future of smart display navigation with intuitive swipe gestures!

---

**Version**: 6.0  
**Last Updated**: 2025-10-10  
**Status**: Ready for Production
