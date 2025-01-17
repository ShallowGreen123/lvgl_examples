﻿

#include "ui_epd47.h"
#include "ui_epd47_port.h"

/* clang-format off */
#define SETTING_PAGE_MAX_ITEM 7
#if UI_EPD47_DISPALY 1

#define UI_PORTRAIT_SCR_MODE    1
#define UI_LORA_AUTO_SEND       0

#define ARRAY_LEN(a) (sizeof(a)/sizeof(a[0]))
//************************************[ Other fun ]******************************************
#if 1
static void scr_back_btn_create(lv_obj_t *parent, const char *text, lv_event_cb_t cb)
{
    lv_obj_t * btn = lv_btn_create(parent);
    lv_obj_set_style_pad_all(btn, 0, 0);
    lv_obj_set_height(btn, 50);
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 15, 15);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label2 = lv_label_create(btn);
    lv_obj_align(label2, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_color(label2, lv_color_hex(EPD_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text(label2, " " LV_SYMBOL_LEFT);

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_align_to(label, btn, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_30, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(EPD_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text(label, text);
    lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(label, cb, LV_EVENT_CLICKED, NULL);
}

static void scr_middle_line(lv_obj_t *parent)
{
    static lv_point_t line_points[] = { {LCD_HOR_SIZE/2, 0}, {LCD_HOR_SIZE/2, LCD_VER_SIZE-150}};
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_color_black());
    lv_style_set_line_rounded(&style_line, true);
    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(parent);
    lv_line_set_points(line1, line_points, 2);     /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_set_align(line1, LV_ALIGN_LEFT_MID);
}

/* clang-format on */

/**
 * func:      setting
 * handle:    setting_handle_list
 * list:      scr2_list
 * num:       setting_num
 * page_num:  setting_page_num
 * curr_page: setting_curr_page
 */
#define UI_LIST_CREATE(func, handle, list, num, page_num, curr_page)                       \
    static void func##_scr_event(lv_event_t *e)                                            \
    {                                                                                      \
        lv_obj_t *tgt = (lv_obj_t *)e->target;                                             \
        ui_setting_handle *h = (ui_setting_handle *)e->user_data;                          \
        int n;                                                                             \
        if (e->code == LV_EVENT_CLICKED)                                                   \
        {                                                                                  \
            switch (h->type)                                                               \
            {                                                                              \
            case UI_SETTING_TYPE_SW:                                                       \
                if (h->get_cb != NULL && h->set_cb != NULL)                                \
                {                                                                          \
                    h->get_cb(&n);                                                         \
                    h->set_cb(n);                                                          \
                    lv_label_set_text_fmt(h->st, "%s", h->get_cb(NULL));                   \
                }                                                                          \
                break;                                                                     \
            case UI_SETTING_TYPE_SUB:                                                      \
                printf("id=%d\n", h->sub_id);                                              \
                scr_mgr_push(h->sub_id, false);                                            \
                break;                                                                     \
            default:                                                                       \
                break;                                                                     \
            }                                                                              \
        }                                                                                  \
    }                                                                                      \
    static void func##_item_create(void)                                                   \
    {                                                                                      \
        num = sizeof(handle) / sizeof(handle[0]);                                          \
        page_num = num / SETTING_PAGE_MAX_ITEM;                                            \
        int start = (curr_page * SETTING_PAGE_MAX_ITEM);                                   \
        int end = start + SETTING_PAGE_MAX_ITEM;                                           \
        if (end > num)                                                                     \
            end = num;                                                                     \
        for (int i = start; i < end; i++)                                                  \
        {                                                                                  \
            ui_setting_handle *h = &handle[i];                                             \
                                                                                           \
            h->obj = lv_obj_class_create_obj(&lv_list_btn_class, list);                    \
            lv_obj_class_init_obj(h->obj);                                                 \
            lv_obj_set_size(h->obj, LV_PCT(100), LV_SIZE_CONTENT);                         \
                                                                                           \
            lv_obj_t *label = lv_label_create(h->obj);                                     \
            lv_label_set_text(label, h->name);                                             \
            lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);                  \
            lv_obj_align(label, LV_ALIGN_LEFT_MID, 10, 0);                                 \
                                                                                           \
            lv_obj_set_height(h->obj, 85);                                                 \
            lv_obj_set_style_text_font(h->obj, &Font_Mono_Bold_30, LV_PART_MAIN);          \
            lv_obj_set_style_bg_color(h->obj, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);   \
            lv_obj_set_style_text_color(h->obj, lv_color_hex(EPD_COLOR_FG), LV_PART_MAIN); \
            lv_obj_set_style_border_width(h->obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);     \
            lv_obj_set_style_border_width(h->obj, 3, LV_PART_MAIN | LV_STATE_PRESSED);     \
            lv_obj_set_style_outline_width(h->obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);    \
            lv_obj_set_style_radius(h->obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);          \
            lv_obj_add_event_cb(h->obj, func##_scr_event, LV_EVENT_CLICKED, (void *)h);    \
                                                                                           \
            if (h->get_cb)                                                                 \
            {                                                                              \
                h->st = lv_label_create(h->obj);                                           \
                lv_obj_set_style_text_font(h->st, &Font_Mono_Bold_30, LV_PART_MAIN);       \
                lv_obj_set_style_border_width(h->st, 3, LV_PART_MAIN | LV_STATE_DEFAULT);     \
                lv_obj_align(h->st, LV_ALIGN_RIGHT_MID, -3, 0);                            \
                lv_label_set_text_fmt(h->st, "%s", h->get_cb(NULL));                       \
            }                                                                              \
        }                                                                                  \
    }
/**
 * func:      setting
 * list:      scr2_list
 * page:      setting_page
 * num:       setting_num
 * page_num:  setting_page_num
 * curr_page: setting_curr_page
 */
#define UI_LIST_BTN_CREATE(func, list, page, num, page_num, curr_page) \
    static void func##_page_switch_cb(lv_event_t *e)                   \
    {                                                                  \
        char opt = (int)e->user_data;                                  \
                                                                       \
        if (num < SETTING_PAGE_MAX_ITEM)                               \
            return;                                                    \
                                                                       \
        int child_cnt = lv_obj_get_child_cnt(list);                    \
                                                                       \
        for (int i = 0; i < child_cnt; i++)                            \
        {                                                              \
            lv_obj_t *child = lv_obj_get_child(list, 0);               \
            if (child)                                                 \
                lv_obj_del(child);                                     \
        }                                                              \
                                                                       \
        if (opt == 'p')                                                \
        {                                                              \
            curr_page = (curr_page < page_num) ? curr_page + 1 : 0;    \
        }                                                              \
        else if (opt == 'n')                                           \
        {                                                              \
            curr_page = (curr_page > 0) ? curr_page - 1 : page_num;    \
        }                                                              \
                                                                       \
        func##_item_create();                                          \
        lv_label_set_text_fmt(page, "%d / %d", curr_page, page_num);   \
    }

/* clang-format off */

#endif
//************************************[ screen 0 ]****************************************** menu
#if 1
#define MENU_ICON_NUM  (sizeof(icon_buf)/sizeof(icon_buf[0]))
#define MENU_CONT_HIGH (LCD_VER_SIZE * 0.84)

static int icon_width = 120; // 
static int menu_icon_num = 0;

static lv_obj_t * menu_taskbar = NULL;
static lv_obj_t * menu_taskbar_time = NULL;
static lv_obj_t * menu_taskbar_charge = NULL;
static lv_obj_t * menu_taskbar_battery = NULL;
static lv_obj_t * menu_taskbar_battery_percent = NULL;
static lv_obj_t * menu_taskbar_wifi = NULL;

static lv_obj_t *scr0_cont;
struct menu_icon {
    const void *icon_src;
    const char *icon_str;
    lv_coord_t offs_x;
    lv_coord_t offs_y;
};

#if UI_PORTRAIT_SCR_MODE
// 960 * 540
const struct menu_icon icon_buf[] = {
    {"A:/ver_clock.png",    "clock",    45, 375}, 
    {"A:/ver_lora.png",     "lora",     45, 210},
    {"A:/ver_sd.png",       "sd card",  45, 45},
    {"A:/ver_setting.png",  "setting",  250, 375},
    {"A:/ver_test.png",     "test",     250, 210},
    {"A:/ver_wifi.png",     "wifi",     250, 45},
    {"A:/ver_battery.png",  "battery",  455, 375},
    {"A:/ver_shutdown.png", "shutdown", 455, 210},
};
#else
const struct menu_icon icon_buf[] = {
    {"A:/img_clock.png",    "clock",    0, 0}, 
    {"A:/img_lora.png",     "lora",     0, 0},
    {"A:/img_sd_card.png",  "sd card",  0, 0},
    {"A:/img_setting.png",  "setting",  0, 0},
    {"A:/img_test.png",     "test",     0, 0},
    {"A:/img_wifi.png",     "wifi",     0, 0},
    {"A:/img_battery.png",  "battery",  0, 0},
    {"A:/img_shutdown.png", "shutdown", 0, 0},
};
#endif

static void menu_btn_event(lv_event_t *e)
{
    
    int data = (int)e->user_data;
    if(e->code == LV_EVENT_CLICKED) {
        printf("%s is clicked.\n", icon_buf[data].icon_str);
        switch (data) {
            case 0: scr_mgr_push(SCREEN1_ID, false); break;
            case 1: scr_mgr_push(SCREEN2_ID, false); break;
            case 2: scr_mgr_push(SCREEN3_ID, false); break;
            case 3: scr_mgr_push(SCREEN4_ID, false); break;
            case 4: scr_mgr_push(SCREEN5_ID, false); break;
            case 5: scr_mgr_push(SCREEN6_ID, false); break;
            case 6: scr_mgr_push(SCREEN7_ID, false); break;
            case 7: scr_mgr_push(SCREEN8_ID, false); break;
            default:
                break;
        }
    }
    
}

static void create0(lv_obj_t *parent) 
{
#if UI_PORTRAIT_SCR_MODE  // 如果菜单是竖屏

    int status_bar_height = 60;

    menu_taskbar = lv_obj_create(parent);
    lv_obj_set_size(menu_taskbar, LV_HOR_RES, status_bar_height);
    lv_obj_set_style_pad_all(menu_taskbar, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(menu_taskbar, 1, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(menu_taskbar, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(menu_taskbar, LV_OBJ_FLAG_SCROLLABLE);
    
    menu_taskbar_time = lv_label_create(menu_taskbar);
    lv_obj_set_style_border_width(menu_taskbar_time, 1, 0);
    lv_label_set_text_fmt(menu_taskbar_time, "%02d:%02d", 10, 19);
    lv_obj_set_style_text_font(menu_taskbar_time, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_align(menu_taskbar_time, LV_ALIGN_LEFT_MID, 20, 0);

    lv_obj_t *status_parent = lv_obj_create(menu_taskbar);
    lv_obj_set_size(status_parent, lv_pct(80)-4, status_bar_height -10);
    lv_obj_set_style_pad_all(status_parent, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(status_parent, 1, LV_PART_MAIN);
    lv_obj_set_flex_flow(status_parent, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(status_parent, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_left(status_parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(status_parent, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(status_parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(status_parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(status_parent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(status_parent, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(status_parent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(status_parent, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(status_parent, LV_ALIGN_RIGHT_MID, 0, 0);

    menu_taskbar_wifi = lv_label_create(status_parent);
    lv_label_set_text_fmt(menu_taskbar_wifi, "%s", LV_SYMBOL_WIFI);

    menu_taskbar_charge = lv_label_create(status_parent);
    lv_label_set_text_fmt(menu_taskbar_charge, "%s", LV_SYMBOL_CHARGE);

    menu_taskbar_battery = lv_label_create(status_parent);
    lv_label_set_text_fmt(menu_taskbar_battery, "%s", LV_SYMBOL_BATTERY_2);

    menu_taskbar_battery_percent = lv_label_create(status_parent);
    lv_obj_set_style_text_font(menu_taskbar_battery_percent, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_label_set_text_fmt(menu_taskbar_battery_percent, "%d", 50);

    for(int i = 0; i < sizeof(icon_buf)/sizeof(icon_buf[0]); i++) {

        lv_obj_t *img = lv_img_create(parent);
        lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_x(img, icon_buf[i].offs_x);
        lv_obj_set_y(img, icon_buf[i].offs_y);
        lv_img_set_src(img, icon_buf[i].icon_src);
        lv_obj_add_event_cb(img, menu_btn_event, LV_EVENT_CLICKED, (void *)i);
        lv_obj_set_style_outline_width(img, 1, LV_PART_MAIN );
    }

#else
    lv_obj_t *scr0_cont = lv_obj_create(parent);
    lv_obj_set_size(scr0_cont, lv_pct(100), MENU_CONT_HIGH);
    lv_obj_set_style_bg_color(scr0_cont, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr0_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr0_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(scr0_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr0_cont, 0, LV_PART_MAIN);
    lv_obj_align(scr0_cont, LV_ALIGN_BOTTOM_MID, 0, 0);

    int row_n = 2;
    int col_n = 5;
    lv_obj_t *img_buf[MENU_ICON_NUM] = {0};
    lv_obj_t *lab_buf[MENU_ICON_NUM] = {0};
    
    for(int i = 0; i < MENU_ICON_NUM; i++) {
        lv_obj_t *img = lv_img_create(scr0_cont);
        lv_img_set_src(img, icon_buf[i].icon_src);
        lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(img, menu_btn_event, LV_EVENT_CLICKED, (void *)i);
        lv_obj_t *label = lv_label_create(scr0_cont);
        lv_label_set_text(label, icon_buf[i].icon_str);
        img_buf[i] = img;
        lab_buf[i] = label;
    }

    lv_coord_t x_gap = (LCD_HOR_SIZE-(icon_width * col_n)) / (col_n+1);
    lv_coord_t y_gap = (MENU_CONT_HIGH / 5);

    printf("x=%d, y=%d\n", x_gap, y_gap);

    // row 1
    lv_obj_align_to(img_buf[0], scr0_cont, LV_ALIGN_TOP_LEFT, x_gap, 0);
    for(int i = 1; i < col_n; i++) {
        lv_obj_align_to(img_buf[i], img_buf[i-1], LV_ALIGN_OUT_RIGHT_MID, x_gap, 0);
    }

    if(MENU_ICON_NUM > col_n) {
        // row 2
        lv_obj_align_to(img_buf[col_n], img_buf[0], LV_ALIGN_OUT_BOTTOM_MID, 0, y_gap);
        for(int i = col_n+1; i < MENU_ICON_NUM; i++) {
            lv_obj_align_to(img_buf[i], img_buf[i-1], LV_ALIGN_OUT_RIGHT_MID, x_gap, 0);
        }
    }

    for(int i = 0; i < MENU_ICON_NUM; i++) {
        lv_obj_align_to(lab_buf[i], img_buf[i], LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }
#endif
}
static void entry0(void) { }
static void exit0(void) { }
static void destroy0(void) {
    if(menu_taskbar){
        lv_obj_del(menu_taskbar);
        menu_taskbar = NULL;
    }
}

static scr_lifecycle_t screen0 = {
    .create = create0,
    .entry =   entry0,
    .exit  =   exit0,
    .destroy = destroy0,
};
#endif
//************************************[ screen 1 ]****************************************** clock
#if 1
static lv_obj_t *calendar;
static lv_obj_t *clock_time;
static lv_obj_t *clock_data;
static lv_obj_t *clock_ap;
static lv_obj_t *clock_month;
static lv_timer_t *get_timer = NULL;

static const char *week_list_en[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static const char * month_names_def[12] = LV_CALENDAR_DEFAULT_MONTH_NAMES;


static void scr1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void get_timer_event(lv_timer_t *t) 
{
    uint16_t hour, minute, second;
    uint16_t year, minth, day, week;


}

static void create1(lv_obj_t *parent) {

    clock_time = lv_label_create(parent);
    clock_data = lv_label_create(parent);
    clock_ap = lv_label_create(parent);
    clock_month = lv_label_create(parent);

    lv_obj_set_style_border_width(clock_data, 2, 0);
    lv_obj_set_style_pad_top(clock_data, 30, 0);
    lv_obj_set_style_border_side(clock_data, LV_BORDER_SIDE_TOP, LV_PART_MAIN);

    lv_obj_set_style_text_font(clock_time, &Font_Mono_Bold_90, LV_PART_MAIN);
    lv_obj_set_style_text_font(clock_data, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_set_style_text_font(clock_ap, &Font_Mono_Bold_30, LV_PART_MAIN);
    lv_obj_set_style_text_font(clock_month, &Font_Mono_Bold_30, LV_PART_MAIN);

    lv_label_set_text_fmt(clock_time, "%02d:%02d", 10, 19);
    lv_label_set_text_fmt(clock_data, "%04d-%02d-%02d Sun", 2024, 5, 8);
    lv_label_set_text_fmt(clock_ap, "%s", "P.M.");
    lv_label_set_text_fmt(clock_month, "%s", month_names_def[0]);

    calendar = lv_calendar_create(parent);
    lv_obj_set_size(calendar, 430, 380);
    
    // lv_obj_add_event_cb(calendar, event_handler, LV_EVENT_ALL, NULL);
    // lv_obj_set_style_radius(calendar, 20, LV_PART_MAIN);
    lv_obj_set_style_text_font(calendar, &Font_Geist_Bold_20, LV_PART_MAIN);

    lv_obj_set_style_border_width(calendar, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(lv_calendar_get_btnmatrix(calendar), 0, LV_PART_ITEMS);
    lv_obj_set_style_border_side(lv_calendar_get_btnmatrix(calendar), LV_BORDER_SIDE_TOP, LV_PART_MAIN);

    lv_calendar_set_today_date(calendar, 2024, 5, 9);
    lv_calendar_set_showed_date(calendar, 2024, 5);

    //---------------------
    // scr_middle_line(parent);

    // back
    scr_back_btn_create(parent, "Clock", scr1_btn_event_cb);
}
static void entry1(void) {
    get_timer = lv_timer_create(get_timer_event, 6000, NULL);

    lv_obj_set_style_text_align(clock_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_align(clock_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_align(clock_ap, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // lv_obj_align(clock_time, LV_ALIGN_LEFT_MID, 70, -50);
    // lv_obj_align_to(clock_data, clock_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
    // lv_obj_align_to(clock_ap, clock_time, LV_ALIGN_OUT_RIGHT_MID, 0, 20);

    lv_obj_align(calendar, LV_ALIGN_TOP_MID, 0, 130);
    lv_obj_align_to(clock_month, calendar, LV_ALIGN_OUT_TOP_RIGHT, 0, -5);
    lv_obj_align_to(clock_time, calendar, LV_ALIGN_OUT_BOTTOM_MID, 0, 100);
    lv_obj_align_to(clock_data, clock_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
    lv_obj_align_to(clock_ap, clock_time, LV_ALIGN_OUT_RIGHT_MID, 0, 20);
}
static void exit1(void) {
    if(get_timer) {
        lv_timer_del(get_timer);
        get_timer = NULL;
    }
}
static void destroy1(void) {
    lv_anim_del_all();
}

static scr_lifecycle_t screen1 = {
    .create = create1,
    .entry = entry1,
    .exit  = exit1,
    .destroy = destroy1,
};
#endif
//************************************[ screen 2 ]****************************************** lora
// --------------------- screen 2 --------------------- LoRa
#if 1
lv_obj_t * scr2_list;
static lv_obj_t *scr2_lab_buf[20];

static lv_obj_t * scr2_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, lv_pct(99));
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_20, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    return label;
}

static void scr2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void scr2_list_event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    for(int i = 0; i < lv_obj_get_child_cnt(obj); i++) 
    {
        lv_obj_t * child = lv_obj_get_child(obj, i);
        if(lv_obj_check_type(child, &lv_label_class)) {
            char *str = lv_label_get_text(child);

            if(strcmp("Auto Send", str) == 0)
            {
                scr_mgr_push(SCREEN2_1_ID, false);
            }
            if(strcmp("Manual Send", str) == 0)
            {
                scr_mgr_push(SCREEN2_2_ID, false);
            }
        }
    }
}

static void scr2_item_create(const char *name, lv_event_cb_t cb)
{
    lv_obj_t * obj = lv_obj_class_create_obj(&lv_list_btn_class, scr2_list);
    lv_obj_class_init_obj(obj);
    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);

    lv_obj_t *label = lv_label_create(obj);
    lv_label_set_text(label, name);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 10, 0);

    lv_obj_set_height(obj, 130);
    lv_obj_set_style_text_font(obj, &Font_Mono_Bold_30, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_text_color(obj, lv_color_hex(EPD_COLOR_FG), LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(obj, cb, LV_EVENT_CLICKED, NULL); 
}

static void create2(lv_obj_t *parent)
{
    scr2_list = lv_list_create(parent);
    lv_obj_set_size(scr2_list, lv_pct(93), lv_pct(91));
    lv_obj_align(scr2_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(scr2_list, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_pad_top(scr2_list, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_row(scr2_list, 15, LV_PART_MAIN);
    lv_obj_set_style_radius(scr2_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(scr2_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(scr2_list, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(scr2_list, lv_color_hex(EPD_COLOR_FG), LV_PART_MAIN);
    lv_obj_set_style_shadow_width(scr2_list, 0, LV_PART_MAIN);

    scr2_item_create("Auto Send", scr2_list_event);
    scr2_item_create("Manual Send", scr2_list_event);

    // back
    scr_back_btn_create(parent, "Lora", scr2_btn_event_cb);
}

static void entry2(void) { }
static void exit2(void) { }
static void destroy2(void) { }

static scr_lifecycle_t screen2 = {
    .create = create2,
    .entry = entry2,
    .exit  = exit2,
    .destroy = destroy2,
};
#endif
// --------------------- screen 2.1 --------------------- Auto Send
#if 1
static lv_obj_t *scr2_1_cont;
static lv_timer_t *scr2_1_timer = NULL;
static lv_obj_t *scr2_1_sw_btn;
static lv_obj_t *scr2_1_sw_btn_info;

static int scr2_1_mode = 0;

static void scr2_1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void lora_auto_send_event(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        if(scr2_1_mode == 0) {
            scr2_1_mode = 1;
            lv_label_set_text(scr2_1_sw_btn_info, "Recv");
        } else if(scr2_1_mode == 1) {
            scr2_1_mode = 0;
            lv_label_set_text(scr2_1_sw_btn_info, "Send");
        }
    }
}

static void lora_timer_event(lv_timer_t *t)
{
}

static void create2_1(lv_obj_t *parent) 
{
    scr2_1_cont = lv_obj_create(parent);
    lv_obj_set_size(scr2_1_cont, lv_pct(98), lv_pct(80));
    lv_obj_set_style_bg_color(scr2_1_cont, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr2_1_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr2_1_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr2_1_cont, 1, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr2_1_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr2_1_cont, 20, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr2_1_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(scr2_1_cont, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr2_1_cont, 5, LV_PART_MAIN);
    lv_obj_align(scr2_1_cont, LV_ALIGN_BOTTOM_MID, 0, -20);

    for(int i = 0; i < ARRAY_LEN(scr2_lab_buf); i++) {
        scr2_lab_buf[i] = scr2_create_label(scr2_1_cont);
        
        // lv_obj_set_width(scr2_lab_buf[i], lv_pct(90));
        lv_obj_set_width(scr2_lab_buf[i], LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(scr2_lab_buf[i], LV_SIZE_CONTENT);    /// 1
        lv_obj_set_style_border_width(scr2_lab_buf[i], 1, LV_PART_MAIN);
        lv_label_set_long_mode(scr2_lab_buf[i], LV_LABEL_LONG_DOT);
        lv_label_set_text_fmt(scr2_lab_buf[i], "Send #%d fadfasdfasdfasfadfasdfasdfasdfasdfadfasdfa", i);
    }

    scr2_1_sw_btn = lv_btn_create(parent);
    lv_obj_set_size(scr2_1_sw_btn, 100, 50);
    lv_obj_set_style_radius(scr2_1_sw_btn, 5, LV_PART_MAIN);
    lv_obj_set_style_border_width(scr2_1_sw_btn, 2, LV_PART_MAIN);
    scr2_1_sw_btn_info = lv_label_create(scr2_1_sw_btn);
    // lv_obj_set_style_text_font(scr2_1_sw_btn_info, FONT_BOLD_SIZE_15, LV_PART_MAIN);
    lv_obj_set_style_text_align(scr2_1_sw_btn_info, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(scr2_1_sw_btn_info, "Send");
    lv_obj_center(scr2_1_sw_btn_info);
    lv_obj_align(scr2_1_sw_btn, LV_ALIGN_TOP_RIGHT, -10, 20);
    lv_obj_add_event_cb(scr2_1_sw_btn, lora_auto_send_event, LV_EVENT_CLICKED, NULL);

    scr_back_btn_create(parent, ("Auto Send"), scr2_1_btn_event_cb);
}
static void entry2_1(void) 
{
    scr2_1_timer = lv_timer_create(lora_timer_event, 3000, NULL);
}
static void exit2_1(void) 
{
    if(scr2_1_timer) {
        lv_timer_del(scr2_1_timer);
        scr2_1_timer = NULL;
    }
}
static void destroy2_1(void) { }

static scr_lifecycle_t screen2_1 = {
    .create = create2_1,
    .entry = entry2_1,
    .exit  = exit2_1,
    .destroy = destroy2_1,
};
#endif
// --------------------- screen 2.2 --------------------- Manual Send
#if 1
#define LORA_MODE_SEND 0
#define LORA_MODE_RECV 1

#define MANUAL_SEND_LINE_MAX 15
#define MANUAL_SEND_LINE_MAX_CH 42

static bool lora_mode_st = LORA_MODE_SEND;
static lv_obj_t *lora_mode_lab;
static lv_obj_t *keyborad;
static lv_obj_t *textarea;
static lv_obj_t *cnt_label;

static lv_obj_t *lora_mode_sw;

int send_cnt = 10000;
int recv_cnt = 0;

int lab_idx = 0;

static lv_obj_t *scr2_2_cont_info;
static lv_obj_t *lora_lab_buf[15] = {0};


static void scr2_2_btn_event_cb(lv_event_t * e)
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
    // if(code == LV_EVENT_FOCUSED) {
    //     lv_keyboard_set_textarea(kb, ta);
    //     lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    //     lv_obj_clear_flag(ta, LV_OBJ_FLAG_HIDDEN);
    // }

    // if(code == LV_EVENT_DEFOCUSED) {
    //     lv_keyboard_set_textarea(kb, NULL);
    //     lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    //     lv_obj_add_flag(ta, LV_OBJ_FLAG_HIDDEN);
    // }

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        // printf("LV_EVENT_VALUE_CHANGED\n");
    }

    if(code == LV_EVENT_READY)
    {
        // printf("LV_EVENT_READY\n");

        char *str = lv_textarea_get_text(ta);
        int str_len = strlen(str);

        send_cnt += str_len;
        lv_label_set_text_fmt(cnt_label, "S:%d", send_cnt);

        printf("lab_idx=%d, mode=%d, len=%d, %s\n", lab_idx, lora_mode_st, str_len, str);
        

        // 

        static bool negation = true;

        if(negation)
        {
            lv_label_set_text_fmt(scr2_lab_buf[lab_idx], "S:%s", str);
        } else {
            char buf[43];
            lv_snprintf(buf, 43, "%s:R", str);
            int len = strlen(buf);
            int i;
            for(i = 0; i < 43-len; i++)
            {
                buf[i] = ' ';
            }

            printf("len=%d, i=%d\n", len, i);
            strcpy(&buf[i], str);
            lv_label_set_text_fmt(scr2_lab_buf[lab_idx], "%s:R", buf);
        }
        negation = !negation;

        lab_idx++;
        if(lab_idx >= MANUAL_SEND_LINE_MAX) {
            lab_idx = 0;
        }

        lv_textarea_set_text(ta,"");
    }
}

static void lora_mode_sw_event(lv_event_t * e)
{
    if(lora_mode_st == LORA_MODE_SEND)
    {
        lora_mode_st = LORA_MODE_RECV;
        lv_obj_add_flag(keyborad, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(textarea, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(scr2_2_cont_info, LV_OBJ_FLAG_HIDDEN);
        
    } 
    else if(lora_mode_st == LORA_MODE_RECV) 
    {
        lora_mode_st = LORA_MODE_SEND;
        lv_obj_clear_flag(keyborad, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(textarea, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(scr2_2_cont_info, LV_OBJ_FLAG_HIDDEN);
        
    }

    lv_label_set_text_fmt(lora_mode_lab, "MODE : %s", (lora_mode_st == LORA_MODE_SEND)? "SEND" : "RECV");
}

static lv_obj_t * scr2_2_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, lv_pct(99));
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_20, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    return label;
}

static void create2_2(lv_obj_t *parent) 
{
    /*Create a keyboard to use it with an of the text areas*/
    keyborad = lv_keyboard_create(parent);
    lv_obj_set_height(keyborad, lv_pct(40));
    lv_obj_align(keyborad, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_border_width(keyborad, 0, LV_PART_MAIN);

    /*Create a text area. The keyboard will write here*/
    textarea = lv_textarea_create(parent);
    lv_obj_set_style_text_font(textarea, &Font_Mono_Bold_20, LV_PART_MAIN);  
    lv_obj_add_event_cb(textarea, ta_event_cb, LV_EVENT_VALUE_CHANGED, keyborad);
    lv_obj_add_event_cb(textarea, ta_event_cb, LV_EVENT_READY, keyborad);
    lv_obj_set_size(textarea, lv_pct(98), lv_pct(6));
    lv_obj_add_state(textarea, LV_STATE_FOCUSED);       /// States
    lv_obj_clear_flag(textarea, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_letter_space(textarea, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(textarea, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_keyboard_set_textarea(keyborad, textarea);
    // lv_obj_set_style_border_width(textarea, 0, LV_PART_MAIN);
    // lv_obj_set_style_shadow_width(textarea, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_width(textarea, 0, LV_PART_MAIN);
    lv_obj_align_to(textarea, keyborad, LV_ALIGN_OUT_TOP_MID, 0, -5);

    scr2_2_cont_info = lv_obj_create(parent);
    
    lv_obj_set_size(scr2_2_cont_info, lv_pct(100), lv_pct(45));
    lv_obj_set_style_bg_color(scr2_2_cont_info, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr2_2_cont_info, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr2_2_cont_info, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr2_2_cont_info, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr2_2_cont_info, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(scr2_2_cont_info, 10, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr2_2_cont_info, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(scr2_2_cont_info, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr2_2_cont_info, 0, LV_PART_MAIN);
    lv_obj_align_to(scr2_2_cont_info, textarea, LV_ALIGN_OUT_TOP_MID, 0, 0);

    for(int i = 0; i < MANUAL_SEND_LINE_MAX; i++) {
        scr2_lab_buf[i] = scr2_2_create_label(scr2_2_cont_info);
        lv_label_set_text_fmt(scr2_lab_buf[i], "%d:1234567890", i);
    }
    // 
    lora_mode_sw = lv_btn_create(parent);
    lv_obj_set_style_radius(lora_mode_sw, 5, LV_PART_MAIN);
    lv_obj_set_style_border_width(lora_mode_sw, 2, LV_PART_MAIN);
    lora_mode_lab = lv_label_create(lora_mode_sw);
    lv_obj_set_style_text_font(lora_mode_lab, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_align(lora_mode_sw, LV_ALIGN_TOP_MID, 0, 22);
    lv_obj_add_event_cb(lora_mode_sw, lora_mode_sw_event, LV_EVENT_CLICKED, NULL);

    cnt_label = lv_label_create(parent);
    lv_obj_set_style_text_font(cnt_label, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_align(cnt_label, LV_ALIGN_TOP_RIGHT, -30, 22);

    scr_back_btn_create(parent, ("Manual Send"), scr2_2_btn_event_cb);
}
static void entry2_2(void) 
{
    send_cnt = 0;
    recv_cnt = 0;

    // if(lora_mode_st == LORA_MODE_SEND)
    // {
    //     lv_label_set_text(lora_mode_lab, "MODE : SEND");
    //     lv_label_set_text_fmt(cnt_label, "S:%d", send_cnt);
    //     lv_obj_clear_flag(keyborad, LV_OBJ_FLAG_HIDDEN);
    //     lv_obj_clear_flag(textarea, LV_OBJ_FLAG_HIDDEN);
    //     lv_obj_add_flag(scr2_2_cont_info, LV_OBJ_FLAG_HIDDEN);
    // }
    // else
    // {
    //     lv_label_set_text(lora_mode_lab, "MODE : RECV");
    //     lv_label_set_text_fmt(cnt_label, "R:%d", recv_cnt);
    //     lv_obj_add_flag(keyborad, LV_OBJ_FLAG_HIDDEN);
    //     lv_obj_add_flag(textarea, LV_OBJ_FLAG_HIDDEN);
    //     lv_obj_clear_flag(scr2_2_cont_info, LV_OBJ_FLAG_HIDDEN);
    // }
}
static void exit2_2(void) {
}
static void destroy2_2(void) { }

static scr_lifecycle_t screen2_2 = {
    .create = create2_2,
    .entry = entry2_2,
    .exit  = exit2_2,
    .destroy = destroy2_2,
};
#endif
//************************************[ screen 3 ]****************************************** sd_card
#if 1
static lv_obj_t *scr3_cont_file;
static lv_obj_t *scr3_cont_img;
static lv_obj_t *sd_info;
static lv_obj_t *ui_photos_img = NULL;

static void read_img_btn_event(lv_event_t * e)
{
    static int idx = 0;
    if(e->code == LV_EVENT_CLICKED) {
        lv_img_set_src(ui_photos_img, icon_buf[idx].icon_src);
        idx++;
        if(idx > sizeof(icon_buf)/sizeof(icon_buf[0])-1) {
            idx = 0;
        }
    }
}

static void scr3_btn_event_cb(lv_event_t * e)
{   
    
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void scr3_add_img_btn(lv_obj_t *parent, const void *src, const char *tetx)
{
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_set_size(obj, LCD_HOR_SIZE/11, LCD_HOR_SIZE/11);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);

    lv_obj_t *img = lv_img_create(obj);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, -10);
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(img, src);

    lv_obj_t *lab = lv_label_create(obj);
    lv_obj_set_style_text_font(lab, &Font_Mono_Bold_20, LV_PART_MAIN);
    lv_label_set_text(lab, tetx);
    lv_obj_align_to(lab, img, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    lv_obj_add_event_cb(img, read_img_btn_event, LV_EVENT_CLICKED, NULL);
}

static void create3(lv_obj_t *parent) {
    scr3_cont_file = lv_obj_create(parent);
    lv_obj_set_size(scr3_cont_file, lv_pct(49), lv_pct(85));
    lv_obj_set_style_bg_color(scr3_cont_file, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr3_cont_file, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr3_cont_file, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr3_cont_file, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr3_cont_file, 5, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr3_cont_file, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(scr3_cont_file, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr3_cont_file, 5, LV_PART_MAIN);
    lv_obj_set_align(scr3_cont_file, LV_ALIGN_BOTTOM_LEFT);

    scr3_cont_img = lv_obj_create(parent);
    lv_obj_set_size(scr3_cont_img, lv_pct(49), lv_pct(85));
    lv_obj_set_style_bg_color(scr3_cont_img, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr3_cont_img, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr3_cont_img, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr3_cont_img, 0, LV_PART_MAIN);
    lv_obj_set_align(scr3_cont_img, LV_ALIGN_BOTTOM_RIGHT);

    ui_photos_img = lv_img_create(scr3_cont_img);
    lv_obj_align(ui_photos_img, LV_ALIGN_CENTER, 0, 0);

    //---------------------
    scr_middle_line(parent);


    for(int i = 0; i < 10; i++) {
        scr3_add_img_btn(scr3_cont_file, "A:/img_PNG.png", "image");
    }


    lv_obj_t *lab1;
    if(true) {
        // ui_if_epd_read_from_SD();

        sd_info = lv_label_create(parent);
        lv_obj_set_style_text_font(sd_info, &Font_Mono_Bold_30, LV_PART_MAIN);
        lv_label_set_text(sd_info, "SD GALLERY"); 
    } else {
        sd_info = lv_label_create(parent);
        lv_obj_set_style_text_font(sd_info, &Font_Mono_Bold_90, LV_PART_MAIN);
        lv_label_set_text(sd_info, "NO FIND SD CARD!"); 
    }

    // back
    scr_back_btn_create(parent, "SD", scr3_btn_event_cb);
}
static void entry3(void) 
{
    if(true) {
        lv_obj_align(sd_info, LV_ALIGN_TOP_MID, 0, 22);
    } else {
        lv_obj_center(sd_info);
    }
}
static void exit3(void) { }
static void destroy3(void) { }

static scr_lifecycle_t screen3 = {
    .create = create3,
    .entry = entry3,
    .exit  = exit3,
    .destroy = destroy3,
};
#endif
//************************************[ screen 4 ]****************************************** setting
// --------------------- screen 4.1 --------------------- About System
#if 1
static void scr4_1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void create4_1(lv_obj_t *parent) 
{
    lv_obj_t *info = lv_label_create(parent);
    lv_obj_set_width(info, LV_HOR_RES * 0.9);
    lv_obj_set_style_text_color(info, lv_color_hex(EPD_COLOR_FG), LV_PART_MAIN);
    lv_obj_set_style_text_font(info, &Font_Mono_Bold_30, LV_PART_MAIN);
    lv_obj_set_style_text_align(info, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(info, LV_LABEL_LONG_WRAP);
    lv_label_set_text_fmt(info, "                           \n"
                                "Version:        %s\n"
                                "                           \n"
                                "Version:               v1.0\n"
                                "                           \n"
                                "Version:               v1.0\n"
                                "                           \n"
                                "Version:               v1.0\n"
                                "                           \n"
                                "Version:               v1.0\n"
                                "                           \n"
                                "Version:               v1.0\n"
                                "                           \n"
                                "Version:               v1.0\n"
                                "                           \n"
                                "Version:               v3.0\n"
                                "                           \n"
                                ,
                                "v1.0-241205"
                                );
    
    lv_obj_align(info, LV_ALIGN_TOP_MID, 0, 50);
    
    scr_back_btn_create(parent, ("About System"), scr4_1_btn_event_cb);
}
static void entry4_1(void) 
{
}
static void exit4_1(void) {
}
static void destroy4_1(void) { }

static scr_lifecycle_t screen4_1 = {
    .create = create4_1,
    .entry = entry4_1,
    .exit  = exit4_1,
    .destroy = destroy4_1,
};
#endif
// --------------------- screen 4.2 --------------------- Set EPD Vcom
#if 1

static lv_obj_t *set_1000mv_item;
static lv_obj_t *set_100mv_item;
static lv_obj_t *set_10mv_item;

static lv_obj_t * set_epd_vcom_lab;
static lv_obj_t *set_1000mv_lab;
static lv_obj_t *set_100mv_lab;
static lv_obj_t *set_10mv_lab;

static float set_epd_vcom_num;
static int   set_1000mv_num;
static int   set_100mv_num;
static int   set_10mv_num;

static void scr4_2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

/* clang-format on */
#define SET_RANGE(opt, num, min, max, num_lab) \
    if (opt == '+') {                          \
        num++;                                 \
    }                                          \
    else {                                     \
        num--;                                 \
    }                                          \
    num = num > max ? max : num;               \
    num = num < min ? min : num;               \
    lv_label_set_text_fmt(num_lab, "%d", num);
/* clang-format off */
static void scr4_2_sub_item_event(lv_event_t *e)
{
    lv_obj_t *parent = lv_obj_get_parent(e->target);
    char opt = (char)(e->user_data);

    if(parent == set_1000mv_item) 
    {
        SET_RANGE(opt, set_1000mv_num, 0, 4, set_1000mv_lab);
    } 
    else if(parent == set_100mv_item) 
    {
        SET_RANGE(opt, set_100mv_num, 0, 9, set_100mv_lab);
    } 
    else if(parent == set_10mv_item) 
    {
        SET_RANGE(opt, set_10mv_num, 0, 9, set_10mv_lab);
    }

    set_epd_vcom_num = (set_1000mv_num * 1000 + set_100mv_num * 100 + set_10mv_num * 10) / 1000.0;
    lv_label_set_text_fmt(set_epd_vcom_lab, "%.2fV", set_epd_vcom_num);
}

static lv_obj_t *scr4_2_sub_item_create(lv_obj_t *parent, lv_obj_t **lab, const char *range, const char *unit)
{
    lv_obj_t *ui_Container1 = lv_obj_create(parent);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_width(ui_Container1, 490);
    lv_obj_set_height(ui_Container1, 145);
    lv_obj_set_x(ui_Container1, 5);
    lv_obj_set_y(ui_Container1, -177);
    lv_obj_set_align(ui_Container1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_width(ui_Container1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_Container1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label2 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, 0);
    lv_obj_set_y(ui_Label2, 29);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_obj_set_style_border_width(ui_Label2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text_fmt(ui_Label2, "%s", range);
    lv_obj_set_style_text_font(ui_Label2, &Font_Mono_Bold_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    *lab = lv_label_create(ui_Container1);
    lv_obj_set_width(*lab, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(*lab, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(*lab, -23);
    lv_obj_set_y(*lab, -13);
    lv_obj_set_align(*lab, LV_ALIGN_CENTER);
    lv_label_set_text(*lab, "0");
    lv_obj_set_style_border_width(*lab, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(*lab, &Font_Mono_Bold_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label9 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, 20);
    lv_obj_set_y(ui_Label9, -12);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text_fmt(ui_Label9, "%s", unit);
    lv_obj_set_style_border_width(ui_Label9, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &Font_Mono_Bold_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *sub_btn = lv_obj_create(ui_Container1);
    lv_obj_remove_style_all(sub_btn);
    lv_obj_set_width(sub_btn, 76);
    lv_obj_set_height(sub_btn, 72);
    lv_obj_set_x(sub_btn, -171);
    lv_obj_set_y(sub_btn, 6);
    lv_obj_set_align(sub_btn, LV_ALIGN_CENTER);
    lv_obj_clear_flag(sub_btn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(sub_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(sub_btn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(sub_btn, scr4_2_sub_item_event, LV_EVENT_CLICKED, '-');

    lv_obj_t *sub_txt = lv_label_create(sub_btn);
    lv_obj_set_align(sub_txt, LV_ALIGN_CENTER);
    lv_label_set_text(sub_txt, "SUB");
    lv_obj_set_style_text_font(sub_txt, &Font_Mono_Bold_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *add_btn = lv_obj_create(ui_Container1);
    lv_obj_remove_style_all(add_btn);
    lv_obj_set_width(add_btn, 76);
    lv_obj_set_height(add_btn, 72);
    lv_obj_set_x(add_btn, 166);
    lv_obj_set_y(add_btn, 3);
    lv_obj_set_align(add_btn, LV_ALIGN_CENTER);
    lv_obj_clear_flag(add_btn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(add_btn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(add_btn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(add_btn, scr4_2_sub_item_event, LV_EVENT_CLICKED, '+');

    lv_obj_t *add_txt = lv_label_create(add_btn);
    lv_obj_set_align(add_txt, LV_ALIGN_CENTER);
    lv_label_set_text(add_txt, "ADD");
    lv_obj_set_style_text_font(add_txt, &Font_Mono_Bold_20, LV_PART_MAIN | LV_STATE_DEFAULT);


    return ui_Container1;
}

static void create4_2(lv_obj_t *parent) 
{
    lv_obj_t * ui_Container2 = lv_obj_create(parent);
    lv_obj_remove_style_all(ui_Container2);
    lv_obj_set_width(ui_Container2, lv_pct(100));
    lv_obj_set_height(ui_Container2, lv_pct(60));
    lv_obj_set_x(ui_Container2, 0);
    lv_obj_set_y(ui_Container2, 23);
    lv_obj_set_align(ui_Container2, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Container2, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Container2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_width(ui_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_Container2, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    set_epd_vcom_lab = lv_label_create(parent);
    lv_obj_set_width(set_epd_vcom_lab, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(set_epd_vcom_lab, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(set_epd_vcom_lab, -1);
    lv_obj_set_y(set_epd_vcom_lab, -310);
    lv_obj_set_align(set_epd_vcom_lab, LV_ALIGN_CENTER);
    lv_label_set_text(set_epd_vcom_lab, "1.54V");
    lv_obj_set_style_text_font(set_epd_vcom_lab, &Font_Mono_Bold_90, LV_PART_MAIN | LV_STATE_DEFAULT);

    set_1000mv_item = scr4_2_sub_item_create(ui_Container2, &set_1000mv_lab, "range: 0 - 4", "* V");
    set_100mv_item  = scr4_2_sub_item_create(ui_Container2, &set_100mv_lab , "range: 0 - 9", "* 0.1V");
    set_10mv_item   = scr4_2_sub_item_create(ui_Container2, &set_10mv_lab  , "range: 0 - 9", "* 0.01V");

    lv_obj_align(set_1000mv_lab, LV_ALIGN_CENTER, -23, -12);
    lv_obj_align(set_100mv_lab, LV_ALIGN_CENTER,  -38, -12);
    lv_obj_align(set_10mv_lab, LV_ALIGN_CENTER,   -48, -12);

    set_epd_vcom_num = (set_1000mv_num * 1000 + set_100mv_num * 100 + set_10mv_num * 10) / 1000.0;
    lv_label_set_text_fmt(set_epd_vcom_lab, "%.2fV", set_epd_vcom_num);

    scr_back_btn_create(parent, ("Set Vcom"), scr4_2_btn_event_cb);
}
static void entry4_2(void) 
{
}
static void exit4_2(void) {
}
static void destroy4_2(void) { }

static scr_lifecycle_t screen4_2 = {
    .create = create4_2,
    .entry = entry4_2,
    .exit  = exit4_2,
    .destroy = destroy4_2,
};
#endif
// --------------------- screen --------------------- Setting
#if 1
static lv_obj_t *scr4_list;
static lv_obj_t *setting_page;
static int setting_num = 0;
static int setting_page_num = 0;
static int setting_curr_page = 0;

void set_cb(int n) {}

const char *get_cb(int *ret_n)
{
    return "OFF";
}
char buf[16];
const char *get_vcom_cb(int *ret_n) 
{
    float v = (1560 / 1000.0);
    
    lv_snprintf(buf, 16, "%.5fV", v);
    return buf;
}

static ui_setting_handle setting_handle_list[] = {
    {.name = "Keypad Backlight", .type=UI_SETTING_TYPE_SW,  .set_cb = set_cb, .get_cb = get_cb},
    {.name = "-Set EPD Vcom", .type=UI_SETTING_TYPE_SUB,  .set_cb = NULL, .get_cb = get_vcom_cb, .sub_id=SCREEN4_2_ID},
    {.name = "-About System", .type=UI_SETTING_TYPE_SUB,  .set_cb = NULL, .get_cb = NULL, .sub_id=SCREEN4_1_ID},
};

static void setting_item_create();

static void scr4_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}
///////////////////// FUNCTIONS ////////////////////

/**
 * func:      setting
 * handle:    setting_handle_list
 * list:      scr4_list
 * num:       setting_num
 * page_num:  setting_page_num
 * curr_page: setting_curr_page
 */
// #define UI_LIST_CREATE(func, handle, list, num, page_num, curr_page) 
UI_LIST_CREATE(setting, setting_handle_list, scr4_list, setting_num, setting_page_num, setting_curr_page)

/**
 * func:      setting
 * list:      scr4_list
 * page:      setting_page
 * num:       setting_num
 * page_num:  setting_page_num
 * curr_page: setting_curr_page
 */
// #define UI_LIST_BTN_CREATE(func, list, page, num, page_num, curr_page) 
UI_LIST_BTN_CREATE(setting, scr4_list, setting_page, setting_num, setting_page_num, setting_curr_page)


void ui_list_btn_create(lv_obj_t *parent)
{
    lv_obj_t * ui_Button2 = lv_btn_create(parent);
    lv_obj_set_width(ui_Button2, 90);
    lv_obj_set_height(ui_Button2, 45);
    lv_obj_align(ui_Button2, LV_ALIGN_BOTTOM_MID, -140, -30);
    // lv_obj_set_align(ui_Button2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Button2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Button2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Button2, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_Button2, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_Button2, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui_Button2, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * ui_Label1 = lv_label_create(ui_Button2);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Back");
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * ui_Button14 = lv_btn_create(parent);
    lv_obj_set_width(ui_Button2, 90);
    lv_obj_set_height(ui_Button2, 45);
    lv_obj_align(ui_Button14, LV_ALIGN_BOTTOM_MID, 140, -30);
    // lv_obj_set_align(ui_Button14, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button14, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button14, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button14, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Button14, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Button14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Button14, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_Button14, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_Button14, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui_Button14, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * ui_Label15 = lv_label_create(ui_Button14);
    lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label15, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label15, "Next");
    lv_obj_set_style_text_color(ui_Label15, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Button2, setting_page_switch_cb, LV_EVENT_CLICKED, (void*)'n');
    lv_obj_add_event_cb(ui_Button14, setting_page_switch_cb, LV_EVENT_CLICKED, (void*)'p');
}

static void create4(lv_obj_t *parent) 
{
    printf("vcom = %s\n", setting_handle_list[1].get_cb(NULL));

    scr4_list = lv_list_create(parent);
    lv_obj_set_size(scr4_list, lv_pct(93), lv_pct(91));
    lv_obj_align(scr4_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(scr4_list, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_pad_top(scr4_list, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_row(scr4_list, 10, LV_PART_MAIN);
    lv_obj_set_style_radius(scr4_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(scr4_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(scr4_list, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(scr4_list, lv_color_hex(EPD_COLOR_FG), LV_PART_MAIN);
    lv_obj_set_style_shadow_width(scr4_list, 0, LV_PART_MAIN);

    setting_item_create();

    if(setting_page_num > 0)
        ui_list_btn_create(parent);

    setting_page = lv_label_create(parent);
    lv_obj_set_width(setting_page, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(setting_page, LV_SIZE_CONTENT);    /// 1
    lv_obj_align(setting_page, LV_ALIGN_BOTTOM_MID, 0, -30);
    lv_label_set_text_fmt(setting_page, "%d / %d", setting_curr_page, setting_page_num);
    lv_obj_set_style_text_color(setting_page, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(setting_page, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // back
    scr_back_btn_create(parent, "Setting", scr4_btn_event_cb);
}
static void entry4(void) { }
static void exit4(void) { }
static void destroy4(void) { }

static scr_lifecycle_t screen4 = {
    .create = create4,
    .entry = entry4,
    .exit  = exit4,
    .destroy = destroy4,
};
#endif
//************************************[ screen 5 ]****************************************** test
#if 1
static lv_obj_t *test_list;
static lv_obj_t *test_page;
static int test_num = 0;
static int test_page_num = 0;
static int test_curr_page = 0;

void test_set_cb(int n) {}

const char *test_get_cb(int *ret_n)
{
    return "OFF";
}

static ui_setting_handle test_handle_list[] = {
    {.name = "Keypad Backlight", .type=UI_SETTING_TYPE_SW,  .set_cb = test_set_cb, .get_cb = test_get_cb},
    {.name = "-About System", .type=UI_SETTING_TYPE_SUB,  .set_cb = test_set_cb, .get_cb = test_get_cb, .sub_id=SCREEN4_1_ID},
    {.name = "-About System", .type=UI_SETTING_TYPE_SUB,  .set_cb = test_set_cb, .get_cb = test_get_cb, .sub_id=SCREEN4_1_ID},
    {.name = "-About System", .type=UI_SETTING_TYPE_SUB,  .set_cb = test_set_cb, .get_cb = test_get_cb, .sub_id=SCREEN4_1_ID},
};

///////////////////// FUNCTIONS ////////////////////
/**
 * func:      test
 * handle:    test_handle_list
 * list:      test_list
 * num:       test_num
 * page_num:  test_page_num
 * curr_page: test_curr_page
 */
// #define UI_LIST_CREATE(func, handle, list, num, page_num, curr_page) 
UI_LIST_CREATE(test, test_handle_list, test_list, test_num, test_page_num, test_curr_page)

/**
 * func:      test
 * list:      test_list
 * page:      test_page
 * num:       test_num
 * page_num:  test_page_num
 * curr_page: test_curr_page
 */
// #define UI_LIST_BTN_CREATE(func, list, page, num, page_num, curr_page) 
UI_LIST_BTN_CREATE(test, test_list, test_page, test_num, test_page_num, test_curr_page)

static void scr5_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void create5(lv_obj_t *parent) {

    test_list = lv_list_create(parent);
    lv_obj_set_size(test_list, lv_pct(93), lv_pct(91));
    lv_obj_align(test_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(test_list, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_pad_top(test_list, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_row(test_list, 10, LV_PART_MAIN);
    lv_obj_set_style_radius(test_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(test_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(test_list, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(test_list, lv_color_hex(EPD_COLOR_FG), LV_PART_MAIN);
    lv_obj_set_style_shadow_width(test_list, 0, LV_PART_MAIN);

    test_item_create();

    if(test_page_num > 0)
        ui_list_btn_create(parent);

    test_page = lv_label_create(parent);
    lv_obj_set_width(test_page, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(test_page, LV_SIZE_CONTENT);    /// 1
    lv_obj_align(test_page, LV_ALIGN_BOTTOM_MID, 0, -30);
    lv_label_set_text_fmt(test_page, "%d / %d", test_curr_page, test_page_num);
    lv_obj_set_style_text_color(test_page, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(test_page, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // back
    scr_back_btn_create(parent, "Test", scr5_btn_event_cb);
}
static void entry5(void) { }
static void exit5(void) { }
static void destroy5(void) { }

static scr_lifecycle_t screen5 = {
    .create = create5,
    .entry = entry5,
    .exit  = exit5,
    .destroy = destroy5,
};
#endif
//************************************[ screen 6 ]****************************************** wifi
#if 1
static lv_obj_t *scr6_cont;
static lv_obj_t *wifi_st_lab = NULL;
static lv_obj_t *ip_lab;
static lv_obj_t *ssid_lab;
static lv_obj_t *pwd_lab;

static void wifi_info_label_create(lv_obj_t *parent)
{
    ip_lab = lv_label_create(parent);
    // lv_obj_set_style_text_color(ip_lab, lv_color_hex(COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(ip_lab, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_label_set_text_fmt(ip_lab, "ip: %s", "192.168.5.12");
    lv_obj_align_to(ip_lab, wifi_st_lab, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    ssid_lab = lv_label_create(parent);
    // lv_obj_set_style_text_color(ssid_lab, lv_color_hex(COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(ssid_lab, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_label_set_text_fmt(ssid_lab, "ssid: %s", "xinyuandianzi");
    lv_obj_align_to(ssid_lab, ip_lab, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    pwd_lab = lv_label_create(parent);
    // lv_obj_set_style_text_color(pwd_lab, lv_color_hex(COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(pwd_lab, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_label_set_text_fmt(pwd_lab, "pswd: %s", "AA15994823428");
    lv_obj_align_to(pwd_lab, ssid_lab, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
}
static void scr6_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        
        scr_mgr_pop(false);
    }
}

static void create6(lv_obj_t *parent) {

    bool wifi_st = false;
    wifi_st_lab = lv_label_create(parent);
    lv_obj_set_width(wifi_st_lab, 360);
    // lv_obj_set_style_text_color(wifi_st_lab, lv_color_hex(COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(wifi_st_lab, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_set_style_border_width(wifi_st_lab, 0, LV_PART_MAIN);
    lv_label_set_text(wifi_st_lab, (wifi_st ? "Wifi Connect" : "Wifi Disconnect"));
    // lv_obj_set_style_text_align(wifi_st_lab, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_style_text_align(wifi_st_lab, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(wifi_st_lab, LV_ALIGN_BOTTOM_MID, -0, -190);
    

    // if(ui_if_epd_get_WIFI()) {
        // wifi_info_label_create(parent);
    // }

    // lv_label_set_text(tips_label,   "Use ESP Touch App Configure your network\n"
    //                                 "1. Install ESPTouch App\n"
    //                                 "2. Turn on ESPTouch -> Click EspTouch\n"
    //                                 "3. Enter Your WiFi Password, Other setting use default\n"
    //                                 "4. Confirm\n"
    //                                 "5. Click Config WiFi Button\n"
    //                                 "6. Wait config done\n");

    lv_obj_t *label, *tips_label;
    tips_label = lv_label_create(parent);
    lv_obj_set_width(tips_label, LV_PCT(100));
    lv_label_set_long_mode(tips_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_text_color(tips_label, lv_color_black(), LV_PART_MAIN);
    lv_label_set_text(tips_label,   "1. Scan the QR code to download `EspTouch`\n\n"
                                    "2. Install and launch `EspTouch` APP\n\n"
                                    "3. Make sure your phone is \nconnected to WIFI\n\n"
                                    "4. Tap the [EspTouch] option of the APP\n\n"
                                    "5. Enter your WIFI password and click \n[confirm]\n\n"
                                    "6. Finally, click [config wifi] on the\n ink screen\n\n"
                                    "After that, wait for the network \ndistribution to succeed!"
                                    );

    
    lv_obj_set_style_text_font(tips_label, &Font_Mono_Bold_20, LV_PART_MAIN);
    lv_obj_align(tips_label, LV_ALIGN_TOP_MID, 0, 100);

    const char *android_url = "https://github.com/EspressifApp/EsptouchForAndroid/releases/tag/v2.0.0/esptouch-v2.0.0.apk";
    const char *ios_url     = "https://apps.apple.com/cn/app/espressif-esptouch/id1071176700";

    lv_coord_t size            = 120;
    lv_obj_t  *android_rq_code = lv_qrcode_create(parent, size, lv_color_black(), lv_color_white());
    lv_qrcode_update(android_rq_code, android_url, strlen(android_url));
    lv_obj_set_pos(android_rq_code, 340, 10);
    lv_obj_align(android_rq_code, LV_ALIGN_LEFT_MID, 50, 100);

    lv_obj_set_style_border_color(android_rq_code, lv_color_white(), 0);
    lv_obj_set_style_border_width(android_rq_code, 5, 0);
    label = lv_label_create(parent);
    lv_label_set_text(label, "Android");
    lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align_to(label, android_rq_code, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_obj_t *ios_rq_code = lv_qrcode_create(parent, size, lv_color_black(), lv_color_white());
    lv_qrcode_update(ios_rq_code, ios_url, strlen(ios_url));
    lv_obj_align(ios_rq_code, LV_ALIGN_RIGHT_MID, -50, 100);

    lv_obj_set_style_border_color(ios_rq_code, lv_color_white(), 0);
    lv_obj_set_style_border_width(ios_rq_code, 5, 0);
    label = lv_label_create(parent);
    lv_label_set_text(label, "IOS");
    lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align_to(label, ios_rq_code, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);


    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 200, 60);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -120);
    lv_obj_set_style_border_width(btn, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(btn, 10, LV_PART_MAIN);


    label = lv_label_create(btn);
    lv_label_set_text(label, "Config Wifi");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_center(label);


    //---------------------
    // scr_middle_line(parent);
    // back
    scr_back_btn_create(parent, "Wifi", scr6_btn_event_cb);
}
static void entry6(void) { }
static void exit6(void) { }
static void destroy6(void) { }

static scr_lifecycle_t screen6 = {
    .create = create6,
    .entry = entry6,
    .exit  = exit6,
    .destroy = destroy6,
};
#endif
//************************************[ screen 7 ]****************************************** battery
#if 1
static lv_obj_t *scr7_cont_letf;
static lv_obj_t *scr7_cont_right;
static lv_obj_t *batt_right[10] = {0};
static lv_obj_t *batt_left[10] = {0};
static lv_timer_t *batt_refr_timer = NULL;
#define line_max 28

static void battery_set_line(lv_obj_t *label, const char *str1, const char *str2)
{
    int w2 = strlen(str2);
    int w1 = line_max - w2;
    lv_label_set_text_fmt(label, "%-*s%-*s", w1, str1, w2, str2);
}
static void scr7_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void battery_data_refr(void)
{
    char buf[line_max];
    // BQ25896
    if(battery_25896_is_vaild()) {
        battery_set_line(batt_left[0], "Charge:", (battery_25896_is_chr() == true ? "Charging" : "Not charged"));

        lv_snprintf(buf, line_max, "%.2fV", battery_25896_get_VBUS());
        battery_set_line(batt_left[1], "VBUS:", buf);

        lv_snprintf(buf, line_max, "%s", battery_25896_get_VBUS_ST());
        battery_set_line(batt_left[2], "VBUS Status:", buf);

        lv_snprintf(buf, line_max, "%.2fV", battery_25896_get_VSYS());
        battery_set_line(batt_left[3], "VSYS:", buf);

        lv_snprintf(buf, line_max, "%s", battery_25896_get_VSYS_ST());
        battery_set_line(batt_left[4], "VSYS Status:", buf);

        lv_snprintf(buf, line_max, "%.2fV", battery_25896_get_VBAT());
        battery_set_line(batt_left[5], "VBAT:", buf);

        lv_snprintf(buf, line_max, "%.2fmA", battery_25896_get_ICHG());
        battery_set_line(batt_left[6], "ICHG:", buf);

        lv_snprintf(buf, line_max, "%.2fK", battery_25896_get_TEMP());
        battery_set_line(batt_left[7], "TEMP:", buf);

        lv_snprintf(buf, line_max, "%.2f", battery_25896_get_TSPCT());
        battery_set_line(batt_left[8], "TSPCT:", buf);

        lv_snprintf(buf, line_max, "%s", battery_25896_get_CHG_ERR());
        battery_set_line(batt_left[9], "Charger Err:", buf);
    }

    // BQ27220
    if(battery_27220_is_vaild()) {
        battery_set_line(batt_right[0], "Charge:", (battery_27220_is_chr() == true? "Charging" : "Not charged"));

        lv_snprintf(buf, line_max, "%.2fV", battery_27220_get_VOLT());
        battery_set_line(batt_right[1], "VOLT:", buf);

        lv_snprintf(buf, line_max, "%.2fV", battery_27220_get_VOLT_CHG());
        battery_set_line(batt_right[2], "VOLT Charge:", buf);

        lv_snprintf(buf, line_max, "%.2fmA", battery_27220_get_CURR_ARG());
        battery_set_line(batt_right[3], "CURR Average:", buf);

        lv_snprintf(buf, line_max, "%.2fmA", battery_27220_get_CURR_INS());
        battery_set_line(batt_right[4], "CURR Instant:", buf);

        lv_snprintf(buf, line_max, "%.2fmA", battery_27220_get_CURR_STD());
        battery_set_line(batt_right[5], "Curr Standby:", buf);

        lv_snprintf(buf, line_max, "%.2fmA", battery_27220_get_CURR_CHG());
        battery_set_line(batt_right[6], "Curr Charging:", buf);

        lv_snprintf(buf, line_max, "%.2f℃", battery_27220_get_TEMP());
        battery_set_line(batt_right[7], "TEMP:", buf);

        lv_snprintf(buf, line_max, "%.2fmAh", battery_27220_get_BATT_CAP());
        battery_set_line(batt_right[8], "CAP BATT:", buf);

        lv_snprintf(buf, line_max, "%.2fmAh", battery_27220_get_BATT_CAP_FULL());
        battery_set_line(batt_right[9], "CAP BATT Full:", buf);
    }
}

static void batt_refr_timer_event(lv_timer_t *t)
{
    battery_data_refr();
}


static lv_obj_t * scr7_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, LCD_HOR_SIZE/2-50);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_25, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    return label;
}

static void create7(lv_obj_t *parent)
{
    lv_obj_t *label;

    // left cont
    scr7_cont_letf = lv_obj_create(parent);
    lv_obj_set_size(scr7_cont_letf, lv_pct(49), lv_pct(85));
    lv_obj_set_style_bg_color(scr7_cont_letf, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr7_cont_letf, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr7_cont_letf, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr7_cont_letf, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr7_cont_letf, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr7_cont_letf, 20, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr7_cont_letf, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(scr7_cont_letf, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr7_cont_letf, 5, LV_PART_MAIN);
    lv_obj_set_align(scr7_cont_letf, LV_ALIGN_BOTTOM_LEFT);

    // left
    if(!battery_25896_is_vaild()) {
        label = scr7_create_label(scr7_cont_letf);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_label_set_text_fmt(label, "%s", "[0x6B] BQ25896 NOT FOUND");
        goto NO_BATTERY_BQ25896;
    }

    label = scr7_create_label(scr7_cont_letf);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text_fmt(label, "%s", "[0x6B] BQ25896");


    for(int i = 0; i < sizeof(batt_left) / sizeof(batt_left[0]); i++) {
        batt_left[i] = scr7_create_label(scr7_cont_letf);
    }

    battery_set_line(batt_left[0], "Charge:", "---");
    battery_set_line(batt_left[1], "VBUS:", "---");
    battery_set_line(batt_left[2], "VBUS Status:", "---");
    battery_set_line(batt_left[3], "VSYS:", "---");
    battery_set_line(batt_left[4], "VSYS Status:", "---");
    battery_set_line(batt_left[5], "VBAT:", "---");
    battery_set_line(batt_left[6], "ICHG:", "---");
    battery_set_line(batt_left[7], "TEMP:", "---");
    battery_set_line(batt_left[8], "TSPCT:", "---");
    battery_set_line(batt_left[9], "Charger Err:", "---");

    // right cont
NO_BATTERY_BQ25896:

    scr7_cont_right = lv_obj_create(parent);
    lv_obj_set_size(scr7_cont_right, lv_pct(49), lv_pct(85));
    lv_obj_set_style_bg_color(scr7_cont_right, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr7_cont_right, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr7_cont_right, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr7_cont_right, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr7_cont_right, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr7_cont_right, 10, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr7_cont_right, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(scr7_cont_right, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr7_cont_right, 5, LV_PART_MAIN);
    lv_obj_set_align(scr7_cont_right, LV_ALIGN_BOTTOM_RIGHT);

    // right
    if(!battery_27220_is_vaild()) {
        label = scr7_create_label(scr7_cont_right);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_label_set_text_fmt(label, "%s", "[0x55] BQ27220 NOT FOUND");
        goto NO_BATTERY;
    }
    label = scr7_create_label(scr7_cont_right);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text_fmt(label, "%s", "BQ27220 [0x55]");

    for(int i = 0; i < sizeof(batt_right) / sizeof(batt_right[0]); i++) {
        batt_right[i] = scr7_create_label(scr7_cont_right);
    }

    battery_set_line(batt_right[0], "Charge:", "---");
    battery_set_line(batt_right[1], "VOLT:", "---");
    battery_set_line(batt_right[2], "VOLT Charge:", "---");
    battery_set_line(batt_right[3], "CURR Average:", "---");
    battery_set_line(batt_right[4], "CURR Instant:", "---");
    battery_set_line(batt_right[5], "Curr Standby:", "---");
    battery_set_line(batt_right[6], "Curr Charging:", "---");
    battery_set_line(batt_right[7], "TEMP:", "---");
    battery_set_line(batt_right[8], "CAP BATT:", "---");
    battery_set_line(batt_right[9], "CAP BATT Full:", "---");

NO_BATTERY:
    //---------------------
    scr_middle_line(parent);
    // back
    scr_back_btn_create(parent, "battery", scr7_btn_event_cb);

    batt_refr_timer = lv_timer_create(batt_refr_timer_event, 3000, NULL);
}
static void entry7(void) {
    battery_data_refr();
    lv_timer_resume(batt_refr_timer);
}
static void exit7(void) {
    lv_timer_pause(batt_refr_timer);
}
static void destroy7(void) {
    lv_timer_del(batt_refr_timer);
    if(batt_refr_timer){
        batt_refr_timer = NULL;
    }
}

static scr_lifecycle_t screen7 = {
    .create = create7,
    .entry = entry7,
    .exit  = exit7,
    .destroy = destroy7,
};

#undef line_max
#endif
//************************************[ screen 8 ]****************************************** shutdown
#if 1

static void scr8_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_switch(SCREEN0_ID, false);
    }
}

static void create8(lv_obj_t *parent)
{

    lv_obj_t * img = lv_img_create(parent);
    lv_img_set_src(img, "A:/img_start1.png");
    lv_obj_center(img);

    const char *str1 = "PWR: Press and hold to power on";

    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "PWR: Press and hold to power on");
    lv_obj_set_style_transform_angle(label, -900, 0);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, 50, 80);

    lv_coord_t w = lv_txt_get_width(str1, strlen(str1), &lv_font_montserrat_20, 0, false);
    lv_obj_set_style_transform_pivot_x(label, w / 2, 0);
    printf("w = %d\n", w);

    // back
    scr_back_btn_create(parent, "Shoutdown", scr8_btn_event_cb);
}

static void entry8(void) {
    // ui_batt_power_off();
}
static void exit8(void) {
}
static void destroy8(void) { 

}

static scr_lifecycle_t screen8 = {
    .create = create8,
    .entry = entry8,
    .exit  = exit8,
    .destroy = destroy8,
};
#endif
//************************************[ UI ENTRY ]******************************************
void ui_epd47_entry(void)
{
    lv_disp_t *disp = lv_disp_get_default();
    disp->theme = lv_theme_mono_init(disp, false, LV_FONT_DEFAULT);

    scr_mgr_init();
    scr_mgr_set_bg_color(EPD_COLOR_BG);
    scr_mgr_register(SCREEN0_ID,   &screen0);    // menu
    scr_mgr_register(SCREEN1_ID,   &screen1);    // clock
    scr_mgr_register(SCREEN2_ID,   &screen2);    // lora
    scr_mgr_register(SCREEN2_1_ID, &screen2_1);  //     - Auto Send
    scr_mgr_register(SCREEN2_2_ID, &screen2_2);  //     - Manual Send
    scr_mgr_register(SCREEN3_ID,   &screen3);    // sd card
    scr_mgr_register(SCREEN4_ID,   &screen4);    // setting
    scr_mgr_register(SCREEN4_1_ID, &screen4_1);  //     - About System
    scr_mgr_register(SCREEN4_2_ID, &screen4_2);  //     - Set EPD Vcom
    scr_mgr_register(SCREEN5_ID,   &screen5);    // test
    scr_mgr_register(SCREEN6_ID,   &screen6);    // wifi
    scr_mgr_register(SCREEN7_ID,   &screen7);    // battery
    scr_mgr_register(SCREEN8_ID,   &screen8);    // battery

    scr_mgr_switch(SCREEN2_2_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}

#endif
