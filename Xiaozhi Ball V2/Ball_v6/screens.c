#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

// Current screen index for circular navigation
static uint8_t current_screen_index = 0;
#define SCREEN_COUNT 3

// Forward declarations for screen management
static void navigate_to_screen(uint8_t screen_index);
static void screen_gesture_event_cb(lv_event_t *e);

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Enable gesture detection for swipe navigation
    lv_obj_add_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_add_event_cb(obj, screen_gesture_event_cb, LV_EVENT_GESTURE, NULL);
    
    {
        lv_obj_t *parent_obj = obj;
        {
            // Light Toggle Switch - modern iOS-style
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 75, 175);
            lv_obj_set_size(obj, 90, 40);
            lv_obj_set_style_radius(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3a3a3a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, -100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, -100, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff666666), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 18, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, -8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, -8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, -8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, -8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff34c759), LV_PART_INDICATOR | LV_STATE_CHECKED);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff34c759), LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            // Brightness Slider - sleek and modern
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 26, 115);
            lv_obj_set_size(obj, 188, 30);
            lv_slider_set_range(obj, 0, 100);
            lv_slider_set_value(obj, 50, LV_ANIM_OFF);
            lv_obj_set_style_radius(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2a2a2a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 15, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffb800), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_all(obj, 4, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(obj, 8, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0x00000000), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 100, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // Brightness Icon/Label - sun icon position
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.brightness_label = obj;
            lv_obj_set_pos(obj, 0, 90);
            lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffaaaaaa), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Brightness");
        }
        {
            // Light Status Label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.light_status = obj;
            lv_obj_set_pos(obj, 0, 155);
            lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Light Control");
        }
        {
            // Date
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.date = obj;
            lv_obj_set_pos(obj, 51, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "10:10");
        }
        {
            // Battery
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.battery = obj;
            lv_obj_set_pos(obj, 153, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "100%");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_media() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.media = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Enable gesture detection for swipe navigation
    lv_obj_add_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_add_event_cb(obj, screen_gesture_event_cb, LV_EVENT_GESTURE, NULL);
    
    {
        lv_obj_t *parent_obj = obj;
        {
            // Previous Track
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.back = obj;
            lv_obj_set_pos(obj, 52, 176);
            lv_obj_set_size(obj, 45, 45);
            lv_obj_set_style_radius(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff333333), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Label_Previous
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_back = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "<<");
                }
            }
        }
        {
            // Next Track
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.forward = obj;
            lv_obj_set_pos(obj, 143, 176);
            lv_obj_set_size(obj, 45, 45);
            lv_obj_set_style_radius(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff333333), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Label_Next
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_forward = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ">>");
                }
            }
        }
        {
            // Play/Pause
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.pause = obj;
            lv_obj_set_pos(obj, 98, 176);
            lv_obj_set_size(obj, 45, 45);
            lv_obj_set_style_radius(obj, 23, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4a4a4a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Label_Play
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pause = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, ">");
                }
            }
        }
        {
            // Album Art Image - centered at top with rounded corners
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.media_img = obj;
            lv_obj_set_pos(obj, 70, 30);
            lv_obj_set_size(obj, 100, 100);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff666666), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Progress arc - subtle and elegant
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.media_arc = obj;
            lv_obj_set_pos(obj, 60, 20);
            lv_obj_set_size(obj, 120, 120);
            lv_arc_set_range(obj, 0, 100);
            lv_arc_set_value(obj, 25);
            lv_arc_set_bg_angles(obj, 0, 360);
            lv_obj_set_style_arc_width(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff2a2a2a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 4, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff1db954), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_remove_style(obj, NULL, LV_PART_KNOB);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // Song Title Label - below album art
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.media_title = obj;
            lv_obj_set_pos(obj, 0, 140);
            lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_label_set_text(obj, "Song Title");
        }
        {
            // Artist Label - below title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.media_artist = obj;
            lv_obj_set_pos(obj, 0, 158);
            lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffaaaaaa), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_label_set_text(obj, "Artist Name");
        }
    }
    
    tick_screen_media();
}

void tick_screen_media() {
}

void create_screen_weather() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.weather = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 240);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Enable gesture detection for swipe navigation
    lv_obj_add_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_add_event_cb(obj, screen_gesture_event_cb, LV_EVENT_GESTURE, NULL);
    
    {
        lv_obj_t *parent_obj = obj;
        {
            // Weather Title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.weather_title = obj;
            lv_obj_set_pos(obj, 0, 30);
            lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffaaaaaa), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Weather");
        }
        {
            // Weather Condition Icon/Text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.weather_condition = obj;
            lv_obj_set_pos(obj, 0, 60);
            lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff87ceeb), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Partly Cloudy");
        }
        {
            // Temperature - large centered display
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp = obj;
            lv_obj_set_pos(obj, 0, 95);
            lv_obj_set_size(obj, 240, LV_SIZE_CONTENT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "20°");
        }
        {
            // Humidity Container - bottom section
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 30, 165);
            lv_obj_set_size(obj, 180, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1a1a1a), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff333333), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_all(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Humidity label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.humidity_label = obj;
                    lv_obj_set_pos(obj, 0, 2);
                    lv_obj_set_size(obj, 164, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff888888), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Humidity");
                }
                {
                    // Humidity value
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.humidity_insert = obj;
                    lv_obj_set_pos(obj, 0, 18);
                    lv_obj_set_size(obj, 164, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff87ceeb), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "65%");
                }
            }
        }
    }
    
    tick_screen_weather();
}

void tick_screen_weather() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_media,
    tick_screen_weather,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

// Gesture event callback for swipe navigation
static void screen_gesture_event_cb(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    
    if (event_code == LV_EVENT_GESTURE) {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        
        // Wait for gesture to complete
        lv_indev_wait_release(lv_indev_get_act());
        
        switch(dir) {
            case LV_DIR_LEFT:
                // Swipe left: go to next screen (circular)
                current_screen_index = (current_screen_index + 1) % SCREEN_COUNT;
                navigate_to_screen(current_screen_index);
                break;
                
            case LV_DIR_RIGHT:
                // Swipe right: go to previous screen (circular)
                current_screen_index = (current_screen_index + SCREEN_COUNT - 1) % SCREEN_COUNT;
                navigate_to_screen(current_screen_index);
                break;
                
            default:
                // Ignore other gestures
                break;
        }
    }
}

// Navigate to a specific screen with animation
static void navigate_to_screen(uint8_t screen_index) {
    lv_obj_t *target_screen = NULL;
    lv_scr_load_anim_t anim_type;
    
    // Determine animation direction based on navigation
    if (screen_index == ((current_screen_index + SCREEN_COUNT - 1) % SCREEN_COUNT)) {
        anim_type = LV_SCR_LOAD_ANIM_MOVE_RIGHT;
    } else {
        anim_type = LV_SCR_LOAD_ANIM_MOVE_LEFT;
    }
    
    // Select target screen
    switch(screen_index) {
        case 0:
            target_screen = objects.main;
            break;
        case 1:
            target_screen = objects.media;
            break;
        case 2:
            target_screen = objects.weather;
            break;
        default:
            target_screen = objects.main;
            current_screen_index = 0;
            break;
    }
    
    // Load the screen with smooth slide animation (250ms)
    if (target_screen != NULL) {
        lv_scr_load_anim(target_screen, anim_type, 250, 0, false);
    }
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_media();
    create_screen_weather();
    
    // Load the main screen initially
    current_screen_index = 0;
    lv_scr_load(objects.main);
}
