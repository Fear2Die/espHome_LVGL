# Flow Diagrams: Ball V5 Light Control

This document shows how the light control works in different scenarios.

## Ball V5.0 (Buggy) - Feedback Loop

### User Adjusts Brightness
```
┌─────────────────────────────────────────────────────────────┐
│  USER ACTION: Move brightness slider to 75%                  │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  SLIDER on_value EVENT                                        │
│  • Triggers immediately                                       │
│  • Calls homeassistant.action: light.turn_on                 │
│  • Data: brightness_pct = 75                                 │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  HOME ASSISTANT                                               │
│  • Receives light.turn_on call                               │
│  • Sets light brightness to 75%                              │
│  • Light physically changes                                  │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  HA SENSOR on_value EVENT                                     │
│  • ha_light_brightness detects change                        │
│  • Value: 191 (75% of 255)                                   │
│  • Calls lvgl.slider.update                                  │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  ❌ PROBLEM: SLIDER UPDATED                                  │
│  • lvgl.slider.update sets slider to 75%                     │
│  • THIS TRIGGERS on_value EVENT AGAIN!                       │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  ❌ LOOP: BACK TO SLIDER on_value                            │
│  • Calls homeassistant.action AGAIN                          │
│  • HA receives another command                               │
│  • Sensor detects change AGAIN                               │
│  • INFINITE LOOP → FLICKERING                                │
└─────────────────────────────────────────────────────────────┘
                            ↓
                      FLICKER FLICKER
                      ON OFF ON OFF
```

## Ball V5.1 (Fixed) - Protected Flow

### User Adjusts Brightness
```
┌─────────────────────────────────────────────────────────────┐
│  USER ACTION: Move brightness slider to 75%                  │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  SLIDER on_value EVENT                                        │
│  • Check: updating_light_from_ha = false ✓                   │
│  • Condition passes: User action allowed                     │
│  • Calls homeassistant.action: light.turn_on                 │
│  • Data: brightness_pct = 75                                 │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  HOME ASSISTANT                                               │
│  • Receives light.turn_on call                               │
│  • Sets light brightness to 75%                              │
│  • Light physically changes                                  │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  HA SENSOR on_value EVENT                                     │
│  • ha_light_brightness detects change                        │
│  • Value: 191 (75% of 255)                                   │
│  • 🛡️ SET FLAG: updating_light_from_ha = true               │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  SLIDER UPDATE (Protected)                                    │
│  • lvgl.slider.update sets slider to 75%                     │
│  • This triggers on_value event                              │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  ✅ PROTECTION: SLIDER on_value BLOCKED                      │
│  • Check: updating_light_from_ha = true ✗                    │
│  • Condition fails: Skip HA call                             │
│  • Only update label (visual feedback)                       │
│  • 🛡️ CLEAR FLAG: updating_light_from_ha = false            │
└─────────────────────────────────────────────────────────────┘
                            ↓
                     ✅ DONE - NO LOOP!
```

### External Change (Automation, Voice, Physical Switch)
```
┌─────────────────────────────────────────────────────────────┐
│  EXTERNAL: HA automation sets light to 50%                   │
│  (Not from ESPHome device)                                    │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  HOME ASSISTANT                                               │
│  • Light changes to 50%                                      │
│  • Light physically changes                                  │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  HA SENSOR on_value EVENT                                     │
│  • ha_light_brightness detects change                        │
│  • Value: 127 (50% of 255)                                   │
│  • 🛡️ SET FLAG: updating_light_from_ha = true               │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  SLIDER UPDATE (Protected)                                    │
│  • lvgl.slider.update sets slider to 50%                     │
│  • Display now shows correct value                           │
│  • This triggers on_value event                              │
└─────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────┐
│  ✅ PROTECTION: SLIDER on_value BLOCKED                      │
│  • Check: updating_light_from_ha = true ✗                    │
│  • Condition fails: Skip HA call (correct!)                  │
│  • Device synced with HA, no extra calls                     │
│  • 🛡️ CLEAR FLAG: updating_light_from_ha = false            │
└─────────────────────────────────────────────────────────────┘
                            ↓
              ✅ DEVICE SYNCED WITH HA - NO LOOP!
```

## Comparison Table

| Scenario | Ball V5.0 (Buggy) | Ball V5.1 (Fixed) |
|----------|-------------------|-------------------|
| **User moves slider** | ❌ Triggers loop → Flicker | ✅ Works smoothly |
| **HA automation changes light** | ❌ Triggers loop → Flicker | ✅ Syncs quietly |
| **Voice command changes light** | ❌ Triggers loop → Flicker | ✅ Syncs quietly |
| **External switch/button** | ❌ Triggers loop → Flicker | ✅ Syncs quietly |
| **User moves slider rapidly** | ❌ Multiple loops → Chaos | ✅ Handles smoothly |
| **HA updates during user action** | ❌ Conflicts → Flicker | ✅ Flag prevents conflict |

## Key Concepts

### The Flag Mechanism
```
┌──────────────────────────────────────┐
│  Flag: updating_light_from_ha        │
├──────────────────────────────────────┤
│  Purpose: Prevent feedback loop       │
│  Default: false                       │
│  Set to true: When HA updates device  │
│  Checked by: Slider on_value          │
│  Result: Skip HA call if true         │
└──────────────────────────────────────┘
```

### The Protection Logic
```python
# Pseudocode
def slider_on_value(new_value):
    if updating_light_from_ha == False:  # User action
        call_home_assistant(new_value)
    # Always update label for visual feedback
    update_label(new_value)

def ha_sensor_on_value(new_value):
    updating_light_from_ha = True   # Set flag
    update_slider(new_value)        # This triggers on_value
    updating_light_from_ha = False  # Clear flag
```

## Timing Diagram

### Ball V5.0 (Buggy)
```
Time →
0ms:  User moves slider
10ms: HA receives call
20ms: Light changes
30ms: Sensor detects change
40ms: Slider updates → TRIGGERS ON_VALUE
50ms: HA receives call AGAIN ❌
60ms: Light changes AGAIN
70ms: Sensor detects change AGAIN
80ms: Slider updates AGAIN → TRIGGERS ON_VALUE AGAIN
... INFINITE LOOP ...
```

### Ball V5.1 (Fixed)
```
Time →
0ms:  User moves slider (flag=false)
10ms: HA receives call
20ms: Light changes
30ms: Sensor detects change → SET FLAG
40ms: Slider updates → on_value BLOCKED by flag ✅
50ms: CLEAR FLAG → Ready for next user action
... NO LOOP - DONE ...
```

## State Machine

### Ball V5.1 Flag States
```
     ┌─────────────────┐
     │   IDLE          │
     │ Flag = false    │◄────────┐
     │ Ready for user  │         │
     └────────┬────────┘         │
              │                  │
      User moves slider          │
              │                  │
              ↓                  │
     ┌─────────────────┐         │
     │  CALLING HA     │         │
     │ Flag = false    │         │
     │ HA processes    │         │
     └────────┬────────┘         │
              │                  │
     HA changes light            │
              │                  │
              ↓                  │
     ┌─────────────────┐         │
     │  SYNCING        │         │
     │ Flag = true 🛡️  │         │
     │ Update slider   │         │
     │ Block on_value  │         │
     └────────┬────────┘         │
              │                  │
      Clear flag                 │
              │                  │
              └──────────────────┘
```

## Summary

The fix uses a **semaphore/mutex pattern**:
1. Flag = false: Normal operation, user can control
2. Flag = true: Sync in progress, block new HA calls
3. After sync: Clear flag, ready for next user action

This is a standard pattern for preventing feedback loops in bidirectional control systems and is minimal, efficient, and reliable.

---

**Legend:**
- ✅ Success / Working correctly
- ❌ Problem / Error
- 🛡️ Protection mechanism active
- ↓ Flow direction
- ◄ Loop/Return
