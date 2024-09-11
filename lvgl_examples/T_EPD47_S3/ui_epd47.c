

#include "ui_epd47.h"
#include "ui_epd47_port.h"

#if UI_EPD47_DISPALY
//************************************[ Other fun ]******************************************
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
//************************************[ screen 0 ]****************************************** menu
#if 1

#define MENU_ICON_NUM  (sizeof(icon_buf)/sizeof(icon_buf[0]))
#define MENU_CONT_HIGH (LCD_VER_SIZE * 0.84)

static int icon_width = 120; // 
static int menu_icon_num = 0;
static lv_obj_t *scr0_cont;
struct menu_icon {
    const void *icon_src;
    const char *icon_str;
};

const struct menu_icon icon_buf[] = {
    {"A:/img_clock.png", "clock"}, 
    {"A:/img_lora.png", "lora"},
    {"A:/img_sd_card.png", "sd card"},
    {"A:/img_setting.png", "setting"},
    {"A:/img_test.png", "test"},
    {"A:/img_wifi.png", "wifi"},
    {"A:/img_battery.png", "battery"},
    {"A:/img_shutdown.png", "shutdown"},
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
            case 6: scr_mgr_push(SCREEN7_ID, false); break;
            case 7: scr_mgr_push(SCREEN8_ID, false); break;
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

    //---------------------
    scr_middle_line(parent);

    // back
    scr_back_btn_create(parent, "Clock", scr1_btn_event_cb);
}
static void entry1(void) {
    get_timer = lv_timer_create(get_timer_event, 6000, NULL);

    lv_obj_set_style_text_align(clock_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_align(clock_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_align(clock_ap, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(clock_time, LV_ALIGN_LEFT_MID, 70, -50);
    lv_obj_align_to(clock_data, clock_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
    lv_obj_align_to(clock_ap, clock_time, LV_ALIGN_OUT_RIGHT_MID, 0, 20);
    lv_obj_align_to(clock_month, calendar, LV_ALIGN_OUT_TOP_RIGHT, 0, -5);
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
#if 1
static lv_obj_t *scr2_cont;
static lv_obj_t *scr2_cont_info;
static lv_obj_t *lora_mode_sw;
static lv_obj_t *lora_lab_time;
static lv_obj_t *lora_lab_mode;

static void scr2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        
        scr_mgr_pop(false);
    }
}

static void label_buf_fill_20(const char *text, int idx)
{
#define ONE_LINE_LEN 35
    char buf[ONE_LINE_LEN];
    int text_len = strlen(text);
    int i = text_len;
    int digi = 0;
    
    while(idx > 0) {
        idx = idx / 10;
        digi++;
    }
    
    strncpy(buf, ONE_LINE_LEN-3, text);

    while(i < (ONE_LINE_LEN-3)) {
        buf[i] = '-';
    };
#undef ONE_LINE_LEN
}

static lv_obj_t * scr2_create_label(lv_obj_t *parent)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_width(label, LCD_HOR_SIZE/2-50);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_25, LV_PART_MAIN);   
    lv_obj_set_style_border_width(label, 0, LV_PART_MAIN);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    return label;
}

static void create2(lv_obj_t *parent) {

    scr2_cont = lv_obj_create(parent);
    lv_obj_set_size(scr2_cont, lv_pct(49), lv_pct(85));
    lv_obj_set_style_bg_color(scr2_cont, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr2_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr2_cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr2_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr2_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr2_cont, 20, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr2_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(scr2_cont, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr2_cont, 5, LV_PART_MAIN);
    lv_obj_set_align(scr2_cont, LV_ALIGN_BOTTOM_LEFT);

    scr2_cont_info = lv_obj_create(parent);
    lv_obj_set_size(scr2_cont_info, lv_pct(49), lv_pct(85));
    lv_obj_set_style_bg_color(scr2_cont_info, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr2_cont_info, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(scr2_cont_info, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(scr2_cont_info, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr2_cont_info, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(scr2_cont_info, 10, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr2_cont_info, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(scr2_cont_info, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr2_cont_info, 5, LV_PART_MAIN);
    lv_obj_set_align(scr2_cont_info, LV_ALIGN_BOTTOM_RIGHT);

    //
    lora_mode_sw = lv_btn_create(parent);
    lv_obj_set_style_radius(lora_mode_sw, 5, LV_PART_MAIN);
    lv_obj_set_style_border_width(lora_mode_sw, 2, LV_PART_MAIN);
    
    lv_obj_t *label;
    label = lv_label_create(lora_mode_sw);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_25, LV_PART_MAIN);   
    lv_label_set_text(label, "MODE SW");
    
    //---------------------
    scr_middle_line(parent);

    lora_lab_mode = scr2_create_label(scr2_cont);
    // int mode = ui_if_epd_get_LORA_mode();
    // if(mode == LORA_MODE_SEND ){
        lv_label_set_text_fmt(lora_lab_mode, "%s : %s", "Mode", "send");
    // } else {
    //     lv_label_set_text_fmt(lora_lab_mode, "%s : %s", "Mode", "recv");
    // }

    lora_lab_time = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(lora_lab_time, "%s : %ds", "SendTimeInterval", 5);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : %0.1fMHz", "Frequency", 850.0);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : %0.1fKHz", "Bandwidth", 125.0);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : %d", "SpreadingFactor", 10);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : %d", "CodingRate", 6);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : 0x%X", "SyncWord", 0xAB);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : %d", "OutputPower", 10);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : %d", "CurrentLimit", 140);

    label = scr2_create_label(scr2_cont);
    lv_label_set_text_fmt(label, "%s : %d", "PreambleLength", 15);


    // --------------- RIGHT ---------------
    label = scr2_create_label(scr2_cont_info);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_label_set_text(label, "SEND");

    for(int i = 0; i < 10; i++) {
        label = scr2_create_label(scr2_cont_info);
        lv_label_set_text_fmt(label, "Lora Send #%d", i);
    }

    //
    // for(int i = 0; i < 10; i++) {
    //     char buf[35];
    //     lv_snprintf(buf, 35, "%d-%s", i, "Test Label");
    //     scr2_create_label(scr2_cont, buf);
        // label = lv_label_create(scr2_cont);
        // lv_obj_set_width(label, LCD_HOR_SIZE/2-50);
        // lv_obj_set_style_text_font(label, &Font_Mono_Bold_25, LV_PART_MAIN);   
        // lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
        // lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
        // lv_label_set_text_fmt(label, "1234567890123456789012345678");
        // lv_label_set_text_fmt(label, "1234567890123456789012345678901234567890");
    // }
    // back
    scr_back_btn_create(parent, "Lora", scr2_btn_event_cb);
}
static void entry2(void) { 
    lv_obj_align(lora_mode_sw, LV_ALIGN_TOP_MID, 0, 22);
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
#if 1
static lv_obj_t *scr4_cont;
static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static uint32_t active_index_1 = 0;
static uint32_t active_index_2 = 0;

lv_obj_t * ui_Slider1;
lv_obj_t * ui_Slider2;
lv_obj_t * ui_Slider3;
lv_obj_t * ui_label1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_backlight;
lv_obj_t * ui_refr_cycle;
lv_obj_t * ui_refr_time;



static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    if(e->code == LV_EVENT_VALUE_CHANGED) {
        if(slider == ui_Slider1) {
        lv_label_set_text_fmt(ui_backlight, "%d", (int)lv_slider_get_value(slider));
        } else if(slider == ui_Slider2) {
            lv_label_set_text_fmt(ui_refr_cycle, "%d", (int)lv_slider_get_value(slider));
        } else if(slider == ui_Slider3) {
            lv_label_set_text_fmt(ui_refr_time, "%d", (int)lv_slider_get_value(slider));
        }
    } else if(e->code == LV_EVENT_RELEASED) {
        printf("LV_EVENT_RELEASED\n");
    }

    
}

static void scr4_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

///////////////////// FUNCTIONS ////////////////////
void ui_event_Slider1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider_event_cb(e);
    }
}
void ui_event_Slider2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider_event_cb(e);
    }   
}
void ui_event_Slider3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider_event_cb(e);
    }
}

static void create4(lv_obj_t *parent) {
    ui_Slider1 = lv_slider_create(parent);
    lv_slider_set_range(ui_Slider1, 0, 10);
    lv_slider_set_value(ui_Slider1, 0, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Slider1) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Slider1, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Slider1, 500);
    lv_obj_set_height(ui_Slider1, 50);
    lv_obj_set_x(ui_Slider1, 333);
    lv_obj_set_y(ui_Slider1, 165);
    lv_obj_set_style_radius(ui_Slider1, 32767, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_Slider2 = lv_slider_create(parent);
    lv_slider_set_range(ui_Slider2, 1, 100);
    lv_slider_set_value(ui_Slider2, 50, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Slider2) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Slider2, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Slider2, 500);
    lv_obj_set_height(ui_Slider2, 50);
    lv_obj_set_x(ui_Slider2, 333);
    lv_obj_set_y(ui_Slider2, 288);
    lv_obj_set_style_radius(ui_Slider2, 32767, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_Slider3 = lv_slider_create(parent);
    lv_slider_set_range(ui_Slider3, 1, 5);
    lv_slider_set_value(ui_Slider3, 4, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_Slider3) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Slider3, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Slider3, 500);
    lv_obj_set_height(ui_Slider3, 50);
    lv_obj_set_x(ui_Slider3, 335);
    lv_obj_set_y(ui_Slider3, 414);
    lv_obj_set_style_radius(ui_Slider3, 32767, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_label1 = lv_label_create(parent);
    lv_obj_set_width(ui_label1, LV_SIZE_CONTENT);   /// 9
    lv_obj_set_height(ui_label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_label1, 58);
    lv_obj_set_y(ui_label1, 172);
    lv_label_set_text(ui_label1, "Backlight");
    lv_obj_set_style_text_font(ui_label1, &Font_Mono_Bold_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(parent);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -332);
    lv_obj_set_y(ui_Label2, 39);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Refresh Cycle");
    lv_obj_set_style_text_font(ui_Label2, &Font_Mono_Bold_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(parent);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -321);
    lv_obj_set_y(ui_Label3, 161);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Refresh Times");
    lv_obj_set_style_text_font(ui_Label3, &Font_Mono_Bold_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_backlight = lv_label_create(parent);
    lv_obj_set_width(ui_backlight, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_backlight, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_backlight, 870);
    lv_obj_set_y(ui_backlight, 170);
    lv_label_set_text(ui_backlight, "10");
    lv_obj_set_style_text_font(ui_backlight, &Font_Mono_Bold_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_refr_cycle = lv_label_create(parent);
    lv_obj_set_width(ui_refr_cycle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_refr_cycle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_refr_cycle, 870);
    lv_obj_set_y(ui_refr_cycle, 296);
    lv_label_set_text(ui_refr_cycle, "50");
    lv_obj_set_style_text_font(ui_refr_cycle, &Font_Mono_Bold_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_refr_time = lv_label_create(parent);
    lv_obj_set_width(ui_refr_time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_refr_time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_refr_time, 870);
    lv_obj_set_y(ui_refr_time, 425);
    lv_label_set_text(ui_refr_time, "4");
    lv_obj_set_style_text_font(ui_refr_time, &Font_Mono_Bold_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Slider1, ui_event_Slider1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Slider2, ui_event_Slider2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Slider3, ui_event_Slider3, LV_EVENT_ALL, NULL);

    // 
    lv_obj_set_style_anim_time(ui_Slider1, 0, LV_PART_MAIN);
    lv_obj_set_style_anim_time(ui_Slider2, 0, LV_PART_MAIN);
    lv_obj_set_style_anim_time(ui_Slider3, 0, LV_PART_MAIN);


    // /*Create a slider in the center of the display*/
    // lv_obj_t * slider = lv_slider_create(parent);
    // lv_obj_set_size(slider, 500, 40);
    // lv_slider_set_range(slider, 0, 10);
    // lv_obj_set_style_anim_time(slider, 0, LV_PART_MAIN);
    // lv_obj_center(slider);
    // // lv_obj_set_style_radius(slider, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    // lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    // /*Create a label below the slider*/
    // slider_label = lv_label_create(parent);
    // lv_label_set_text(slider_label, "0");

    // lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

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
static lv_obj_t *scr5_cont_PASS;
static lv_obj_t *scr5_cont_FAIL;

static void scr5_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        
        scr_mgr_pop(false);
    }
}

lv_obj_t * scr5_imgbtn_create(lv_obj_t *parent, int idx)
{
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_set_size(obj, 120, 150);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);

    lv_obj_t *img = lv_img_create(obj);
    lv_img_set_src(img, icon_buf[idx].icon_src);
    lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *lab = lv_label_create(obj);
    lv_obj_set_style_text_font(lab, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_label_set_text(lab, icon_buf[idx].icon_str);
    lv_obj_align_to(lab, img, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    return obj;
}

static void create5(lv_obj_t *parent) {

    scr5_cont_PASS = lv_obj_create(parent);
    lv_obj_set_size(scr5_cont_PASS, lv_pct(49), lv_pct(80));
    lv_obj_set_style_bg_color(scr5_cont_PASS, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr5_cont_PASS, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_style_border_width(scr5_cont_PASS, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr5_cont_PASS, 26, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr5_cont_PASS, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(scr5_cont_PASS, 27, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr5_cont_PASS, 27, LV_PART_MAIN);
    lv_obj_set_align(scr5_cont_PASS, LV_ALIGN_BOTTOM_LEFT);

    scr5_cont_FAIL = lv_obj_create(parent);
    lv_obj_set_size(scr5_cont_FAIL, lv_pct(49), lv_pct(80));
    lv_obj_set_style_bg_color(scr5_cont_FAIL, lv_color_hex(EPD_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr5_cont_FAIL, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_style_border_width(scr5_cont_FAIL, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr5_cont_FAIL, 26, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr5_cont_FAIL, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(scr5_cont_FAIL, 27, LV_PART_MAIN);
    lv_obj_set_style_pad_column(scr5_cont_FAIL, 27, LV_PART_MAIN);
    lv_obj_set_align(scr5_cont_FAIL, LV_ALIGN_BOTTOM_RIGHT);


    lv_obj_t *pass = lv_label_create(parent);
    lv_obj_t *fail = lv_label_create(parent);

    lv_obj_set_style_text_font(pass, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_set_style_text_font(fail, &Font_Mono_Bold_25, LV_PART_MAIN);

    lv_label_set_text(pass, "INIT PASS");
    lv_label_set_text(fail, "INIT FAIL");

    lv_obj_align_to(pass, scr5_cont_PASS, LV_ALIGN_OUT_TOP_MID, 0, 0);
    lv_obj_align_to(fail, scr5_cont_FAIL, LV_ALIGN_OUT_TOP_MID, 0, 0);


    for(int i = 0; i < 4; i++) {
        scr5_imgbtn_create(scr5_cont_PASS, i);
    }

    for(int i = 0; i < 4; i++) {
        scr5_imgbtn_create(scr5_cont_FAIL, i);
    }

    //---------------------
    scr_middle_line(parent);

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
    lv_obj_set_style_text_align(wifi_st_lab, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_align(wifi_st_lab, LV_ALIGN_BOTTOM_RIGHT, -0, -190);

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
    lv_label_set_text(tips_label,   "1. Scan the QR code to download `EspTouch`\n"
                                    "2. Install and launch `EspTouch` APP\n"
                                    "3. Make sure your phone is connected to WIFI\n"
                                    "4. Tap the [EspTouch] option of the APP\n"
                                    "5. Enter your WIFI password and click [confirm]\n"
                                    "6. Finally, click [config wifi] on the ink screen\n"
                                    "After that, wait for the network distribution to succeed!"
                                    );

    
    lv_obj_set_style_text_font(tips_label, &Font_Mono_Bold_25, LV_PART_MAIN);
    lv_obj_align(tips_label, LV_ALIGN_LEFT_MID, 50, -100);

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
    lv_obj_align_to(ios_rq_code, android_rq_code, LV_ALIGN_OUT_RIGHT_MID, 20, 0);

    lv_obj_set_style_border_color(ios_rq_code, lv_color_white(), 0);
    lv_obj_set_style_border_width(ios_rq_code, 5, 0);
    label = lv_label_create(parent);
    lv_label_set_text(label, "IOS");
    lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
    lv_obj_align_to(label, ios_rq_code, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);


    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 200, 60);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, -20, -120);
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
    scr_mgr_register(SCREEN0_ID, &screen0); // menu
    scr_mgr_register(SCREEN1_ID, &screen1); // clock
    scr_mgr_register(SCREEN2_ID, &screen2); // lora
    scr_mgr_register(SCREEN3_ID, &screen3); // sd card
    scr_mgr_register(SCREEN4_ID, &screen4); // setting
    scr_mgr_register(SCREEN5_ID, &screen5); // test
    scr_mgr_register(SCREEN6_ID, &screen6); // wifi
    scr_mgr_register(SCREEN7_ID, &screen7); // battery
    scr_mgr_register(SCREEN8_ID, &screen8); // battery

    scr_mgr_switch(SCREEN0_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}

#endif
