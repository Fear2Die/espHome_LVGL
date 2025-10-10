# Ball V6.1 Verification Checklist

This checklist should be used to verify all changes work correctly on the physical device.

## Pre-Testing Setup

- [ ] Ensure Home Assistant entities are configured:
  - [ ] `light_entity` points to a valid light
  - [ ] `media_player_entity` points to a valid media player
  - [ ] `weather_entity` points to a valid weather integration
- [ ] Flash the updated firmware to the device
- [ ] Verify WiFi connection is established
- [ ] Verify Home Assistant connection is established

## Test 1: Main Screen - Title Removal

**Expected Behavior**: The main screen should NOT have a "Light Control" title at the top.

### Steps:
1. Navigate to the main screen (swipe or boot)
2. Look at the top of the screen

**Verify**:
- [ ] No "Light Control" title is visible at y: 30
- [ ] Time is visible at top-left
- [ ] Battery percentage is visible at top-right
- [ ] "Brightness" label is above the slider
- [ ] "Light Switch" label is above the switch

## Test 2: Weather Screen - Initial Data Display

**Expected Behavior**: Weather data should show placeholders initially, then update with real data.

### Steps:
1. Boot the device or navigate to weather screen immediately after boot
2. Observe initial temperature and humidity values
3. Wait 5-10 seconds for Home Assistant data to arrive

**Verify**:
- [ ] Initial temperature shows "--°" (not "20°")
- [ ] Initial humidity shows "--%" (not "65%")
- [ ] After HA connection, temperature updates to real value (e.g., "22°")
- [ ] After HA connection, humidity updates to real value (e.g., "45%")

## Test 3: Weather Screen - Humidity Container Position

**Expected Behavior**: Humidity container should not clip at the bottom of the screen.

### Steps:
1. Navigate to the weather screen
2. Look at the bottom of the screen where humidity is displayed

**Verify**:
- [ ] Humidity container is fully visible
- [ ] Bottom edge of humidity container is NOT cut off
- [ ] There is visible space (at least 5-10px) between humidity container and screen edge
- [ ] Container position is y: 155 (10px higher than before)

## Test 4: Slider Interaction - No Screen Switching

**Expected Behavior**: Using sliders should NOT trigger screen navigation.

### Steps:
1. Navigate to main screen
2. Touch the brightness slider knob
3. Drag left and right to adjust brightness
4. Release the slider
5. Navigate to media screen
6. Touch the volume arc knob
7. Drag up and down to adjust volume
8. Release the arc

**Verify**:
- [ ] Dragging brightness slider left does NOT switch to weather screen
- [ ] Dragging brightness slider right does NOT switch to media screen
- [ ] Brightness changes as expected when dragging
- [ ] Screen stays on main screen during brightness adjustment
- [ ] Dragging volume arc does NOT switch screens
- [ ] Volume changes as expected when dragging
- [ ] Screen stays on media screen during volume adjustment

## Test 5: Screen Swipe - Still Works Outside Sliders

**Expected Behavior**: Swipe navigation should still work when NOT touching sliders.

### Steps:
1. On main screen, swipe left from empty area (not on slider)
2. Should navigate to media screen
3. Swipe left again
4. Should navigate to weather screen
5. Swipe right
6. Should navigate back to media screen

**Verify**:
- [ ] Swipe left from empty area switches to next screen
- [ ] Swipe right from empty area switches to previous screen
- [ ] Circular navigation works (main → media → weather → main)
- [ ] Swipe gestures are smooth and responsive

## Test 6: Media Screen - Volume Arc Slider

**Expected Behavior**: A half-circle volume control should appear on the right edge.

### Steps:
1. Navigate to media screen
2. Look at the right edge of the screen
3. Touch and drag the arc to adjust volume
4. Check media player volume in Home Assistant

**Verify**:
- [ ] Volume arc is visible on right edge
- [ ] Arc is semi-circular (135° to 45°)
- [ ] Arc has orange indicator color (0xFFB800) - matches brightness slider
- [ ] Arc has white knob
- [ ] Dragging up increases volume
- [ ] Dragging down decreases volume
- [ ] Volume changes are reflected in Home Assistant media player
- [ ] Arc does not interfere with other media controls

## Test 7: Media Screen - Album Art Display

**Expected Behavior**: Album art should display in the center when media is playing.

### Steps:
1. Start playing media on the configured media player
2. Wait for album art to load
3. Navigate to media screen

**Verify**:
- [ ] Album art is visible in center of screen
- [ ] Album art is 100x100 pixels
- [ ] Album art has rounded corners (radius: 10)
- [ ] Album art has gray border (2px)
- [ ] Album art updates when changing songs
- [ ] Progress arc is visible around album art (green indicator)

## Test 8: Media Controls - Still Functional

**Expected Behavior**: All media controls should work as before.

### Steps:
1. Ensure media is playing
2. Test previous track button (<<)
3. Test play/pause button (>/<||)
4. Test next track button (>>)

**Verify**:
- [ ] Previous button skips to previous track
- [ ] Play/Pause button toggles playback
- [ ] Play/Pause label changes between ">" and "||"
- [ ] Next button skips to next track
- [ ] Song title and artist update correctly
- [ ] All buttons are circular (radius: 23)
- [ ] All buttons respond to touch

## Test 9: Light Controls - Still Functional

**Expected Behavior**: Light controls should work as before.

### Steps:
1. Navigate to main screen
2. Toggle the light switch
3. Adjust the brightness slider
4. Check light state in Home Assistant

**Verify**:
- [ ] Light switch toggles light on/off
- [ ] Light state in HA reflects switch state
- [ ] Brightness slider adjusts light brightness
- [ ] Brightness changes are reflected in HA
- [ ] Slider doesn't cause screen to switch (verified in Test 4)
- [ ] Switch has iOS-style appearance (rounded, colored)

## Test 10: General UI Appearance

**Expected Behavior**: Overall UI should look clean and professional.

### Steps:
1. Navigate through all three screens
2. Observe fonts, colors, spacing

**Verify**:
- [ ] All text is readable and properly sized
- [ ] Colors are consistent across screens
- [ ] No UI elements overlap or clip
- [ ] Rounded corners appear smooth
- [ ] Screen transitions are smooth (250ms)
- [ ] No visual glitches during navigation

## Issues Found

Document any issues discovered during testing:

| Test # | Issue Description | Severity | Notes |
|--------|------------------|----------|-------|
|        |                  |          |       |

## Sign-Off

- **Tester Name**: ___________________________
- **Test Date**: ___________________________
- **Device Version**: ___________________________
- **ESPHome Version**: ___________________________
- **Result**: [ ] All tests passed [ ] Issues found (see above)

## Notes

Additional observations or comments:
```




```
