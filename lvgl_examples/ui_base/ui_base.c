
#include "ui_base.h"
#include "assets/assets.h"
#if UI_BASE_DISPALY

lv_obj_t * tv;
lv_obj_t * screen1;
lv_obj_t * screen2;

void tile_sw_event11(lv_event_t *e)
{
    lv_scr_load_anim(tv, LV_SCR_LOAD_ANIM_FADE_IN, 300, 0, false);
}

void screen1_create(void)
{
    screen1 = lv_obj_create(NULL);
    lv_obj_set_size(screen1, LV_PCT(100), LV_PCT(100));

    lv_obj_t * btn = lv_btn_create(screen1);     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 50, 50);                          /*Set its size*/
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_add_event_cb(btn, tile_sw_event11, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/
    lv_obj_center(btn);
    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "C");                     /*Set the labels text*/
    lv_obj_center(label);
}

void screen2_create(void)
{
    screen2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(screen2, LV_PCT(100), LV_PCT(100));
}


void tile_sw_event(lv_event_t *e)
{
    lv_scr_load_anim(screen1, LV_SCR_LOAD_ANIM_FADE_IN, 300, 0, false);
}

void ui_base_entry(void)
{
    screen1_create();

    tv = lv_tileview_create(NULL);

    /*Tile1: just a label*/
    lv_obj_t * tile1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_BOTTOM);
    lv_obj_t * label = lv_label_create(tile1);
    lv_label_set_text(label, "Scroll down");
    lv_obj_center(label);

    /*Tile2: a button*/
    lv_obj_t * tile2 = lv_tileview_add_tile(tv, 0, 1, LV_DIR_TOP | LV_DIR_RIGHT);

    lv_obj_t * btn = lv_btn_create(tile2);

    label = lv_label_create(btn);
    lv_label_set_text(label, "Scroll up or right");

    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, tile_sw_event, LV_EVENT_CLICKED, NULL);

    /*Tile3: a list*/
    lv_obj_t * tile3 = lv_tileview_add_tile(tv, 1, 1, LV_DIR_LEFT);
    lv_obj_t * list = lv_list_create(tile3);
    lv_obj_set_size(list, LV_PCT(100), LV_PCT(100));

    lv_list_add_btn(list, NULL, "One");
    lv_list_add_btn(list, NULL, "Two");
    lv_list_add_btn(list, NULL, "Three");
    lv_list_add_btn(list, NULL, "Four");
    lv_list_add_btn(list, NULL, "Five");
    lv_list_add_btn(list, NULL, "Six");
    lv_list_add_btn(list, NULL, "Seven");
    lv_list_add_btn(list, NULL, "Eight");
    lv_list_add_btn(list, NULL, "Nine");
    lv_list_add_btn(list, NULL, "Ten");

    lv_scr_load(tv);
}

#endif

