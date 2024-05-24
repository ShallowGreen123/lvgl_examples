
#include "ui_deckpro.h"
#if UI_DECKPRO_DISPALY

const char *test_str = "name";

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

void ui_deckpro_entry(void)
{
    lv_i18n_init(lv_i18n_language_pack);
    lv_i18n_set_locale("en-us");
    label1 = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(label1, &Font_Mono_Bold_20, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 100);
    lv_label_set_text(label1, _(test_str));
    lv_obj_t* btn = lv_obj_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(btn,50,50);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x335566), 0);
    lv_obj_add_event_cb(btn, callback, LV_EVENT_CLICKED, NULL);


    // label1 = lv_label_create(lv_scr_act());
    // lv_obj_set_style_text_font(label1, &Font_Han_Mono_Bold_20, 0);
    // lv_obj_align(label1, LV_ALIGN_CENTER, 0, 100);
    // lv_label_set_text(label1, "你好");
    // lv_obj_t* btn = lv_obj_create(lv_scr_act());
    // lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_size(btn,50,50);
    // lv_obj_set_style_bg_color(btn, lv_color_hex(0x335566), 0);
    // lv_obj_add_event_cb(btn, callback, LV_EVENT_CLICKED, NULL);
                        

    //// lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    // lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    // lv_obj_set_size(btn, 50, 50);                          /*Set its size*/
    // lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(btn, DECKPRO_COLOR_FG, LV_PART_MAIN);
    // // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/
    // lv_obj_center(btn);
    // lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    // lv_label_set_text(label, "C");                     /*Set the labels text*/
    // lv_obj_center(label);

    // btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    // lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    // lv_obj_set_size(btn, 50, 50);                          /*Set its size*/
    // lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(btn, DECKPRO_COLOR_FG, LV_PART_MAIN);
    // // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/
    // lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 0, 0);
    // label = lv_label_create(btn);          /*Add a label to the button*/
    // lv_label_set_text(label, "TL");                     /*Set the labels text*/
    // lv_obj_center(label);


    // btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    // lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    // lv_obj_set_size(btn, 50, 50);                          /*Set its size*/
    // lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(btn, DECKPRO_COLOR_FG, LV_PART_MAIN);
    // // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/
    // lv_obj_align(btn, LV_ALIGN_TOP_RIGHT, 0, 0);
    // label = lv_label_create(btn);          /*Add a label to the button*/
    // lv_label_set_text(label, "TR");                     /*Set the labels text*/
    // lv_obj_center(label);

    // btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    // lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    // lv_obj_set_size(btn, 50, 50);                          /*Set its size*/
    // lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(btn, DECKPRO_COLOR_FG, LV_PART_MAIN);
    // // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/
    // lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    // label = lv_label_create(btn);          /*Add a label to the button*/
    // lv_label_set_text(label, "BL");                     /*Set the labels text*/
    // lv_obj_center(label);


    // btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    // lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    // lv_obj_set_size(btn, 50, 50);                          /*Set its size*/
    // lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(btn, DECKPRO_COLOR_FG, LV_PART_MAIN);
    // // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/
    // lv_obj_align(btn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    // label = lv_label_create(btn);          /*Add a label to the button*/
    // lv_label_set_text(label, "BR");                     /*Set the labels text*/
    // lv_obj_center(label);

}

#endif /* UI_DECKPRO_DISPALY */

