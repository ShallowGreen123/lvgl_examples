#include "ui_epd47.h"
#include "assets/assets.h"
//************************************[ Other fun ]******************************************
void scr_back_btn_create(lv_obj_t *parent, const char *text, lv_event_cb_t cb)
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

//************************************[ screen 0 ]****************************************** menu
#if 1

#define MENU_ICON_NUM  (6)
#define MENU_CONT_HIGH (LCD_VER_SIZE * 0.80)

lv_obj_t *scr0_cont;
struct menu_icon {
    const void *icon_src;
    const char *icon_str;
};

const struct menu_icon icon_buf[MENU_ICON_NUM] = {
    {&img_clock, "clock"}, 
    {&img_lora, "lora"},
    {&img_sd_card, "sd card"},
    {&img_setting, "setting"},
    {&img_test, "test"},
    {&img_wifi, "wifi"},
};

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
            default:
                break;
        }
    }
}

static void create0(lv_obj_t *parent) 
{
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

    lv_coord_t x_gap = (LCD_HOR_SIZE-(img_clock.header.w * col_n)) / (col_n+1);
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
}
static void entry0(void) { }
static void exit0(void) { }
static void destroy0(void) { }

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
static lv_obj_t * meter;
static lv_timer_t *get_timer = NULL;
static lv_meter_indicator_t * indic_min;
static lv_meter_indicator_t * indic_hour;
static lv_obj_t *clock_time;
static lv_obj_t *clock_data;
static lv_obj_t *clock_ap;
static lv_obj_t *clock_month;

static const char *week_list_en[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static const char * month_names_def[12] = LV_CALENDAR_DEFAULT_MONTH_NAMES;

static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

static void scr1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
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
    lv_obj_set_size(calendar, 380, 350);
    lv_obj_align(calendar, LV_ALIGN_RIGHT_MID, -50, 27);
    // lv_obj_add_event_cb(calendar, event_handler, LV_EVENT_ALL, NULL);
    // lv_obj_set_style_radius(calendar, 20, LV_PART_MAIN);
    lv_obj_set_style_text_font(calendar, &Font_Geist_Bold_20, LV_PART_MAIN);

    lv_obj_set_style_border_width(calendar, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(lv_calendar_get_btnmatrix(calendar), 0, LV_PART_ITEMS);
    lv_obj_set_style_border_side(lv_calendar_get_btnmatrix(calendar), LV_BORDER_SIDE_TOP, LV_PART_MAIN);

    lv_calendar_set_today_date(calendar, 2024, 5, 9);
    lv_calendar_set_showed_date(calendar, 2024, 5);



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

    // meter = lv_meter_create(parent);
    // lv_obj_set_size(meter, 400, 400);
    // lv_obj_set_style_border_width(meter, 2, LV_PART_MAIN);
    // lv_obj_set_style_border_color(meter, lv_color_black(), LV_PART_MAIN);
    // lv_obj_set_style_shadow_width(meter, 0, LV_PART_MAIN);

    // /*Create a scale for the minutes*/
    // /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    // lv_meter_scale_t * scale_min = lv_meter_add_scale(meter);
    // lv_meter_set_scale_ticks(meter, scale_min, 61, 3, 10, lv_palette_main(LV_PALETTE_GREY));
    // lv_meter_set_scale_range(meter, scale_min, 0, 60, 360, 270);

    // /*Create another scale for the hours. It's only visual and contains only major ticks*/
    // lv_meter_scale_t * scale_hour = lv_meter_add_scale(meter);
    // lv_meter_set_scale_ticks(meter, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
    // lv_meter_set_scale_major_ticks(meter, scale_hour, 1, 3, 20, lv_color_black(), 25);    /*Every tick is major*/
    // lv_meter_set_scale_range(meter, scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/

    // /*Add a the hands from images*/
    // indic_hour = lv_meter_add_needle_img(meter, scale_min, &img_hand, 5, 5);
    // indic_min = lv_meter_add_needle_img(meter, scale_min, &img_hand_sec, 5, 5);
    

    // /*Create an animation to set the value*/
    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_exec_cb(&a, set_value);
    // lv_anim_set_values(&a, 0, 60);
    // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_set_time(&a, 2000);     /*2 sec for 1 turn of the minute hand (1 hour)*/
    // lv_anim_set_var(&a, indic_min);
    // lv_anim_start(&a);

    // lv_anim_set_var(&a, indic_hour);
    // lv_anim_set_time(&a, 24000);    /*24 sec for 1 turn of the hour hand*/
    // lv_anim_set_values(&a, 0, 60);
    // lv_anim_start(&a);
    
    // back
    scr_back_btn_create(parent, "Clock", scr1_btn_event_cb);
}
static void entry1(void) {
    // lv_obj_align(meter, LV_ALIGN_RIGHT_MID, -100, 0);

    lv_obj_set_style_text_align(clock_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_align(clock_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_align(clock_ap, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(clock_time, LV_ALIGN_LEFT_MID, 70, -50);
    lv_obj_align_to(clock_data, clock_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
    lv_obj_align_to(clock_ap, clock_time, LV_ALIGN_OUT_RIGHT_MID, 0, 20);
    lv_obj_align_to(clock_month, calendar, LV_ALIGN_OUT_TOP_RIGHT, 0, -5);
}
static void exit1(void) { }
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
#if 1
static lv_obj_t *scr2_cont;

static void scr2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        
        scr_mgr_pop(false);
    }
}

static void create2(lv_obj_t *parent) {
    
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
//************************************[ screen 3 ]****************************************** sd_card
#if 1
lv_obj_t *scr3_cont;
lv_obj_t *sd_info;
lv_obj_t *ui_photos_img = NULL;

static void read_img_btn_event(lv_event_t * e)
{
    int data = (int)e->user_data;

    if(e->code = LV_EVENT_CLICKED) {
        printf("imgbtn %d\n", data);
    }
}

static void scr3_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void scr3_add_img_btn(void)
{
    lv_obj_t *obj = lv_obj_create(scr3_cont);
    lv_obj_set_size(obj, LCD_HOR_SIZE/9, LCD_HOR_SIZE/9);
    lv_obj_set_style_bg_color(obj, lv_color_white(), LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN);

    lv_obj_t *btn = lv_img_create(obj);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, -10);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(btn, &img_PNG);

    lv_obj_t *lab = lv_label_create(obj);
    lv_obj_set_style_text_font(lab, &Font_Mono_Bold_20, LV_PART_MAIN);
    lv_label_set_text(lab, "image");
    lv_obj_align_to(lab, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

static void create3(lv_obj_t *parent) {
    scr3_cont = lv_obj_create(parent);
    lv_obj_set_size(scr3_cont, lv_pct(100), lv_pct(85));
    lv_obj_set_style_bg_color(scr3_cont, lv_color_white(), LV_PART_MAIN);
    lv_obj_clear_flag(scr3_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(scr3_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr3_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr3_cont, 0, LV_PART_MAIN);

    for(int i = 0; i < 36; i++) {
        scr3_add_img_btn();
    }

    lv_obj_t *lab1;
    if(true) {
        // ui_if_epd_read_from_SD();
        ui_photos_img = lv_img_create(lv_layer_top());
        lv_obj_align(ui_photos_img, LV_ALIGN_BOTTOM_MID, 0, 0);

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
    lv_obj_align(scr3_cont, LV_ALIGN_BOTTOM_MID, 0, 0);

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
#if 1
lv_obj_t *scr4_cont;

static void scr4_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        
        scr_mgr_pop(false);
    }
}

static void create4(lv_obj_t *parent) {
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
lv_obj_t *scr5_cont;

static void scr5_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        
        scr_mgr_pop(false);
    }
}

static void create5(lv_obj_t *parent) {
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
lv_obj_t *scr6_cont;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        if(lv_calendar_get_pressed_date(obj, &date)) {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
        }
    }
}

static void scr6_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        
        scr_mgr_pop(false);
    }
}

static void create6(lv_obj_t *parent) {
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

//************************************[ UI ENTRY ]******************************************
void ui_epd47_entry(void)
{
    lv_disp_t *disp = lv_disp_get_default();
    disp->theme = lv_theme_mono_init(disp, false, LV_FONT_DEFAULT);

    scr_mgr_init();
    scr_mgr_set_bg_color(EPD_COLOR_BG);
    scr_mgr_register(SCREEN0_ID, &screen0);
    scr_mgr_register(SCREEN1_ID, &screen1);
    scr_mgr_register(SCREEN2_ID, &screen2);
    scr_mgr_register(SCREEN3_ID, &screen3);
    scr_mgr_register(SCREEN4_ID, &screen4);
    scr_mgr_register(SCREEN5_ID, &screen5);
    scr_mgr_register(SCREEN6_ID, &screen6);

    scr_mgr_switch(SCREEN0_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}
