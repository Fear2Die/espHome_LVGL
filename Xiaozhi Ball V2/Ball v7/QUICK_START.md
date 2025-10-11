# Ball V7 - Quick Start Guide

## What You Need

- ✅ ESPHome-compatible device (Ball V2 hardware)
- ✅ Home Assistant instance
- ✅ Media player integrated with Home Assistant
- ✅ 5 minutes setup time

---

## Step 1: Add Home Assistant Template Sensors

Open your Home Assistant `configuration.yaml` and add:

```yaml
template:
  - sensor:
      - name: "Now Playing Title"
        state: >
          {{ state_attr('media_player.spotify', 'media_title') or 'No media' }}

      - name: "Now Playing Artist"
        state: >
          {{ state_attr('media_player.spotify', 'media_artist') or '' }}

      - name: "Now Playing Album Art"
        state: >
          {% set art = state_attr('media_player.spotify', 'entity_picture') %}
          {% if art %}
            http://homeassistant.local:8123{{ art }}
          {% else %}
            ""
          {% endif %}
```

**Important:**
- Replace `media_player.spotify` with your actual media player entity
- Replace `http://homeassistant.local:8123` if your HA URL is different

**Then:**
1. Save the file
2. Go to Developer Tools → YAML → Check Configuration
3. Restart Home Assistant

**Verify:**
- Go to Developer Tools → States
- Search for `sensor.now_playing_album_art`
- Should show a URL when media is playing

---

## Step 2: Configure Ball V7 YAML

Open `Ball_v7.yaml` and update these lines:

```yaml
substitutions:
  # Your entities
  light_entity: "light.living_room_lamp"           # Your light
  media_player_entity: "media_player.spotify"       # Your media player
  weather_entity: "weather.home"                    # Your weather
```

---

## Step 3: Flash to Device

### Using ESPHome Dashboard:
1. Open ESPHome dashboard
2. Upload `Ball_v7.yaml`
3. Click "Install"
4. Choose install method (WiFi or USB)

### Using ESPHome CLI:
```bash
esphome run Ball_v7.yaml
```

---

## Step 4: Test

1. **Start Playing Media**
   - Play music on your media player
   - Album art should appear within seconds

2. **Navigate to Media Screen**
   - Swipe left from main screen
   - Album art should be visible inside progress arc

3. **Change Tracks**
   - Skip to next song
   - Album art should update automatically

---

## Troubleshooting

### "Album art not showing"

**Check 1:** Template sensor working?
```
Developer Tools → States → sensor.now_playing_album_art
Should show: http://homeassistant.local:8123/api/media_player_proxy/...
```

**Check 2:** ESPHome logs
```
Look for: [album_art] Album art URL: http://...
If not showing, sensor may not be configured correctly
```

**Check 3:** Network connectivity
```
Ping test from device to Home Assistant
Check WiFi connection is stable
```

### "Image not updating"

**Solution:**
- Restart ESPHome device
- Check HA template sensors are updating
- Verify media player provides `entity_picture`

### "No sensors in HA"

**Solution:**
- Verify template sensors added to `configuration.yaml`
- Check YAML syntax is correct
- Restart Home Assistant
- Check Configuration → Logs for errors

---

## What You Should See

```
┌──────────────────────────┐
│ ▓│      ◐──────┐         │  ← Progress arc (green)
│ ▓│      │ Album│         │  ← Album art (100×100)
│ ▓│      │  Art │         │     Rounded corners
│ ▓│      └──────┘         │     Gray border
│ ▓│    Song Title         │  ← Current song
│ ▓│    Artist Name        │  ← Current artist
│ ▓│  [<<]  [▶]  [>>]     │  ← Media controls
└──────────────────────────┘
     ↑
   Volume slider
```

---

## Next Steps

- ✅ Customize entity IDs
- ✅ Test with different media players
- ✅ Adjust display settings if needed
- ✅ Explore all three screens (Main, Media, Weather)

---

## Support

If you encounter issues:

1. Check ESPHome logs for errors
2. Verify Home Assistant template sensors
3. Ensure media player provides album art
4. Review `README.md` for detailed troubleshooting

---

## Credits

Ball V7 by Fear2Die - Album Art Edition  
Based on Ball V6 with album art enhancement
