# ESPHome Xiaozhi Ball V6 - Advanced Features & Enhanced Circular UX

## 🎯 What's New in V6?

### Major Features

Ball V6 brings cutting-edge features designed specifically for circular displays:

#### 🎨 **Color Theme Support**
- **Multiple color themes** controllable from Home Assistant
- Themes: Dark (default), Blue, Purple, Green, Orange
- Dynamic color updates for all UI elements
- Create an `input_select` in Home Assistant to control themes

#### 👆 **Swipe Gesture Navigation**
- **Natural touch interaction** - swipe left/right to navigate between pages
- Horizontal swipes (>50px) trigger page transitions
- Swipe right: Go to previous page
- Swipe left: Go to next page
- Works seamlessly alongside button navigation

#### 🔵 **Radial Menu System**
- **Circular button layout** designed for circular displays
- Navigation buttons positioned around the center
- Media button at left (♫)
- Weather button at right (☀)
- More intuitive and visually appealing than linear layouts

#### 📊 **Circular Progress Indicators**
- **Arc-based controls** replace traditional linear sliders
- Brightness control: 270-degree arc around center
- Volume control: 90-degree arc at bottom of media page
- Real-time visual feedback
- More natural on circular displays

#### ⏰ **Enhanced Timer/Alarm Management**
- **Circular countdown display** when timer is active
- Visual arc shows remaining time
- Timer label displays time remaining
- Integrated seamlessly into main page

#### ✨ **Optimized Code**
- Removed unused code
- Improved performance
- Better memory management
- Maintained compatibility with existing features

---

## 🚀 Quick Setup

### 1. Configure Your Entities

At the top of `Ball_v6.yaml` (around line 20):

```yaml
## ENTITY CONFIGURATION
substitutions:
  # Light entity
  light_entity: "light.YOUR_LIGHT_ENTITY"
  
  # Media player entity
  media_player_entity: "media_player.YOUR_MEDIA_PLAYER_ENTITY"
  
  # Weather entity
  weather_entity: "weather.YOUR_WEATHER_ENTITY"
  
  # Color theme selector (NEW in V6)
  theme_selector_entity: "input_select.ball_color_theme"
```

### 2. Create Theme Selector in Home Assistant

Add this to your Home Assistant `configuration.yaml`:

```yaml
input_select:
  ball_color_theme:
    name: Ball Color Theme
    options:
      - dark
      - blue
      - purple
      - green
      - orange
    initial: dark
```

### 3. Copy secrets.yaml

```bash
cp secrets.yaml.example secrets.yaml
```

Edit with your credentials:

```yaml
wifi_ssid: "YourWiFiName"
wifi_password: "YourWiFiPassword"
api_key: "your-esphome-api-key"
```

### 4. Flash to Device

```bash
esphome run Ball_v6.yaml
```

---

## 📋 New Features in Detail

### Swipe Gestures

**How to Use:**
- Touch and drag horizontally across the screen
- **Swipe left**: Move to next page (Idle → Media → Weather)
- **Swipe right**: Move to previous page (Weather → Media → Idle)
- Minimum swipe distance: 50 pixels
- Only horizontal swipes are detected (vertical ignored)

**Benefits:**
- Faster navigation than button taps
- More natural touch interaction
- Reduces screen clutter
- Works alongside traditional buttons

### Circular Progress Arcs

**Brightness Control:**
- Large arc around center of screen
- Drag around the arc to adjust brightness
- Shows 0-100% visually
- Updates in real-time

**Volume Control:**
- Arc at bottom of media page
- Smaller 90-degree arc
- Adjust by dragging
- Synchronized with Home Assistant

**Features:**
- Smooth animations
- Visual feedback
- Touch-adjustable
- Auto-updates from HA

### Color Themes

**Available Themes:**
- **Dark** (0x111111 bg, 0xFFCC66 accent) - Default
- **Blue** (0x0a1929 bg, 0x4fc3f7 accent) - Cool and modern
- **Purple** (0x1a0a29 bg, 0xce93d8 accent) - Royal and elegant
- **Green** (0x0a291a bg, 0x81c784 accent) - Natural and calm
- **Orange** (0x291a0a bg, 0xffb74d accent) - Warm and vibrant

**What Gets Themed:**
- Page backgrounds
- Arc colors (brightness & volume)
- Button colors when active
- Accent colors throughout UI

**Change Theme:**
1. In Home Assistant, go to Developer Tools → States
2. Find `input_select.ball_color_theme`
3. Select your desired theme
4. Changes apply immediately!

### Radial Menu

**Layout:**
- Circular buttons positioned around center
- Media button: Left side, blue accent
- Weather button: Right side, yellow accent
- 60x60 circular buttons with icons
- Optimized spacing for easy touch

**Visual Design:**
- Uses Unicode symbols (♫ for media, ☀ for weather)
- Color-coded borders
- Circular shape matches display
- Professional appearance

### Timer Display

**Features:**
- Circular arc shows countdown progress
- Arc color: Red (#FF6666)
- Timer label in center when active
- Auto-hides when no timer
- Visual and clear

---

## 🎨 Customization

### Changing Theme Colors

Edit the theme sensor in the YAML (around line 1228):

```yaml
if (x == "custom") {
  bg_color = 0xYOUR_BG_COLOR;
  accent_color = 0xYOUR_ACCENT_COLOR;
}
```

### Adjusting Arc Sizes

Edit arc widgets in LVGL section:

```yaml
- arc:
    id: brightness_arc
    width: 200  # Change size
    height: 200
    arc_width: 8  # Change thickness
```

### Modifying Swipe Sensitivity

Edit touchscreen section (around line 340):

```yaml
if (abs(dx) > 50 && abs(dx) > abs(dy) * 1.5) {
  // Change 50 to adjust minimum swipe distance
}
```

---

## 📱 Usage

### Navigation

**Button Method:**
- Tap Media or Weather buttons on main page
- Tap "< Back" to return to main page

**Swipe Method:**
- Swipe left to go to next page
- Swipe right to go to previous page
- Page order: Idle ↔ Media ↔ Weather

### Brightness Control

**Arc Method (NEW):**
1. Touch the circular arc around the center
2. Drag clockwise to increase brightness
3. Drag counter-clockwise to decrease
4. Percentage shown in center

**Button Method:**
- Tap "Toggle" button to turn light on/off

### Volume Control

**Arc Method (NEW):**
1. On media page, find arc at bottom
2. Drag left to decrease volume
3. Drag right to increase volume
4. Percentage shown below arc

### Changing Theme

1. Open Home Assistant
2. Go to "input_select.ball_color_theme"
3. Select theme: dark, blue, purple, green, or orange
4. Changes apply instantly!

---

## 🔧 Technical Details

### Hardware Requirements

Same as Ball V5.4:
- ESP32-S3 based device (Xiaozhi Ball)
- 240x240 circular display (GC9A01A)
- Touch screen (CST816) with swipe support
- Microphone and speaker
- Physical button
- RGB LED
- Battery powered

### Software Requirements

- ESPHome 2025.5.0 or later
- Home Assistant with API
- WiFi connection

### New Globals

```yaml
globals:
  - id: current_theme  # Stores selected theme
  - id: swipe_start_x  # Touch start X coordinate
  - id: swipe_start_y  # Touch start Y coordinate
  - id: current_page_index  # Tracks current page (0=idle, 1=media, 2=weather)
```

### Performance

- Optimized arc rendering
- Minimal memory usage
- Smooth 60 FPS target
- Responsive touch input (<100ms)

---

## 🐛 Troubleshooting

### Swipe Not Working

1. Check touchscreen is responding to touch
2. Try larger swipe distance (>75px)
3. Ensure horizontal swipe (not diagonal)
4. Check touch sensor in logs

### Theme Not Changing

1. Verify `input_select.ball_color_theme` exists in HA
2. Check entity name matches in YAML
3. Restart ESPHome device
4. Check HA connection

### Arc Controls Not Responding

1. Ensure LVGL version supports arc widgets
2. Check touch calibration
3. Try tapping center of arc first
4. Verify HA entity is available

### Colors Look Wrong

1. Check theme name matches exactly
2. Try different theme
3. Verify accent colors are visible
4. Check display brightness

---

## 📈 Comparison to V5.4

### What's New
- ✅ Swipe gesture navigation
- ✅ Circular progress arcs
- ✅ Color theme system
- ✅ Radial menu layout
- ✅ Enhanced timer display
- ✅ Optimized code

### What's Preserved
- ✅ All V5.4 features
- ✅ Voice assistant
- ✅ Media player controls
- ✅ Weather display
- ✅ Battery monitoring
- ✅ Button navigation (as backup)

### Breaking Changes
- None! V6 is fully backward compatible
- Button navigation still works
- Can ignore swipe gestures if preferred
- Theme selector is optional (defaults to dark)

---

## 🎯 Future Ideas

Potential enhancements for V6.1+:
- Rotation gestures for circular controls
- Multi-touch support
- Custom theme editor in HA
- More animation effects
- Gesture shortcuts
- Voice-activated theme changes

---

## 📝 Credits

**Ball V6** by ESPHome Community
- Based on Ball V5.4 by Fear2Die
- Implements suggestions from SUGGESTED_IMPROVEMENTS.md
- Features designed for circular displays

---

## 📄 License

MIT License - Free to use and modify

---

## 🤝 Contributing

Found a bug? Have an idea?
- Open an issue on GitHub
- Submit a pull request
- Share your theme colors!

---

## 📚 Documentation

- [LAYOUT.md](LAYOUT.md) - Screen layout details
- [CHANGES.md](CHANGES.md) - Changelog from V5.4
- [secrets.yaml.example](secrets.yaml.example) - Configuration template

**Enjoy your enhanced Ball V6 experience! 🎉**
