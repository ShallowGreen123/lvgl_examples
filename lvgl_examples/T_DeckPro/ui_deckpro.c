
#include "ui_deckpro.h"
#include "ui_deckpro_port.h"

#if UI_DECKPRO_DISPALY

#define line_max 21

#define FONT_BOLD_SIZE_15 &Font_Han_Mono_Bold_15
#define FONT_BOLD_SIZE_16 &Font_Han_Mono_Bold_16
#define FONT_BOLD_SIZE_17 &Font_Han_Mono_Bold_17
#define FONT_BOLD_SIZE_18 &Font_Han_Mono_Bold_18
#define FONT_BOLD_SIZE_19 &Font_Han_Mono_Bold_19

#define FONT_BOLD_MONO_SIZE_15 &Font_Mono_Bold_15
#define FONT_BOLD_MONO_SIZE_16 &Font_Mono_Bold_16
#define FONT_BOLD_MONO_SIZE_17 &Font_Mono_Bold_17
#define FONT_BOLD_MONO_SIZE_18 &Font_Mono_Bold_18
#define FONT_BOLD_MONO_SIZE_19 &Font_Mono_Bold_19

ui_indev_read_cb ui_get_gesture_dir = NULL;
lv_timer_t *touch_chk_timer = NULL;
static lv_obj_t *label_list[10] = {0};

//************************************[ Other fun ]******************************************
#if 1
static void scr_label_line_algin(lv_obj_t *label, int line_len, const char *str1, const char *str2)
{
    int w2 = strlen(str2);
    int w1 = line_len - w2;
    lv_label_set_text_fmt(label, "%-*s%-*s", w1, str1, w2, str2);
}

static lv_obj_t *scr_back_btn_create(lv_obj_t *parent, const char *text, lv_event_cb_t cb)
{
    lv_obj_t * btn = lv_btn_create(parent);
    lv_obj_remove_style_all(btn);
    lv_obj_set_style_pad_all(btn, 0, 0);
    lv_obj_set_height(btn, 30);
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(btn, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label2 = lv_label_create(btn);
    lv_obj_align(label2, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_color(label2, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_label_set_text(label2, " "LV_SYMBOL_LEFT );

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_align_to(label, label2, LV_ALIGN_OUT_RIGHT_MID, 5, -1);
    lv_obj_set_style_text_font(label, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_label_set_text(label, text);
    lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(label, cb, LV_EVENT_CLICKED, NULL);
    return label;
}

#endif
//************************************[ screen 0 ]****************************************** menu
#if 1
#define MENU_BTN_NUM (sizeof(menu_btn_list) / sizeof(menu_btn_list[0]))

static lv_obj_t *menu_screen1;
static lv_obj_t *menu_screen2;
static lv_obj_t *ui_Panel4;

static int page_num = 0;
static int page_curr = 0;

static struct menu_btn menu_btn_list[] = 
{
    {SCREEN1_ID,  "A:/img_lora.png",    "Lora",     23,     23},
    {SCREEN2_ID,  "A:/img_setting.png", "Setting",  95,     23},
    {SCREEN3_ID,  "A:/img_GPS.png",     "GPS",      167,    23},
    {SCREEN4_ID,  "A:/img_SD.png",      "SD",       23,     111},
    {SCREEN5_ID,  "A:/img_test.png",    "Test",     95,     111},
    {SCREEN6_ID,  "A:/img_batt.png",    "Battery",  167,    111},
    {SCREEN7_ID,  "A:/img_lora.png", "Lora6", 23, 199},
    {SCREEN8_ID,  "A:/img_lora.png", "Lora7", 95, 199},
    {SCREEN9_ID,  "A:/img_lora.png", "Lora8", 167, 199},
    {SCREEN10_ID, "A:/img_GPS.png", "Lora9", 23, 23},     // Page two
};

static void menu_btn_event_cb(lv_event_t *e)
{
    struct menu_btn *tgr = (struct menu_btn *)e->user_data;
    scr_mgr_push(tgr->idx, false);
}

static void menu_get_gesture_dir(int dir)
{
    if(MENU_BTN_NUM <= 9) return;

    if(dir == LV_DIR_LEFT) {
        if(page_curr < page_num){
            page_curr++;
            // ui_disp_full_refr();
        }
        else{
            return ;
        }
    } else if(dir == LV_DIR_RIGHT) {
        if(page_curr > 0){
            page_curr--;
        }
        else{
            return ;
        }
    }   

    if(page_curr == 1) {
        lv_obj_clear_flag(menu_screen2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(menu_screen1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(lv_obj_get_child(ui_Panel4, 0), lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(lv_obj_get_child(ui_Panel4, 1), lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    } else if(page_curr == 0) {
        lv_obj_clear_flag(menu_screen1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(menu_screen2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(lv_obj_get_child(ui_Panel4, 0), lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(lv_obj_get_child(ui_Panel4, 1), lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

static void menu_btn_create(lv_obj_t *parent, struct menu_btn *info)
{
    lv_obj_t * btn = lv_btn_create(parent);
    lv_obj_remove_style_all(btn);
    lv_obj_set_width(btn, 50);
    lv_obj_set_height(btn, 50);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(btn, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(btn, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(btn, 3, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_t *label = lv_label_create(btn);
    lv_obj_set_style_text_font(label, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_set_width(label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(label, 0);
    lv_obj_set_y(label, 20);
    lv_obj_set_align(label, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_text_color(label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_x(btn, info->pos_x);
    lv_obj_set_y(btn, info->pos_y);
    lv_obj_set_style_bg_img_src(btn, info->icon, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(label, _(info->name));
    lv_obj_set_style_border_width(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn, menu_btn_event_cb, LV_EVENT_CLICKED, (void *)info);
}

static void create0(lv_obj_t *parent) 
{
    page_num = MENU_BTN_NUM / 9;

    menu_screen1 = lv_obj_create(parent);
    lv_obj_set_size(menu_screen1, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(menu_screen1, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(menu_screen1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(menu_screen1, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(menu_screen1, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_pad_all(menu_screen1, 0, LV_PART_MAIN);
    // lv_obj_add_flag(menu_screen1, LV_OBJ_FLAG_HIDDEN);

    menu_screen2 = lv_obj_create(parent);
    lv_obj_set_size(menu_screen2, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(menu_screen2, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(menu_screen2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(menu_screen2, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(menu_screen2, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_pad_all(menu_screen2, 0, LV_PART_MAIN);
    lv_obj_add_flag(menu_screen2, LV_OBJ_FLAG_HIDDEN);

    for(int i = 0; i < MENU_BTN_NUM; i++) {
        if(i < 9) {
            menu_btn_create(menu_screen1, &menu_btn_list[i]);
        } else {
            menu_btn_create(menu_screen2, &menu_btn_list[i]);
        }
    }

    if(MENU_BTN_NUM > 9) {
        ui_Panel4 = lv_obj_create(parent);
        lv_obj_set_width(ui_Panel4, 240);
        lv_obj_set_height(ui_Panel4, 35);
        lv_obj_set_align(ui_Panel4, LV_ALIGN_BOTTOM_MID);
        lv_obj_set_flex_flow(ui_Panel4, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(ui_Panel4, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
        lv_obj_set_style_radius(ui_Panel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_Panel4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_Panel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Panel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_Panel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_Panel4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Panel4, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui_Panel4, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_spread(ui_Panel4, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

        lv_obj_t *ui_Button11 = lv_btn_create(ui_Panel4);
        lv_obj_set_width(ui_Button11, 10);
        lv_obj_set_height(ui_Button11, 10);
        lv_obj_add_flag(ui_Button11, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
        lv_obj_clear_flag(ui_Button11, LV_OBJ_FLAG_CHECKABLE);      /// Flags
        lv_obj_set_style_radius(ui_Button11, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Button11, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui_Button11, DECKPRO_COLOR_FG, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_t *ui_Button12 = lv_btn_create(ui_Panel4);
        lv_obj_set_width(ui_Button12, 10);
        lv_obj_set_height(ui_Button12, 10);
        lv_obj_add_flag(ui_Button12, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
        lv_obj_clear_flag(ui_Button12, LV_OBJ_FLAG_CHECKABLE);      /// Flags
        lv_obj_set_style_radius(ui_Button12, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui_Button12, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

}

static void entry0(void) {
    ui_get_gesture_dir = menu_get_gesture_dir;
    lv_timer_resume(touch_chk_timer);
}
static void exit0(void) {
    ui_get_gesture_dir = NULL;
    lv_timer_pause(touch_chk_timer);
}
static void destroy0(void) { }

static scr_lifecycle_t screen0 = {
    .create = create0,
    .entry = entry0,
    .exit  = exit0,
    .destroy = destroy0,
};
#endif
//************************************[ screen 1 ]****************************************** lora
#if 1
static void scr1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

static void create1(lv_obj_t *parent) {
    
    /*Create a keyboard to use it with an of the text areas*/
    lv_obj_t * kb = lv_keyboard_create(parent);

    /*Create a text area. The keyboard will write here*/
    lv_obj_t * ta;
    ta = lv_textarea_create(parent);
    lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, 40);
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_textarea_set_placeholder_text(ta, "Hello");
    lv_obj_set_size(ta, 100, 80);

    ta = lv_textarea_create(parent);
    lv_obj_align(ta, LV_ALIGN_TOP_RIGHT, -10, 40);
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_set_size(ta, 100, 80);

    lv_keyboard_set_textarea(kb, ta);

    // back
    scr_back_btn_create(parent, _("Lora"), scr1_btn_event_cb);
}
static void entry1(void) {ui_disp_full_refr();}
static void exit1(void) {ui_disp_full_refr();}
static void destroy1(void) { }

static scr_lifecycle_t screen1 = {
    .create = create1,
    .entry = entry1,
    .exit  = exit1,
    .destroy = destroy1,
};
#endif
//************************************[ screen 2 ]****************************************** setting
#if 1
static lv_obj_t *setting_list;
static lv_obj_t *language_label;
static lv_obj_t *backlight_label;
static lv_obj_t *motor_label;
static lv_obj_t *setting1;
static lv_obj_t *setting2;
static lv_obj_t *setting3;
static lv_obj_t *setting5;
static lv_obj_t *back2_label;

static void layout2(void);

static void scr2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void setting_scr_event(lv_event_t *e)
{
    lv_obj_t *tgt = (lv_obj_t *)e->target;
    int data = (int)e->user_data;

    if(e->code == LV_EVENT_CLICKED) {
        switch (data)
        {
        case 0: { // "Keypad Backlight"
            ui_setting_set_keypad_light(!ui_setting_get_keypad_light());
            layout2();
            } break;
        case 1: { // "Motor Status"
            ui_setting_set_motor_status(!ui_setting_get_motor_status());
            layout2();
            } break;
        case 2:  // "Language"
            if(ui_setting_get_language() == DEFAULT_LANGUAGE_EN) {
                lv_i18n_set_locale("zh-cn");
                ui_setting_set_language(DEFAULT_LANGUAGE_CN);
            }else if(ui_setting_get_language() == DEFAULT_LANGUAGE_CN) {
                lv_i18n_set_locale("en-us");
                ui_setting_set_language(DEFAULT_LANGUAGE_EN);
            } 
            layout2();
            break;
        case 3: { // "System Sound"

            } break;
        case 4: { // "About System"
            
            } break;
        default:
            break;
        }
    }
}

static void layout2(void)
{
    lv_label_set_text(lv_obj_get_child(setting1, 0), _("Keypad Backlight"));
    lv_label_set_text(lv_obj_get_child(setting2, 0), _("Motor Status"));
    lv_label_set_text(lv_obj_get_child(setting3, 0), _("Language"));
    lv_label_set_text(lv_obj_get_child(setting5, 0), _("About System"));

    switch (ui_setting_get_language()) {
        case DEFAULT_LANGUAGE_EN: lv_label_set_text(language_label, _("English")); break;
        case DEFAULT_LANGUAGE_CN: lv_label_set_text(language_label, _("Chinese")); break;
        default:
            break;
    }

    if(ui_setting_get_keypad_light()) {
        lv_label_set_text(backlight_label, _("ON"));
    } else {
        lv_label_set_text(backlight_label, _("OFF"));
    }

    if(ui_setting_get_motor_status()) {
        lv_label_set_text(motor_label, _("ON"));
    } else {
        lv_label_set_text(motor_label, _("OFF"));
    }

    lv_label_set_text(back2_label, _("Setting"));
}

static void create2(lv_obj_t *parent) 
{
    setting_list = lv_list_create(parent);
    lv_obj_set_size(setting_list, LV_HOR_RES, LV_VER_RES - 40);
    lv_obj_align(setting_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(setting_list, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_style_pad_top(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_row(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(setting_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(setting_list, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(setting_list, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(setting_list, 0, LV_PART_MAIN);

    setting1 = lv_list_add_btn(setting_list, NULL, "---");
    setting2 = lv_list_add_btn(setting_list, NULL, "---");
    setting3 = lv_list_add_btn(setting_list, NULL, "---");
    setting5 = lv_list_add_btn(setting_list, NULL, "---");

    for(int i = 0; i < lv_obj_get_child_cnt(setting_list); i++) {
        lv_obj_t *item = lv_obj_get_child(setting_list, i);
        lv_obj_set_style_text_font(item, FONT_BOLD_SIZE_15, LV_PART_MAIN);
        lv_obj_set_style_bg_color(item, DECKPRO_COLOR_BG, LV_PART_MAIN);
        lv_obj_set_style_text_color(item, DECKPRO_COLOR_FG, LV_PART_MAIN);
        lv_obj_set_style_border_width(item, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(item, 1, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_outline_width(item, 2, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_add_event_cb(item, setting_scr_event, LV_EVENT_CLICKED, (void *)i);
    }

    
    
    // setting1
    backlight_label = lv_label_create(setting1);
    lv_obj_set_style_text_font(backlight_label, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_align(backlight_label, LV_ALIGN_RIGHT_MID, 0, 0);
    // setting2
    motor_label = lv_label_create(setting2);
    lv_obj_set_style_text_font(motor_label, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_align(motor_label, LV_ALIGN_RIGHT_MID, 0, 0);
    // setting3
    language_label = lv_label_create(setting3);
    lv_obj_set_style_text_font(language_label, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_align(language_label, LV_ALIGN_RIGHT_MID, 0, 0);

    back2_label = scr_back_btn_create(parent, _("Setting"), scr2_btn_event_cb);
}
static void entry2(void) {
    layout2();
}
static void exit2(void) { }
static void destroy2(void) { }

static scr_lifecycle_t screen2 = {
    .create = create2,
    .entry = entry2,
    .exit  = exit2,
    .destroy = destroy2,
};
#endif
//************************************[ screen 3 ]****************************************** GPS
#if 1
static lv_obj_t *scr3_cont;
static lv_timer_t *GPS_loop_timer = NULL;

static lv_obj_t * scr3_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, lv_pct(90));
    lv_obj_set_style_text_font(label, FONT_BOLD_MONO_SIZE_16, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    return label;
}

static void scr3_GPS_updata(void)
{
    float lat      = 0; // Latitude
    float lon      = 0; // Longitude
    float speed    = 0; // Speed over ground
    float alt      = 0; // Altitude
    float accuracy = 0; // Accuracy
    int   vsat     = 0; // Visible Satellites
    int   usat     = 0; // Used Satellites
    int   year     = 0; // 
    int   month    = 0; // 
    int   day      = 0; // 
    int   hour     = 0; // 
    int   min      = 0; // 
    int   sec      = 0; // 

    char buf[16];

    ui_GPS_get_info(&lat, &lon, &speed, &alt, &accuracy, &vsat, &usat, &year, &month, &day, &hour, &min, &sec);

    lv_snprintf(buf, line_max, "%0.1f", lat);
    scr_label_line_algin(label_list[0], line_max, "lat:", buf);

    lv_snprintf(buf, 16, "%0.1f", lon);
    scr_label_line_algin(label_list[1], line_max, "lon:", buf);

    lv_snprintf(buf, 16, "%0.1f", speed);
    scr_label_line_algin(label_list[2], line_max, "speed:", buf);

    lv_snprintf(buf, 16, "%0.1f", alt);
    scr_label_line_algin(label_list[3], line_max, "alt:", buf);

    lv_snprintf(buf, 16, "%d", vsat);
    scr_label_line_algin(label_list[4], line_max, "vsat:", buf);

    lv_snprintf(buf, 16, "%d", usat);
    scr_label_line_algin(label_list[5], line_max, "usat:", buf);

    lv_snprintf(buf, 16, "%d", year);
    scr_label_line_algin(label_list[6], line_max, "year:", buf);

    lv_snprintf(buf, 16, "%d", month);
    scr_label_line_algin(label_list[7], line_max, "month:", buf);

    lv_snprintf(buf, 16, "%d", day);
    scr_label_line_algin(label_list[8], line_max, "day:", buf);

    lv_snprintf(buf, 16, "%02d:%02d:%02d", hour, min, sec);
    scr_label_line_algin(label_list[9], line_max, "time:", buf);
}

static void GPS_loop_timer_event(lv_timer_t * t)
{
    ui_GPS_print_info();
    scr3_GPS_updata();
}

static void scr3_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void create3(lv_obj_t *parent) 
{   
    scr3_cont = lv_obj_create(parent);
    lv_obj_set_size(scr3_cont, lv_pct(100), lv_pct(90));
    lv_obj_set_style_bg_color(scr3_cont, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr3_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr3_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(scr3_cont, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_align(scr3_cont, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_flex_flow(scr3_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(scr3_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    for(int i = 0; i < sizeof(label_list) / sizeof(label_list[0]); i++) {
        label_list[i] = scr3_create_label(scr3_cont);
    }

    lv_obj_t *back3_label = scr_back_btn_create(parent, _("GPS"), scr3_btn_event_cb);
}
static void entry3(void) 
{
    scr3_GPS_updata();

    GPS_loop_timer = lv_timer_create(GPS_loop_timer_event, 5000, NULL);
    ui_disp_full_refr();
}
static void exit3(void) {
    if(GPS_loop_timer) {
        lv_timer_del(GPS_loop_timer);
        GPS_loop_timer = NULL;
    }
    ui_disp_full_refr();
}
static void destroy3(void) { }

static scr_lifecycle_t screen3 = {
    .create = create3,
    .entry = entry3,
    .exit  = exit3,
    .destroy = destroy3,
};
#endif
//************************************[ screen 4 ]****************************************** SD
#if 1
static void scr4_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}
static void create4(lv_obj_t *parent) 
{
    scr3_cont = lv_obj_create(parent);
    lv_obj_set_size(scr3_cont, lv_pct(100), lv_pct(90));
    lv_obj_set_style_bg_color(scr3_cont, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr3_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr3_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(scr3_cont, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_align(scr3_cont, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_flex_flow(scr3_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(scr3_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    lv_obj_t *back4_label = scr_back_btn_create(parent, _("Battery"), scr4_btn_event_cb);
}
static void entry4(void) 
{
    ui_disp_full_refr();
}
static void exit4(void) {
    ui_disp_full_refr();
}
static void destroy4(void) { }

static scr_lifecycle_t screen4 = {
    .create = create4,
    .entry = entry4,
    .exit  = exit4,
    .destroy = destroy4,
};
#endif
//************************************[ screen 5 ]****************************************** Test
#if 1
static void scr5_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}
static void create5(lv_obj_t *parent) 
{
    
    lv_obj_t *back5_label = scr_back_btn_create(parent, _("555"), scr5_btn_event_cb);
}
static void entry5(void) 
{
    ui_disp_full_refr();
}
static void exit5(void) {
    ui_disp_full_refr();
}
static void destroy5(void) { }

static scr_lifecycle_t screen5 = {
    .create = create5,
    .entry = entry5,
    .exit  = exit5,
    .destroy = destroy5,
};
#endif
//************************************[ screen 6 ]****************************************** Battery
#if 1
static lv_obj_t * scr6_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, lv_pct(90));
    lv_obj_set_style_text_font(label, FONT_BOLD_SIZE_15, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    return label;
}

static void scr6_battert_updata(void)
{
    char buf[line_max];
    /// BQ25896
    scr_label_line_algin(label_list[0], line_max, "Charge:", (ui_batt_25896_is_chg() == true ? "Charging" : "Not charged"));

    lv_snprintf(buf, line_max, "%.2fV", ui_batt_25896_get_vbus());
    scr_label_line_algin(label_list[1], line_max, "VBUS:", buf);

    lv_snprintf(buf, line_max, "%.2fV", ui_batt_25896_get_vsys());
    scr_label_line_algin(label_list[2], line_max, "VSYS:", buf);

    lv_snprintf(buf, line_max, "%.2fV", ui_batt_25896_get_vbat());
    scr_label_line_algin(label_list[3], line_max, "VBAT:", buf);

    lv_snprintf(buf, line_max, "%.2fv", ui_batt_25896_get_volt_targ());
    scr_label_line_algin(label_list[4], line_max, "VOLT Target:", buf);

    lv_snprintf(buf, line_max, "%.2fmA", ui_batt_25896_get_chg_curr());
    scr_label_line_algin(label_list[5], line_max, "Charge Curr:", buf);

    lv_snprintf(buf, line_max, "%.2fmA", ui_batt_25896_get_pre_curr());
    scr_label_line_algin(label_list[6], line_max, "Precharge Curr:", buf);

    lv_snprintf(buf, line_max, "%s", ui_batt_25896_get_chg_st());
    scr_label_line_algin(label_list[7], line_max, "CHG Status:", buf);

    lv_snprintf(buf, line_max, "%s", ui_batt_25896_get_vbus_st());
    scr_label_line_algin(label_list[8], line_max, "VBUS Status:", buf);

    lv_snprintf(buf, line_max, "%s", ui_batt_25896_get_ntc_st());
    scr_label_line_algin(label_list[9], line_max, "NCT:", buf);
}

static void scr6_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}
static void create6(lv_obj_t *parent) 
{
    lv_obj_t *scr6_cont = lv_obj_create(parent);
    lv_obj_set_size(scr6_cont, lv_pct(100), lv_pct(90));
    lv_obj_set_style_bg_color(scr6_cont, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr6_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr6_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr6_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr6_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr6_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(scr6_cont, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr6_cont, 0, LV_PART_MAIN);
    lv_obj_set_align(scr6_cont, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_flex_flow(scr6_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(scr6_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    for(int i = 0; i < sizeof(label_list) / sizeof(label_list[0]); i++) {
        label_list[i] = scr6_create_label(scr6_cont);
    }

    lv_obj_t *back6_label = scr_back_btn_create(parent, _("Battery"), scr6_btn_event_cb);
}
static void entry6(void) 
{
    scr6_battert_updata();
    ui_disp_full_refr();
}
static void exit6(void) {
    ui_disp_full_refr();
}
static void destroy6(void) { }

static scr_lifecycle_t screen6 = {
    .create = create6,
    .entry = entry6,
    .exit  = exit6,
    .destroy = destroy6,
};
#endif
//************************************[ UI ENTRY ]******************************************

extern lv_indev_t* lv_win32_pointer_device_object;
extern lv_indev_t* lv_win32_keypad_device_object; 
extern lv_indev_t* lv_win32_encoder_device_object;

void indev_get_gesture_dir(lv_timer_t *t)
{
    lv_indev_data_t data;
    lv_indev_t * indev_pointer = lv_win32_pointer_device_object;
    lv_dir_t dir = lv_indev_get_gesture_dir(indev_pointer);
    static lv_dir_t curr_dir = LV_DIR_NONE;
    static int test_id = 0;

    _lv_indev_read(indev_pointer, &data);

    if(data.state == LV_INDEV_STATE_PR){
        curr_dir = dir;
    }else{
        switch (curr_dir)
        {
            case LV_DIR_LEFT: 
                if(ui_get_gesture_dir) {
                    ui_get_gesture_dir(LV_DIR_LEFT);
                }
                // printf("scroll left\n");
                break;
            case LV_DIR_RIGHT: 
                if(ui_get_gesture_dir) {
                    ui_get_gesture_dir(LV_DIR_RIGHT);
                }
                // printf("scroll right\n"); 
                break;
            case LV_DIR_TOP:
                // printf("scroll top\n");
                break;
            case LV_DIR_BOTTOM:
                // printf("scroll bottom\n");
                break;
            default:
                break;
        }
        curr_dir = LV_DIR_NONE;
        dir = LV_DIR_NONE;
    }
}

void ui_deckpro_entry(void)
{
    lv_disp_t *disp = lv_disp_get_default();
    disp->theme = lv_theme_mono_init(disp, false, LV_FONT_DEFAULT);

    touch_chk_timer = lv_timer_create(indev_get_gesture_dir, LV_INDEV_DEF_READ_PERIOD, NULL);
    lv_timer_pause(touch_chk_timer);

    // init language
    lv_i18n_init(lv_i18n_language_pack);
    if(ui_setting_get_language() == DEFAULT_LANGUAGE_CN) {
        lv_i18n_set_locale("zh-cn");
    } else {
        lv_i18n_set_locale("en-us");
    }

    scr_mgr_init();

    scr_mgr_register(SCREEN0_ID, &screen0); // menu
    scr_mgr_register(SCREEN1_ID, &screen1); // 
    scr_mgr_register(SCREEN2_ID, &screen2); // 
    scr_mgr_register(SCREEN3_ID, &screen3); // 
    scr_mgr_register(SCREEN4_ID, &screen4); // 
    scr_mgr_register(SCREEN5_ID, &screen5); // 
    scr_mgr_register(SCREEN6_ID, &screen6); // 
    scr_mgr_register(SCREEN7_ID, &screen1); // 
    scr_mgr_register(SCREEN8_ID, &screen1); // 
    scr_mgr_register(SCREEN9_ID, &screen1); // 
    scr_mgr_register(SCREEN10_ID, &screen1); // 

    scr_mgr_switch(SCREEN0_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}

#endif /* UI_DECKPRO_DISPALY */

