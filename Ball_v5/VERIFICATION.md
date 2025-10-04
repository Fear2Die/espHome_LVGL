# Ball V5 - Verification Checklist

## Pre-Installation Verification

### Files Required ✓
- [ ] Ball_v5.yaml (1,613 lines)
- [ ] secrets.yaml (created from example)
- [ ] README.md
- [ ] CHANGES.md
- [ ] QUICK_START.md
- [ ] SUMMARY.md
- [ ] LAYOUT.md
- [ ] COMPARISON.md
- [ ] VERIFICATION.md (this file)

### Home Assistant Entities Required ✓
- [ ] Light entity configured and working
- [ ] Media player entity configured and working
- [ ] Weather entity configured and working

**Verification Commands:**
```bash
# In Home Assistant Developer Tools → States
# Check these entities exist:
light.YOUR_LIGHT_ENTITY
media_player.YOUR_MEDIA_PLAYER_ENTITY
weather.YOUR_WEATHER_ENTITY
```

### Configuration Verification ✓

#### WiFi Settings
- [ ] secrets.yaml created
- [ ] WiFi SSID configured
- [ ] WiFi password configured
- [ ] Fallback AP password set

#### Entity IDs Replaced
- [ ] All 5 light entity references updated
- [ ] All 8 media player entity references updated
- [ ] All 3 weather entity references updated

**Quick Check:**
```bash
# Should return 0 (no matches)
grep -c "YOUR_LIGHT_ENTITY" Ball_v5.yaml
grep -c "YOUR_MEDIA_PLAYER_ENTITY" Ball_v5.yaml
grep -c "YOUR_WEATHER_ENTITY" Ball_v5.yaml
```

## Installation Verification

### Flashing Success ✓
- [ ] ESPHome compile succeeded
- [ ] No error messages during flash
- [ ] Device boots without errors
- [ ] Device shows up in ESPHome dashboard

### Home Assistant Integration ✓
- [ ] Device appears in HA integrations
- [ ] Device is "Online" status
- [ ] HA Actions permission enabled
- [ ] Device entities visible in HA

**Enable HA Actions:**
1. Settings → Devices & Services → ESPHome
2. Find "Ball V5" device
3. Configure → Allow device to perform HA actions
4. Submit

## Functional Verification

### Main Page (Idle) Tests

#### Display Elements ✓
- [ ] Time displays correctly (HH:MM format)
- [ ] Status shows "Ready" (green)
- [ ] Battery percentage displays
- [ ] All text is readable
- [ ] No overlapping elements

#### Light Control ✓
- [ ] Brightness slider responds to touch
- [ ] Slider moves smoothly (no lag)
- [ ] Brightness label updates as slider moves
- [ ] Light actually changes brightness in HA
- [ ] Toggle button works (on/off)

#### Live State Colors ✓
- [ ] Turn light OFF in HA → Slider turns GRAY (#555555)
- [ ] Turn light ON in HA → Slider turns YELLOW (#FFCC66)
- [ ] Toggle button changes color with light state
- [ ] Color changes happen within 1-2 seconds
- [ ] Colors persist after page navigation

**Test Procedure:**
```
1. From HA: Turn light off
   → Wait 2 seconds
   → Check: Slider is gray
   
2. From HA: Turn light on
   → Wait 2 seconds
   → Check: Slider is yellow
   
3. From device: Toggle button
   → Check: Light changes state
   → Check: Colors update
```

#### Navigation Buttons ✓
- [ ] "Media" button visible at bottom left
- [ ] "Weather" button visible at bottom right
- [ ] Both buttons respond to touch
- [ ] Touch feedback is immediate
- [ ] Buttons are properly sized

### Media Page Tests

#### Navigation ✓
- [ ] "Media" button takes you to media page
- [ ] Page transition is smooth
- [ ] Back button returns to main page
- [ ] Back button is visible and accessible

#### Display Elements ✓
- [ ] Media title displays (or "No media")
- [ ] Artist name displays (if available)
- [ ] Media state shows (▶ Playing, ⏸ Paused, ⏹ Idle)
- [ ] Volume label displays
- [ ] All text is readable

#### Media Controls ✓
- [ ] Previous button (⏮) responds to touch
- [ ] Play/Pause button (⏯) responds to touch
- [ ] Next button (⏭) responds to touch
- [ ] Volume slider responds to touch
- [ ] Media player actually responds in HA

**Test Procedure:**
```
1. Start playing media in HA
   → Check: Title and artist appear
   → Check: State shows "▶ Playing"
   
2. Press play/pause button
   → Check: Media pauses
   → Check: State changes to "⏸ Paused"
   
3. Press next button
   → Check: Next track plays
   → Check: Title updates
   
4. Move volume slider
   → Check: Volume changes in HA
   → Check: Slider moves smoothly
```

#### Live Sync ✓
- [ ] Change media in HA → Title updates on device
- [ ] Change volume in HA → Slider updates on device
- [ ] Pause in HA → State updates on device
- [ ] Play in HA → State updates on device

### Weather Page Tests

#### Navigation ✓
- [ ] "Weather" button takes you to weather page
- [ ] Page transition is smooth
- [ ] Back button returns to main page
- [ ] Back button is visible and accessible

#### Display Elements ✓
- [ ] Weather condition displays
- [ ] Temperature displays with unit (°C)
- [ ] Humidity displays with percentage
- [ ] All text is readable
- [ ] Temperature is large and prominent

#### Live Sync ✓
- [ ] Weather data loads on first visit
- [ ] Temperature matches HA weather entity
- [ ] Humidity matches HA weather entity
- [ ] Condition matches HA weather entity
- [ ] Updates when weather changes in HA

**Test Procedure:**
```
1. Navigate to weather page
   → Check: Data loads within 2 seconds
   → Check: Temperature shows correctly
   → Check: Humidity shows correctly
   
2. Compare with HA weather entity
   → Check: Values match exactly
   
3. Wait for weather update (15-30 min)
   → Check: Device updates automatically
```

### Voice Assistant Tests

#### Activation ✓
- [ ] Physical button activates assistant
- [ ] Wake word activates assistant
- [ ] Touch screen does NOT activate assistant
- [ ] Activation is immediate

#### Status Pages ✓
- [ ] Listening page appears (blue background)
- [ ] Thinking page appears (orange background)
- [ ] Replying page appears (green background)
- [ ] Timer finished page appears (red background)
- [ ] Error page appears on errors
- [ ] Muted page appears when muted

#### Voice Commands ✓
- [ ] Simple commands work ("What time is it?")
- [ ] Light control works ("Turn on the lights")
- [ ] Timer works ("Set a timer for 5 minutes")
- [ ] Responses play through speaker
- [ ] Text appears on thinking/replying pages

### Battery Tests

#### Display ✓
- [ ] Battery percentage visible
- [ ] Percentage accurate (compare to HA)
- [ ] Updates in real-time
- [ ] Long-press toggles display (if configured)

### Touch Screen Tests

#### Responsiveness ✓
- [ ] All buttons respond immediately
- [ ] Sliders respond smoothly
- [ ] No ghost touches
- [ ] No missed touches
- [ ] Touch zones are appropriate size

#### Navigation Flow ✓
- [ ] Main → Media → Main works
- [ ] Main → Weather → Main works
- [ ] Voice assistant doesn't interrupt navigation
- [ ] Pages remember state after navigation

## Performance Verification

### Speed Tests ✓
- [ ] Page switching < 200ms
- [ ] Touch response < 100ms
- [ ] Slider updates real-time
- [ ] Color changes < 2 seconds
- [ ] Media updates < 2 seconds
- [ ] Weather updates < 2 seconds

### Stability Tests ✓
- [ ] No crashes after 1 hour
- [ ] No memory leaks (check logs)
- [ ] No disconnections
- [ ] No display glitches
- [ ] No touch issues

### Network Tests ✓
- [ ] Works on WiFi
- [ ] Survives WiFi disconnection
- [ ] Reconnects automatically
- [ ] HA Actions work after reconnect
- [ ] Sensors update after reconnect

## Edge Case Testing

### Missing Entities ✓
- [ ] Works if media player unavailable
- [ ] Works if weather unavailable
- [ ] Shows appropriate message
- [ ] Doesn't crash

### State Transitions ✓
- [ ] Light off → on → off works
- [ ] Media play → pause → play works
- [ ] Page navigation doesn't break states
- [ ] Voice assistant doesn't interfere

### Long-Running Tests ✓
- [ ] 24-hour uptime test
- [ ] Battery drain test
- [ ] Temperature stability
- [ ] No performance degradation

## ESPHome Validation

### Configuration Check
```bash
# Validate YAML syntax
esphome config Ball_v5.yaml

# Expected: No errors, only warnings about strapping pins (normal)
```

### Log Check ✓
- [ ] No ERROR messages
- [ ] No repeated WARNINGs
- [ ] Sensors update as expected
- [ ] Actions execute successfully

**Check Logs:**
```bash
# ESPHome logs
esphome logs Ball_v5.yaml

# Look for:
✓ [sensor] Got state update
✓ [text_sensor] Got state update
✓ No errors or warnings
```

## Compliance Verification

### ESPHome Standards ✓
- [ ] Valid YAML format
- [ ] Compatible with ESPHome 2025.5.0+
- [ ] Uses standard components
- [ ] No deprecated features
- [ ] Follows naming conventions

### Home Assistant Standards ✓
- [ ] Proper entity naming
- [ ] Standard units (%, °C)
- [ ] Correct service calls
- [ ] Valid entity IDs
- [ ] HA Actions permission set

### LVGL Standards ✓
- [ ] Valid widget configuration
- [ ] Proper event handlers
- [ ] Correct coordinate system
- [ ] No widget overlaps
- [ ] Proper color format (0xRRGGBB)

## Documentation Verification

### README.md ✓
- [ ] Setup instructions clear
- [ ] Entity configuration explained
- [ ] Troubleshooting section helpful
- [ ] All features documented

### QUICK_START.md ✓
- [ ] 5-minute setup achievable
- [ ] Steps are accurate
- [ ] Entity replacement clear
- [ ] Testing steps work

### CHANGES.md ✓
- [ ] All changes documented
- [ ] Technical details accurate
- [ ] Migration guide helpful
- [ ] Code examples valid

### LAYOUT.md ✓
- [ ] Layouts accurate
- [ ] Dimensions correct
- [ ] Colors match actual
- [ ] Positioning clear

## Known Issues & Limitations

### Expected Warnings ✓
- [ ] Underscore in hostname (cosmetic)
- [ ] GPIO 45/46 strapping pins (hardware limitation)
- [ ] Lambda expressions (ESPHome quirk)

**These warnings are normal and don't affect functionality.**

### Limitations ✓
- [ ] Single light control only
- [ ] No album artwork
- [ ] Basic weather (no forecast)
- [ ] Fixed layouts
- [ ] Text-only interface

**These are design decisions, not bugs.**

## Final Verification

### All Systems Go ✓
- [ ] Device boots reliably
- [ ] All 3 main pages work
- [ ] All sensors update
- [ ] All controls work
- [ ] Voice assistant works
- [ ] Live states work
- [ ] Navigation works
- [ ] No errors in logs

### Ready for Use ✓
- [ ] User has tested all features
- [ ] All entity IDs configured
- [ ] HA Actions enabled
- [ ] Documentation reviewed
- [ ] Backup configuration saved

## Post-Installation

### Backup ✓
```bash
# Save your working configuration
cp Ball_v5.yaml Ball_v5_working_backup.yaml
cp secrets.yaml secrets_backup.yaml
```

### Monitoring
- [ ] Add to HA dashboard
- [ ] Set up automation alerts
- [ ] Monitor battery level
- [ ] Watch for errors

### Customization
- [ ] Adjust colors if desired
- [ ] Customize entity names
- [ ] Add to HA scenes
- [ ] Create automations

## Sign-off

### Installation Date
- Date: __________
- Time: __________
- Installer: __________

### Verification Results
- [ ] All core tests passed
- [ ] All page tests passed
- [ ] All control tests passed
- [ ] All performance tests passed
- [ ] Ready for production use

### Notes
```
Add any issues, observations, or customizations here:




```

## Support Checklist

If you encounter issues:

1. [ ] Check this verification checklist
2. [ ] Review README.md troubleshooting
3. [ ] Verify entity IDs are correct
4. [ ] Check HA Actions are enabled
5. [ ] Review ESPHome logs
6. [ ] Test entities in HA directly
7. [ ] Verify WiFi connection
8. [ ] Check Home Assistant connection
9. [ ] Try rebooting device
10. [ ] Try reflashing if needed

## Success Criteria

✅ **Ball V5 is successfully installed when:**

1. Device boots without errors
2. All 3 main pages are accessible
3. Light controls work with live colors
4. Media controls work with live state
5. Weather displays current data
6. Voice assistant responds correctly
7. Navigation buttons work perfectly
8. No errors in ESPHome logs
9. Battery and time display correctly
10. User is satisfied with functionality

---

**If all checkboxes are checked, congratulations!** 🎉

Your Ball V5 is fully operational and ready to enhance your smart home experience!
