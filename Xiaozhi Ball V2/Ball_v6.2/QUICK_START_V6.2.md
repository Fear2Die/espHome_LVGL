# Ball V6.2 Quick Start Guide

**⏱️ Time to deploy: 10 minutes**

---

## What's New? 🎉

Ball V6.2 fixes three media player issues:

1. ✅ **Volume Slider** - Moved higher (no more overlap)
2. ✅ **Progress Arc** - Updates every second (smooth animation!)
3. ✅ **Album Art** - Works with JPEG images (was PNG only)

---

## Installation (3 Steps)

### Step 1: Download
Download `Ball_v6.2.yaml` to your ESPHome folder

### Step 2: Configure
Edit three lines to set your Home Assistant entities:
```yaml
Line 20: light_entity: "light.YOUR_LIGHT_ENTITY"
Line 23: media_player_entity: "media_player.YOUR_MEDIA_PLAYER"
Line 26: weather_entity: "weather.YOUR_WEATHER"
```

### Step 3: Flash
```bash
esphome run Ball_v6.2.yaml
```

**Done!** ✨

---

## Testing (3 Things)

### 1. Volume Slider Position ✅
- Navigate to media screen
- Slider should be on left side
- Should not overlap with any UI elements

### 2. Progress Arc ✅
- Play a song
- Watch the green arc around album art
- **Should update every second** (not just when paused!)
- Pause → arc should freeze
- Resume → arc should continue

### 3. Album Art ✅
- Play music from Spotify/YouTube Music
- Album cover should appear within 5-10 seconds
- Should work with JPEG images now!

---

## Troubleshooting

### Problem: Progress arc not animating
**Check**: 
- Is media actually playing? (check Home Assistant)
- Does your media player provide `media_position`?

### Problem: No album art
**Check**:
- Does your media player have `entity_picture` attribute?
- Can ESP32 reach Home Assistant network?
- Try with different music source (Spotify, etc.)

### Problem: Slider in wrong position
**Fix**: Edit line 1509, change y value:
- Current: `-30`
- Lower on screen: `-25` or `-20`
- Higher on screen: `-35` or `-40`

---

## More Help?

📖 **Full Guide**: [README_V6.2.md](README_V6.2.md)  
🔧 **Technical**: [CHANGES_V6.2.md](CHANGES_V6.2.md)  
👁️ **Visual**: [VISUAL_CHANGES_V6.2.md](VISUAL_CHANGES_V6.2.md)  
📑 **Navigation**: [INDEX_V6.2.md](INDEX_V6.2.md)

---

## That's It! 🎵

Enjoy your improved media player with:
- Better positioned volume slider
- Smooth real-time progress arc
- Working album art for all your music!

**Questions?** Check the full [README_V6.2.md](README_V6.2.md)

---

**Version**: 6.2  
**Release**: 2025-10-10
