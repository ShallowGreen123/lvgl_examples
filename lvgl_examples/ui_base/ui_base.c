
#include "ui_base.h"
#include "assets/assets.h"
#if UI_BASE_DISPALY

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

static void create0(lv_obj_t *parent) {
    lv_obj_t * btn = lv_btn_create(parent);     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}
static void entry0(void) { }
static void exit0(void) { }
static void destroy0(void) { }

static scr_lifecycle_t screen0 = {
    .create = create0,
    .entry = entry0,
    .exit  = exit0,
    .destroy = destroy0,
};

void ui_base_entry(void)
{
    scr_mgr_init();
    scr_mgr_set_bg_color(COLOR_BG);
    scr_mgr_register(SCREEN0_ID, &screen0);
    // scr_mgr_register(SCREEN1_ID, &screen1);
    // scr_mgr_register(SCREEN2_ID, &screen2);
    // scr_mgr_register(SCREEN3_ID, &screen3);
    // scr_mgr_register(SCREEN4_ID, &screen4);
    // scr_mgr_register(SCREEN5_ID, &screen5);
    // scr_mgr_register(SCREEN6_ID, &screen6);
    // scr_mgr_register(SCREEN7_ID, &screen7);
    // scr_mgr_register(SCREEN7_1_ID, &screen7_1); //   -IR
    // scr_mgr_register(SCREEN7_2_ID, &screen7_2); //   -MIC
    // scr_mgr_register(SCREEN7_3_ID, &screen7_3); //   -TF Card

    scr_mgr_switch(SCREEN0_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}

#endif

