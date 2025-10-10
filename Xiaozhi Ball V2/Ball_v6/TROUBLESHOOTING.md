# Ball V6 Troubleshooting Guide

## Common Compilation Issues

### Error: 'touch' was not declared in this scope

**Symptom**: Compilation fails with error about `touch` variable not being declared.

**Cause**: Trying to access `touch.x` or `touch.y` outside of the immediate lambda block where they're available.

**Solution**: Store touch coordinates in global variables immediately when they're available:

```yaml
touchscreen:
  - platform: cst816
    on_touch:
      then:
        - lambda: |-
            id(touch_x) = touch.x;  # Store immediately
            id(touch_y) = touch.y;
    on_release:
      then:
        - lambda: |-
            id(release_x) = touch.x;  # Store immediately
            id(release_y) = touch.y;
        # Now use stored values in subsequent blocks
        - lambda: |-
            int dx = id(release_x) - id(touch_x);
```

### Error: 'class esphome::lvgl::LvPageType' has no member named 'show'

**Symptom**: Compilation fails when trying to call `.show()` on a page object.

**Cause**: ESPHome's LVGL integration uses action framework, not direct C++ methods.

**Wrong**:
```yaml
- lambda: |-
    id(my_page).show();  # ❌ This doesn't work
```

**Correct**:
```yaml
- lvgl.page.show: my_page  # ✅ Use ESPHome action syntax
```

**For Conditional Navigation**:
```yaml
- if:
    condition:
      lambda: 'return some_condition;'
    then:
      - lvgl.page.show: my_page
```

## Design Patterns

### Pattern 1: Touch Gesture Detection

When implementing swipe gestures or complex touch interactions:

1. **Capture**: Store coordinates immediately when touch events occur
2. **Calculate**: Perform calculations in lambda using stored values
3. **Decide**: Set flags/globals based on calculations
4. **Act**: Use ESPHome actions based on flags

```yaml
on_release:
  then:
    # 1. CAPTURE
    - lambda: |-
        id(end_x) = touch.x;
        id(end_y) = touch.y;
    
    # 2. CALCULATE
    - lambda: |-
        int distance = sqrt(pow(id(end_x) - id(start_x), 2) + 
                          pow(id(end_y) - id(start_y), 2));
        id(swipe_detected) = (distance > 50);
    
    # 3. DECIDE (implicit in if/then)
    # 4. ACT
    - if:
        condition:
          lambda: 'return id(swipe_detected);'
        then:
          - lvgl.page.show: next_page
```

### Pattern 2: Separating Logic from Actions

**Don't Mix** C++ calls and ESPHome actions in the same lambda:

❌ **Bad**:
```yaml
- lambda: |-
    if (condition) {
      id(some_page).show();  // Won't work
    }
```

✅ **Good**:
```yaml
- lambda: |-
    // Just calculate and store
    id(should_navigate) = condition;
- if:
    condition:
      lambda: 'return id(should_navigate);'
    then:
      - lvgl.page.show: some_page
```

### Pattern 3: Multi-Page Navigation

For navigation between multiple pages based on state:

```yaml
globals:
  - id: current_page
    type: int
    initial_value: '0'
  - id: target_page
    type: int
    initial_value: '0'

# Calculate target page in lambda
- lambda: |-
    if (swipe_left) {
      id(target_page) = (id(current_page) + 1) % 3;
    } else if (swipe_right) {
      id(target_page) = (id(current_page) + 2) % 3;
    }

# Navigate based on target
- if:
    condition:
      lambda: 'return id(target_page) == 0;'
    then:
      - lvgl.page.show: page_0
      - lambda: 'id(current_page) = 0;'
- if:
    condition:
      lambda: 'return id(target_page) == 1;'
    then:
      - lvgl.page.show: page_1
      - lambda: 'id(current_page) = 1;'
```

## Debugging Tips

### Check Configuration Syntax

Always validate your configuration before uploading:

```bash
esphome config ball_v6.yaml
```

### Enable Debug Logging

Add temporary logging to understand what's happening:

```yaml
- lambda: |-
    ESP_LOGD("touch", "Touch at x=%d, y=%d", touch.x, touch.y);
    id(stored_x) = touch.x;
```

### Test Incrementally

When adding complex features:

1. Start with simple logging
2. Add coordinate storage
3. Add calculation logic
4. Add conditional navigation
5. Test at each step

### Common Global Variable Types

```yaml
globals:
  - id: coordinate
    type: int
    restore_value: no
    initial_value: '0'
  
  - id: is_swiping
    type: bool
    restore_value: no
    initial_value: 'false'
  
  - id: swipe_distance
    type: float
    restore_value: no
    initial_value: '0.0'
```

## Configuration Validation Checklist

Before uploading to your device:

- [ ] All `touch.x` and `touch.y` references are in the immediate lambda block
- [ ] Touch coordinates are stored in globals for later use
- [ ] No `.show()` or other C++ method calls on LVGL objects
- [ ] All page navigation uses `lvgl.page.show:` action syntax
- [ ] Lambda expressions only compute/decide, don't execute actions
- [ ] All required global variables are declared
- [ ] Configuration validates with `esphome config`

## Getting Help

If you encounter issues not covered here:

1. Check the [ESPHome documentation](https://esphome.io/)
2. Search [ESPHome discussions](https://github.com/esphome/esphome/discussions)
3. Review the `FIXES.md` file for detailed technical explanation
4. Check ESPHome logs for specific error messages

## Version Information

- **ESPHome**: 2025.5.0 or later
- **LVGL**: Built into ESPHome
- **Platform**: ESP32-S3

## Related Files

- `FIXES.md` - Detailed technical explanation of the fixes
- `Ball_v6.yaml` - Main configuration file
- `LAYOUT.md` - UI design and layout documentation
