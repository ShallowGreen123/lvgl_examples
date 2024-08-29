﻿
#include "ui_deckpro.h"
#include "ui_deckpro_port.h"

#if UI_DECKPRO_DISPALY

#define line_max 21
#define GET_BUFF_LEN(a) sizeof(a)/sizeof(a[0])

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

static lv_timer_t *touch_chk_timer = NULL;
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
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 3, 3);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(btn, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label2 = lv_label_create(btn);
    lv_obj_align(label2, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_color(label2, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_label_set_text(label2, LV_SYMBOL_LEFT);

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_align_to(label, label2, LV_ALIGN_OUT_RIGHT_MID, 5, -1);
    lv_obj_set_style_text_font(label, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_label_set_text(label, text);
    lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(label, cb, LV_EVENT_CLICKED, NULL);
    lv_obj_set_ext_click_area(label, 20);

    return label;
}

#endif
//************************************[ screen 0 ]****************************************** menu
#if 1
#define MENU_BTN_NUM (sizeof(menu_btn_list) / sizeof(menu_btn_list[0]))

static ui_indev_read_cb ui_get_gesture_dir = NULL;

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
    lv_label_set_text(label, (info->name));
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
static lv_obj_t *scr1_cont;
static lv_obj_t *lora_lab_buf[11] = {0};
static lv_obj_t *lora_sw_btn;
static lv_obj_t *lora_sw_btn_info;
static lv_timer_t *lora_RT_timer = NULL;
static int lora_cnt = 0;

static void scr1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void lora_mode_sw_event(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        if(ui_lora_get_mode() == LORA_MODE_SEND) {
            ui_lora_set_mode(LORA_MODE_RECV);
            lv_label_set_text(lora_sw_btn_info, "Recv");
            for(int i = 0; i < GET_BUFF_LEN(lora_lab_buf); i++){
                lv_label_set_text_fmt(lora_lab_buf[i], " ", i);
            }
            lora_cnt = 0;
        } else if(ui_lora_get_mode() == LORA_MODE_RECV) {
            ui_lora_set_mode(LORA_MODE_SEND);
            lv_label_set_text(lora_sw_btn_info, "Send");
            for(int i = 0; i < GET_BUFF_LEN(lora_lab_buf); i++){
                lv_label_set_text_fmt(lora_lab_buf[i], " ", i);
            }
            lora_cnt = 0;
        }
    }
}

static void lora_RT_timer_event(lv_timer_t *t)
{
    static int data = 0;
    char buf[32];
    char *recv_info = NULL;
    int recv_rssi = 0;

    if(ui_lora_get_mode() == LORA_MODE_SEND) 
    {
        lv_snprintf(buf, 32, "DeckPro #%d", data++);
        lv_label_set_text_fmt(lora_lab_buf[lora_cnt], "send-> %s", buf);
        ui_lora_send(buf);

        lora_cnt++;
        if(lora_cnt >= GET_BUFF_LEN(lora_lab_buf)) {
            lora_cnt = 0;
        }
    }
    else if(ui_lora_get_mode() == LORA_MODE_RECV)
    {
        if(ui_lora_get_recv(&recv_info, &recv_rssi))
        {
            ui_lora_set_recv_flag();
            lv_label_set_text_fmt(lora_lab_buf[lora_cnt], "recv-> %s [%d]", recv_info, recv_rssi);

            lora_cnt++;
            if(lora_cnt >= GET_BUFF_LEN(lora_lab_buf)) {
                lora_cnt = 0;
            }
        }
    }
}

static lv_obj_t * scr2_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, LV_HOR_RES - 26);
    lv_obj_set_style_text_font(label, FONT_BOLD_SIZE_15, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 0, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
    return label;
}

static void create1(lv_obj_t *parent) 
{
    scr1_cont = lv_obj_create(parent);
    lv_obj_set_size(scr1_cont, lv_pct(100), lv_pct(85));
    lv_obj_set_style_bg_color(scr1_cont, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr1_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr1_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr1_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr1_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(scr1_cont, 13, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr1_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(scr1_cont, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr1_cont, 5, LV_PART_MAIN);
    lv_obj_set_align(scr1_cont, LV_ALIGN_BOTTOM_MID);

    for(int i = 0; i < GET_BUFF_LEN(lora_lab_buf); i++){
        lora_lab_buf[i] = scr2_create_label(scr1_cont);
        lv_label_set_text_fmt(lora_lab_buf[i], " ", i);
    }

    lora_sw_btn = lv_btn_create(parent);
    lv_obj_set_size(lora_sw_btn, 70, 25);
    lv_obj_set_style_radius(lora_sw_btn, 5, LV_PART_MAIN);
    lv_obj_set_style_border_width(lora_sw_btn, 2, LV_PART_MAIN);
    lora_sw_btn_info = lv_label_create(lora_sw_btn);
    lv_obj_set_style_text_font(lora_sw_btn_info, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_set_style_text_align(lora_sw_btn_info, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(lora_sw_btn_info, "Send");
    lv_obj_center(lora_sw_btn_info);
    lv_obj_align(lora_sw_btn, LV_ALIGN_TOP_MID, 0, 5);
    lv_obj_add_event_cb(lora_sw_btn, lora_mode_sw_event, LV_EVENT_CLICKED, NULL);

    lv_obj_t *lab = lv_label_create(parent);
    lv_obj_set_style_text_font(lab, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_label_set_text_fmt(lab, "%.1fM", ui_lora_get_freq());
    lv_obj_align(lab, LV_ALIGN_TOP_RIGHT, -10, 10);

    // back
    scr_back_btn_create(parent, ("Lora"), scr1_btn_event_cb);
}

static void entry1(void) 
{
    ui_disp_full_refr();
    lora_RT_timer = lv_timer_create(lora_RT_timer_event, 1000, NULL);
}
static void exit1(void) {
    ui_disp_full_refr();
    if(lora_RT_timer) {
        lv_timer_del(lora_RT_timer);
        lora_RT_timer = NULL;
    }
}
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

static int setting_num = 0;
static _ui_setting_handle setting_handle_list[] = {
    {"Keypad Backlight",    NULL, NULL, ui_setting_set_keypad_light, ui_setting_get_keypad_light},
    {"Motor Status",        NULL, NULL, ui_setting_set_motor_status, ui_setting_get_motor_status},
    {"Power GPS",           NULL, NULL, ui_setting_set_gps_status, ui_setting_get_gps_status},
    {"Power Lora",          NULL, NULL, ui_setting_set_lora_status, ui_setting_get_lora_status},
    {"Power Gyro",          NULL, NULL, ui_setting_set_gyro_status, ui_setting_get_gyro_status},
    {"Power A7682",         NULL, NULL, ui_setting_set_a7682_status, ui_setting_get_a7682_status},
};

static void scr2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void setting_scr_event(lv_event_t *e)
{
    lv_obj_t *tgt = (lv_obj_t *)e->target;
    _ui_setting_handle *h = (_ui_setting_handle *)e->user_data;

    if(e->code == LV_EVENT_CLICKED) {
        h->set_cb(!h->get_cb());
        lv_label_set_text_fmt(h->st, "%s", (h->get_cb() ? "ON" : "OFF"));
    }
}

static void create2(lv_obj_t *parent) 
{
    lv_obj_t * setting_list = lv_list_create(parent);
    lv_obj_set_size(setting_list, LV_HOR_RES, lv_pct(88));
    lv_obj_align(setting_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(setting_list, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_style_pad_top(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_row(setting_list, 3, LV_PART_MAIN);
    lv_obj_set_style_radius(setting_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(setting_list, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(setting_list, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(setting_list, 0, LV_PART_MAIN);

    setting_num = sizeof(setting_handle_list) / sizeof(setting_handle_list[0]);

    for(int i = 0; i < setting_num; i++) {
        _ui_setting_handle *h = &setting_handle_list[i];
        h->obj = lv_list_add_btn(setting_list, NULL, h->name);
        h->st = lv_label_create(h->obj);
        lv_obj_set_style_text_font(h->st, FONT_BOLD_SIZE_15, LV_PART_MAIN);
        lv_obj_align(h->st, LV_ALIGN_RIGHT_MID, 0, 0);
        lv_label_set_text_fmt(h->st, "%s", (h->get_cb() ? "ON" : "OFF"));
        // style
        lv_obj_set_style_text_font(h->obj, FONT_BOLD_SIZE_15, LV_PART_MAIN);
        lv_obj_set_style_bg_color(h->obj, DECKPRO_COLOR_BG, LV_PART_MAIN);
        lv_obj_set_style_text_color(h->obj, DECKPRO_COLOR_FG, LV_PART_MAIN);
        lv_obj_set_style_border_width(h->obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(h->obj, 1, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_outline_width(h->obj, 3, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_add_event_cb(h->obj, setting_scr_event, LV_EVENT_CLICKED, (void *)h);
    }

    scr_back_btn_create(parent, ("Setting"), scr2_btn_event_cb);
}
static void entry2(void) {
    ui_disp_full_refr();
}
static void exit2(void) {
    ui_disp_full_refr();
}
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

    lv_snprintf(buf, 16, "%0.1f", lat);
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
    lv_obj_set_size(scr3_cont, lv_pct(100), lv_pct(88));
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

    lv_obj_t *back3_label = scr_back_btn_create(parent, ("GPS"), scr3_btn_event_cb);
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
//************************************[ screen 4 ]****************************************** SD card
#if 1
static void scr4_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void create4(lv_obj_t *parent) 
{
    
    lv_obj_t *back4_label = scr_back_btn_create(parent, ("444"), scr4_btn_event_cb);
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
static ui_test_handle test_handle_list[] = {
    {"SD Card", ui_sd_is_vaild},
    {"Lora", ui_lora_is_vaild},
    {"Keypad", ui_keypad_is_vaild},
    {"BQ25896", ui_bq25896_is_vaild},
    {"BQ27220", ui_bq27220_is_vaild},
    {"LTR553ALS", ui_ltr553_is_vaild},
};

static void scr5_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}
static void create5(lv_obj_t *parent) 
{
    lv_obj_t *test_list = lv_list_create(parent);
    lv_obj_set_size(test_list, LV_HOR_RES, lv_pct(88));
    lv_obj_align(test_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(test_list, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_style_pad_top(test_list, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_row(test_list, 3, LV_PART_MAIN);
    lv_obj_set_style_radius(test_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(test_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(test_list, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(test_list, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(test_list, 0, LV_PART_MAIN);

    for(int i = 0; i < sizeof(test_handle_list) / sizeof(test_handle_list[0]); i++) {
        lv_obj_t *item = lv_list_add_btn(test_list, NULL, test_handle_list[i].name);
        lv_obj_t *label = lv_label_create(item);
        lv_obj_set_style_text_font(label, FONT_BOLD_MONO_SIZE_16, LV_PART_MAIN);
        lv_obj_align(label, LV_ALIGN_RIGHT_MID, 0, 0);
        lv_label_set_text_fmt(label, "%s", (test_handle_list[i].cb() ? "PASS" : "FAIL"));
    }

    for(int i = 0; i < lv_obj_get_child_cnt(test_list); i++) {
        lv_obj_t *item = lv_obj_get_child(test_list, i);
        lv_obj_set_style_text_font(item, FONT_BOLD_MONO_SIZE_16, LV_PART_MAIN);
        lv_obj_set_style_bg_color(item, DECKPRO_COLOR_BG, LV_PART_MAIN);
        lv_obj_set_style_text_color(item, DECKPRO_COLOR_FG, LV_PART_MAIN);
        lv_obj_set_style_border_width(item, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(item, 1, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_outline_width(item, 3, LV_PART_MAIN | LV_STATE_PRESSED);
    }

    lv_obj_t *back5_label = scr_back_btn_create(parent, ("Test"), scr5_btn_event_cb);
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
static lv_obj_t *back6_label;
static bool show_batt_type = true;
static lv_timer_t *batt_updata_timer = NULL;

static lv_obj_t * scr6_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, lv_pct(90));
    lv_obj_set_style_text_font(label, FONT_BOLD_MONO_SIZE_16, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    return label;
}

static void scr6_battert_updata(void)
{
    char buf[line_max];
    if(show_batt_type) {
        /// BQ25896
        lv_label_set_text(back6_label, "BQ25896");

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
        scr_label_line_algin(label_list[6], line_max, "Prechg Curr:", buf);

        lv_snprintf(buf, line_max, "%s", ui_batt_25896_get_chg_st());
        scr_label_line_algin(label_list[7], line_max, "CHG Status:", buf);

        lv_snprintf(buf, line_max, "%s", ui_batt_25896_get_vbus_st());
        scr_label_line_algin(label_list[8], line_max, "VBUS Status:", buf);

        lv_snprintf(buf, line_max, "%s", ui_batt_25896_get_ntc_st());
        scr_label_line_algin(label_list[9], line_max, "NCT:", buf);
    } else {
        /// BQ27220
        lv_label_set_text(back6_label, "BQ27220");
    }
}

static void batt_updata_timer_event(lv_timer_t *t) 
{
    scr6_battert_updata();
}

static void scr6_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

void batt_trans_event_cb(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED) {
        show_batt_type = !show_batt_type;
        // scr6_battert_updata();
    }
}

static void create6(lv_obj_t *parent) 
{
    lv_obj_t *scr6_cont = lv_obj_create(parent);
    lv_obj_set_size(scr6_cont, lv_pct(100), lv_pct(88));
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

    lv_obj_t *batt_trans = lv_btn_create(parent);
    // lv_group_add_obj(lv_group_get_default(), btn);
    lv_obj_set_style_pad_all(batt_trans, 0, 0);
    lv_obj_set_height(batt_trans, 20);
    lv_obj_align(batt_trans, LV_ALIGN_TOP_RIGHT, -8, 8);
    lv_obj_set_style_radius(batt_trans, 5, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(batt_trans, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(batt_trans, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(batt_trans, 1, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(batt_trans, 2, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_event_cb(batt_trans, batt_trans_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label2 = lv_label_create(batt_trans);
    lv_obj_align(label2, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_font(label2, FONT_BOLD_MONO_SIZE_16, LV_PART_MAIN);   
    lv_label_set_text(label2, " Switch ");

    back6_label = scr_back_btn_create(parent, ("BQ25896"), scr6_btn_event_cb);
}
static void entry6(void) 
{
    scr6_battert_updata();
    ui_disp_full_refr();
    batt_updata_timer = lv_timer_create(batt_updata_timer_event, 5000, NULL);
}
static void exit6(void) {
    if(batt_updata_timer) {
        lv_timer_del(batt_updata_timer);
        batt_updata_timer = NULL;
    }
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
//************************************[ screen 7 ]******************************************  
#if 1
static void scr7_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void create7(lv_obj_t *parent) 
{
    
    lv_obj_t *back7_label = scr_back_btn_create(parent, ("777"), scr7_btn_event_cb);
}
static void entry7(void) 
{
    ui_disp_full_refr();
}
static void exit7(void) {
    ui_disp_full_refr();
}
static void destroy7(void) { }

static scr_lifecycle_t screen7 = {
    .create = create7,
    .entry = entry7,
    .exit  = exit7,
    .destroy = destroy7,
};
#endif
//************************************[ screen 8 ]******************************************  
#if 1
static void scr8_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void create8(lv_obj_t *parent) 
{
    
    lv_obj_t *back8_label = scr_back_btn_create(parent, ("888"), scr8_btn_event_cb);
}
static void entry8(void) 
{
    ui_disp_full_refr();
}
static void exit8(void) {
    ui_disp_full_refr();
}
static void destroy8(void) { }

static scr_lifecycle_t screen8 = {
    .create = create8,
    .entry = entry8,
    .exit  = exit8,
    .destroy = destroy8,
};
#endif
//************************************[ screen 9 ]******************************************  
#if 1
static void scr9_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void create9(lv_obj_t *parent) 
{
    
    lv_obj_t *back9_label = scr_back_btn_create(parent, ("999"), scr9_btn_event_cb);
}
static void entry9(void) 
{
    ui_disp_full_refr();
}
static void exit9(void) {
    ui_disp_full_refr();
}
static void destroy9(void) { }

static scr_lifecycle_t screen9 = {
    .create = create9,
    .entry = entry9,
    .exit  = exit9,
    .destroy = destroy9,
};
#endif
//************************************[ screen 10 ]******************************************  
#if 1
static void scr10_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void create10(lv_obj_t *parent) 
{
    
    lv_obj_t *back10_label = scr_back_btn_create(parent, ("101010"), scr10_btn_event_cb);
}
static void entry10(void) 
{
    ui_disp_full_refr();
}
static void exit10(void) {
    ui_disp_full_refr();
}
static void destroy10(void) { }

static scr_lifecycle_t screen10 = {
    .create = create10,
    .entry = entry10,
    .exit  = exit10,
    .destroy = destroy10,
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
    // lv_i18n_init(lv_i18n_language_pack);
    // if(ui_setting_get_language() == DEFAULT_LANGUAGE_CN) {
    //     lv_i18n_set_locale("zh-cn");
    // } else {
    //     lv_i18n_set_locale("en-us");
    // }

    scr_mgr_init();

    scr_mgr_register(SCREEN0_ID, &screen0); // menu
    scr_mgr_register(SCREEN1_ID, &screen1); // 
    scr_mgr_register(SCREEN2_ID, &screen2); // 
    scr_mgr_register(SCREEN3_ID, &screen3); // 
    scr_mgr_register(SCREEN4_ID, &screen4); // 
    scr_mgr_register(SCREEN5_ID, &screen5); // 
    scr_mgr_register(SCREEN6_ID, &screen6); // 
    scr_mgr_register(SCREEN7_ID, &screen7); // 
    scr_mgr_register(SCREEN8_ID, &screen8); // 
    scr_mgr_register(SCREEN9_ID, &screen9); // 
    scr_mgr_register(SCREEN10_ID, &screen10); // 

    scr_mgr_switch(SCREEN0_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}

#endif /* UI_DECKPRO_DISPALY */

