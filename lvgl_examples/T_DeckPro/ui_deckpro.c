
#include "ui_deckpro.h"
#include "ui_deckpro_port.h"

#if UI_DECKPRO_DISPALY

const char *test_str = "hello world";

lv_obj_t* label1;  
bool state = false;
void callback(lv_event_t* e) {
    if (state) {
        lv_i18n_set_locale("en-us");
        lv_obj_set_style_text_font(label1, &Font_Mono_Bold_20, 0);
    }
    else {
        lv_i18n_set_locale("zh-cn");
        lv_obj_set_style_text_font(label1, &Font_Han_Mono_Bold_20, 0);
    }
    lv_label_set_text(label1, _(test_str));
    state = !state;
    printf("hellow\n");
}

//************************************[ Other fun ]******************************************
#if 1

static void parent_sytle_init(lv_obj_t *parent)
{
    lv_obj_set_style_radius(parent, 10, 0);
    lv_obj_set_style_bg_color(parent, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(parent, 2, LV_PART_MAIN);
    lv_obj_set_style_border_color(parent, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_pad_all(parent, 26, LV_PART_MAIN);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(parent, 27, LV_PART_MAIN);
    lv_obj_set_style_pad_column(parent, 27, LV_PART_MAIN);
    lv_obj_set_align(parent, LV_ALIGN_BOTTOM_LEFT);
}

static lv_obj_t *scr_back_btn_create(lv_obj_t *parent, const char *text, lv_event_cb_t cb)
{
    lv_obj_t * btn = lv_btn_create(parent);
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
    lv_label_set_text(label2, " " LV_SYMBOL_LEFT);

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_align_to(label, label2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_text_font(label, &Font_Han_Mono_Bold_18, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_label_set_text(label, text);
    lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(label, cb, LV_EVENT_CLICKED, NULL);
    return label;
}

#endif
//************************************[ screen 0 ]****************************************** 
#if 1

struct menu_icon {
    const void *icon_src;
    const char *icon_str;
};

const struct menu_icon icon_buf[] = {
    {"A:/img_lora.png", "Lora"},
    {"A:/img_SD.png", "SD"},
    {"A:/img_setting.png", "Setting"},
    {"A:/img_GPS.png", "GPS"},
    {"A:/img_about.png", "About"},
    {"A:/img_other.png", "Other"},
    {"A:/img_lora.png", "Lora"},
    {"A:/img_SD.png", "SD"},
    {"A:/img_setting.png", "Setting"},
};

static void menu_btn_event(lv_event_t *e)
{
    int data = (int)e->user_data;
    if(e->code == LV_EVENT_CLICKED) {
        printf("[%d] %s is clicked.\n", data, icon_buf[data].icon_str);
        switch (data) {
            case 0: scr_mgr_push(SCREEN1_ID, false); break;
            case 1: scr_mgr_push(SCREEN2_ID, false); break;
            case 2: scr_mgr_push(SCREEN3_ID, false); break;
            case 3: scr_mgr_push(SCREEN4_ID, false); break;
            case 4: scr_mgr_push(SCREEN5_ID, false); break;
            case 5: scr_mgr_push(SCREEN6_ID, false); break;
            case 6: scr_mgr_push(SCREEN7_ID, false); break;
            default:
                break;
        }
    }
}

static lv_obj_t * scr0_imgbtn_create(lv_obj_t *parent, int idx)
{
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_set_size(obj, (LV_HOR_RES / 3) - 2, LV_VER_RES/3-2);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(obj, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);

    lv_obj_t *img = lv_img_create(obj);
    lv_img_set_src(img, icon_buf[idx].icon_src);
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img, menu_btn_event, LV_EVENT_CLICKED, (void *)idx);
    lv_obj_align(img, LV_ALIGN_CENTER, 1, -5);

    lv_obj_t *lab = lv_label_create(obj);
    lv_obj_set_style_text_font(lab, &Font_Han_Mono_Bold_16, LV_PART_MAIN);
    lv_label_set_text(lab, _(icon_buf[idx].icon_str));
    lv_obj_align_to(lab, img, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    return obj;
}

static void create0(lv_obj_t *parent) 
{
    lv_obj_set_style_bg_color(parent, DECKPRO_COLOR_BG, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(parent, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(parent, 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(parent, DECKPRO_COLOR_FG, LV_PART_MAIN);
    lv_obj_set_style_pad_all(parent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(parent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(parent, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW_WRAP);
    
    lv_obj_set_align(parent, LV_ALIGN_CENTER);

    for(int i = 0; i < sizeof(icon_buf)/sizeof(icon_buf[0]); i++) {
        scr0_imgbtn_create(parent, i);
    }
}

static void entry0(void) {  }
static void exit0(void) { }
static void destroy0(void) { }

static scr_lifecycle_t screen0 = {
    .create = create0,
    .entry = entry0,
    .exit  = exit0,
    .destroy = destroy0,
};
#endif
//************************************[ screen 1 ]****************************************** 
static void scr1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        scr_mgr_pop(false);
    }
}

static void create1(lv_obj_t *parent) {
    
    scr_back_btn_create(parent, _("Lora"), scr1_btn_event_cb);
}
static void entry1(void) {  }
static void exit1(void) { }
static void destroy1(void) { }

static scr_lifecycle_t screen1 = {
    .create = create1,
    .entry = entry1,
    .exit  = exit1,
    .destroy = destroy1,
};

//************************************[ screen 2 ]****************************************** 

static lv_obj_t *setting_list;
static lv_obj_t *language_label;
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
        case 0: { // "Rotatoion"
           
            } break;
        case 1: { // "Deep Sleep"
           
            } break;
        case 2:  // "Language"
            if(ui_get_default_language() == DEFAULT_LANGUAGE_EN) {
                lv_i18n_set_locale("zh-cn");
                ui_set_default_language(DEFAULT_LANGUAGE_CN);
            }else if(ui_get_default_language() == DEFAULT_LANGUAGE_CN) {
                lv_i18n_set_locale("en-us");
                ui_set_default_language(DEFAULT_LANGUAGE_EN);
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
    lv_label_set_text(lv_obj_get_child(setting1, 0), _("Rotatoion"));
    lv_label_set_text(lv_obj_get_child(setting2, 0), _("Deep Sleep"));
    lv_label_set_text(lv_obj_get_child(setting3, 0), _("Language"));
    lv_label_set_text(lv_obj_get_child(setting5, 0), _("About System"));

    switch (ui_get_default_language()) {
        case DEFAULT_LANGUAGE_EN: lv_label_set_text(language_label, _("English")); break;
        case DEFAULT_LANGUAGE_CN: lv_label_set_text(language_label, _("Chinese")); break;
        default:
            break;
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

    setting1 = lv_list_add_btn(setting_list, NULL, _("Rotatoion"));
    setting2 = lv_list_add_btn(setting_list, NULL, _("Deep Sleep"));
    setting3 = lv_list_add_btn(setting_list, NULL, _("Language"));
    setting5 = lv_list_add_btn(setting_list, NULL, _("About System"));

    for(int i = 0; i < lv_obj_get_child_cnt(setting_list); i++) {
        lv_obj_t *item = lv_obj_get_child(setting_list, i);
        lv_obj_set_style_text_font(item, &Font_Han_Mono_Bold_15, LV_PART_MAIN);
        lv_obj_set_style_bg_color(item, DECKPRO_COLOR_BG, LV_PART_MAIN);
        lv_obj_set_style_text_color(item, DECKPRO_COLOR_FG, LV_PART_MAIN);
        lv_obj_add_event_cb(item, setting_scr_event, LV_EVENT_CLICKED, (void *)i);
    }

    // setting3
    language_label = lv_label_create(setting3);
    lv_obj_set_style_text_font(language_label, &Font_Han_Mono_Bold_15, LV_PART_MAIN);
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

//************************************[ UI ENTRY ]******************************************
void ui_deckpro_entry(void)
{
    lv_disp_t *disp = lv_disp_get_default();
    disp->theme = lv_theme_mono_init(disp, false, LV_FONT_DEFAULT);

    // init language
    lv_i18n_init(lv_i18n_language_pack);
    if(ui_get_default_language() == DEFAULT_LANGUAGE_CN) {
        lv_i18n_set_locale("zh-cn");
    } else {
        lv_i18n_set_locale("en-us");
    }

    scr_mgr_init();

    scr_mgr_register(SCREEN0_ID, &screen0); // menu
    scr_mgr_register(SCREEN1_ID, &screen1); // clock
    scr_mgr_register(SCREEN2_ID, &screen2); // lora
    // scr_mgr_register(SCREEN3_ID, &screen3); // sd card
    // scr_mgr_register(SCREEN4_ID, &screen4); // setting
    // scr_mgr_register(SCREEN5_ID, &screen5); // test
    // scr_mgr_register(SCREEN6_ID, &screen6); // wifi
    // scr_mgr_register(SCREEN7_ID, &screen7); // wifi

    scr_mgr_switch(SCREEN0_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);

    // lv_i18n_init(lv_i18n_language_pack);
    // lv_i18n_set_locale("en-us");
    // label1 = lv_label_create(lv_scr_act());
    // lv_obj_set_style_text_font(label1, &Font_Mono_Bold_20, 0);
    // lv_obj_align(label1, LV_ALIGN_CENTER, 0, 100);
    // lv_label_set_text(label1, _(test_str));
    // lv_obj_t* btn = lv_obj_create(lv_scr_act());
    // lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_size(btn,50,50);
    // lv_obj_set_style_bg_color(btn, lv_color_hex(0x335566), 0);
    // lv_obj_add_event_cb(btn, callback, LV_EVENT_CLICKED, NULL);
}

#endif /* UI_DECKPRO_DISPALY */

