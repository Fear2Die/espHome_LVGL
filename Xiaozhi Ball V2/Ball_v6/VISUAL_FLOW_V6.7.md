# Ball V6.7 - Visual Flow Diagram

## Album Art Retrieval Flow

### Configuration
```
┌─────────────────────────────────────────────────────────┐
│ Ball_v6.yaml - Entity Configuration (Lines 28-35)      │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  ha_base_url: "http://homeassistant.local:8123"        │
│  ha_token: ""                                           │
│                                                         │
│  [Optional: Add your long-lived access token]          │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### Process Flow

```
┌──────────────────────────────────────────────────────────────────────┐
│ 1. Media Playing in Home Assistant                                   │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   media_player.spotify                                               │
│   └─ entity_picture: "/api/media_player_proxy/media_player.spotify" │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 2. ESPHome Monitors entity_picture Attribute (Line 1223)            │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   text_sensor:                                                       │
│     - platform: homeassistant                                        │
│       id: ha_media_picture                                           │
│       entity_id: ${media_player_entity}                              │
│       attribute: entity_picture                                      │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 3. Smart URL Construction (Lines 1226-1248)                         │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   if (url starts with '/') {                                         │
│     // Relative URL from Home Assistant                             │
│     url = ha_base_url + url                                          │
│     if (ha_token not empty) {                                        │
│       url += "?access_token=" + ha_token                             │
│     }                                                                │
│   } else {                                                           │
│     // Absolute URL (Spotify, etc.)                                  │
│     use as-is                                                        │
│   }                                                                  │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                ┌───────────────────┴────────────────────┐
                │                                        │
                ▼                                        ▼
    ┌──────────────────────┐              ┌──────────────────────────┐
    │ Relative URL         │              │ Absolute URL             │
    │ (Home Assistant)     │              │ (External Source)        │
    ├──────────────────────┤              ├──────────────────────────┤
    │                      │              │                          │
    │ INPUT:               │              │ INPUT:                   │
    │ "/api/media_player   │              │ "https://i.scdn.co/      │
    │  _proxy/..."         │              │  image/..."              │
    │                      │              │                          │
    │ OUTPUT (no token):   │              │ OUTPUT:                  │
    │ "http://homeassist   │              │ "https://i.scdn.co/      │
    │  ant.local:8123/api  │              │  image/..."              │
    │  /media_player_pro   │              │ (unchanged)              │
    │  xy/..."             │              │                          │
    │                      │              │                          │
    │ OUTPUT (with token): │              │                          │
    │ "http://homeassist   │              │                          │
    │  ant.local:8123/api  │              │                          │
    │  /media_player_pro   │              │                          │
    │  xy/...?access_to    │              │                          │
    │  ken=YOUR_TOKEN"     │              │                          │
    │                      │              │                          │
    └──────────────────────┘              └──────────────────────────┘
                │                                        │
                └───────────────────┬────────────────────┘
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 4. HTTP Request Component Fetches Image (Line 163)                  │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   http_request:                                                      │
│     timeout: 10s                                                     │
│                                                                      │
│   Downloads image data over HTTP/HTTPS                              │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 5. Online Image Component Processes (Lines 168-173)                 │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   online_image:                                                      │
│     - id: album_art_image                                            │
│       type: RGB565                                                   │
│       format: PNG                                                    │
│       resize: 100x100                                                │
│                                                                      │
│   Converts image to display format and caches                       │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 6. LVGL Widget Displays Album Art (Lines 1420-1427)                 │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   - image:                                                           │
│       id: album_art_display                                          │
│       src: album_art_image                                           │
│       align: TOP_MID                                                 │
│       y: 30                                                          │
│       radius: 10                                                     │
│       border_width: 2                                                │
│                                                                      │
│   100x100 rounded square with border                                │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
                    ┌───────────────────────────┐
                    │  👁  User sees album art   │
                    └───────────────────────────┘
```

---

## Progress Arc Update Flow

### Real-Time Animation

```
┌──────────────────────────────────────────────────────────────────────┐
│ 1. Home Assistant Media Player Updates (Every Second)               │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   media_player.spotify                                               │
│   ├─ media_position: 45.2 seconds                                    │
│   └─ media_duration: 180.0 seconds                                   │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                ┌───────────────────┴───────────────────┐
                ▼                                       ▼
┌────────────────────────────────┐  ┌────────────────────────────────┐
│ 2. Position Sensor             │  │ 2. Duration Sensor             │
│    (Lines 307-325)             │  │    (Lines 328-347)             │
├────────────────────────────────┤  ├────────────────────────────────┤
│                                │  │                                │
│ ha_media_position              │  │ ha_media_duration              │
│ attribute: media_position      │  │ attribute: media_duration      │
│                                │  │                                │
│ Receives: 45.2                 │  │ Receives: 180.0                │
│                                │  │                                │
└────────────────────────────────┘  └────────────────────────────────┘
                │                                       │
                └───────────────────┬───────────────────┘
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 3. Progress Calculation (Lambda Function)                           │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   float progress = (position / duration) * 100.0;                    │
│   = (45.2 / 180.0) * 100.0                                           │
│   = 25.1%                                                            │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 4. Arc Widget Update (Lines 316-325, 337-347)                       │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   lvgl.arc.update:                                                   │
│     id: media_progress_arc                                           │
│     value: 25.1                                                      │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
┌──────────────────────────────────────────────────────────────────────┐
│ 5. LVGL Arc Widget Displays Progress (Lines 1430-1444)              │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│   - arc:                                                             │
│       id: media_progress_arc                                         │
│       width: 120                                                     │
│       height: 120                                                    │
│       min_value: 0                                                   │
│       max_value: 100                                                 │
│       value: 25.1    ← Updates in real-time!                         │
│       indicator:                                                     │
│         arc_color: 0x1DB954  (Spotify green)                         │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
                                    │
                                    ▼
                    ┌───────────────────────────┐
                    │  👁  User sees progress    │
                    │      arc animate           │
                    └───────────────────────────┘

Updates automatically as position changes (typically every second)
```

---

## Visual Layout on Display

```
┌─────────────────────────────────────┐
│         Media Screen (240x240)      │
│                                     │
│              ┌─────────┐            │
│           ╱  │         │  ╲         │ ← Progress Arc (120x120)
│         ╱    │ Album   │    ╲       │   Green indicator
│        │     │  Art    │     │      │   Shows 0-100% progress
│        │     │(100x100)│     │      │
│         ╲    │         │    ╱       │
│           ╲  │         │  ╱         │
│              └─────────┘            │
│                                     │
│          Song Title Here            │ ← Scrolling text
│          Artist Name                │ ← Secondary text
│                                     │
│      [<<]    [>]    [>>]            │ ← Control buttons
│                                     │
└─────────────────────────────────────┘

Progress Arc Colors:
- Background: 0x2A2A2A (dark gray)
- Indicator: 0x1DB954 (Spotify green)
- Width: 4px
```

---

## Configuration Decision Tree

```
                    Start Setup
                         │
                         ▼
                Is HA on local network?
                         │
        ┌────────────────┼────────────────┐
        │                │                │
       Yes              Mix              No (Remote)
        │                │                │
        ▼                ▼                ▼
    Try without    Try without      Requires token
    token first      token             │
        │                │                │
        ▼                ▼                ▼
  Album art       Album art        Generate token
  works?          works?           from HA profile
        │                │                │
    ┌───┴───┐        ┌───┴───┐           │
   Yes     No       Yes     No           │
    │       │        │       │            │
    ▼       ▼        ▼       ▼            ▼
  Done  Add token  Done  Add token   Add to config
                                          │
                                          ▼
                                      Test again
                                          │
                                          ▼
                                        Done
```

---

## File Structure

```
Ball_v6/
├── Ball_v6.yaml ⭐ (Modified)
│   ├── Lines 28-35: New token config
│   ├── Line 169: Updated base URL
│   └── Lines 1226-1248: Smart URL construction
│
├── ALBUM_ART_TOKEN_AUTH.md ⭐ (New)
│   └── Complete setup guide (8.6 KB)
│
├── QUICK_START_TOKEN_AUTH.md ⭐ (New)
│   └── Quick reference (4.8 KB)
│
├── CHANGES_V6.7.md ⭐ (New)
│   └── Detailed changelog (11 KB)
│
├── IMPLEMENTATION_SUMMARY_V6.7.md ⭐ (New)
│   └── Implementation details (8.6 KB)
│
├── VISUAL_FLOW_V6.7.md ⭐ (New - This file)
│   └── Visual diagrams (this file)
│
├── README.md (Updated)
│   └── Added configuration section
│
└── CHANGELOG.md (Updated)
    └── Added V6.7 entry

⭐ = Modified or new in V6.7
```

---

## Key Improvements Summary

### Before V6.7
```
❌ Hardcoded URL: http://homeassistant.local:8123
❌ No authentication support
❌ Failed with authenticated HA instances
❌ Didn't work with remote access
```

### After V6.7
```
✅ Configurable base URL
✅ Optional token authentication
✅ Works with authenticated HA
✅ Supports remote access (HTTPS)
✅ Smart URL construction
✅ Backward compatible
✅ Comprehensive documentation
```

---

## Token Security Flow

```
┌────────────────────────────────────────────────────┐
│ 1. Generate in Home Assistant                      │
├────────────────────────────────────────────────────┤
│   Profile → Long-Lived Access Tokens               │
│   → Create Token → Copy (shown once!)              │
└────────────────────────────────────────────────────┘
                     │
                     ▼
┌────────────────────────────────────────────────────┐
│ 2. Store in Ball_v6.yaml (or secrets.yaml)        │
├────────────────────────────────────────────────────┤
│   ha_token: "eyJhbGciOiJIUzI1NiIsInR5cCI..."     │
│   (Not logged, not exposed in UI)                  │
└────────────────────────────────────────────────────┘
                     │
                     ▼
┌────────────────────────────────────────────────────┐
│ 3. Used only for HTTP requests to HA               │
├────────────────────────────────────────────────────┤
│   Added as query parameter: ?access_token=TOKEN    │
│   Sent over HTTPS when using remote URL            │
└────────────────────────────────────────────────────┘
                     │
                     ▼
┌────────────────────────────────────────────────────┐
│ 4. Home Assistant validates and serves image       │
├────────────────────────────────────────────────────┤
│   Token verified → Image served                     │
│   Token invalid → 401 Unauthorized                  │
└────────────────────────────────────────────────────┘
```

---

**Version**: Ball V6.7  
**Last Updated**: 2025-10-11  
**Purpose**: Visual documentation of implementation
