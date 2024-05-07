#include "ui_epd47.h"
#include "assets/assets.h"

void epd_create0(lv_obj_t *parent) {
    lv_obj_t *scr5_cont = lv_obj_create(parent);
    lv_obj_set_size(scr5_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr5_cont, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr5_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr5_cont, 0, LV_PART_MAIN);
    // lv_obj_set_style_pad_all(scr5_cont, 0, LV_PART_MAIN);
    // lv_obj_set_flex_flow(scr5_cont, LV_FLEX_FLOW_ROW_WRAP);

    lv_obj_t * img1 = lv_img_create(scr5_cont);
    lv_obj_t * img2 = lv_img_create(scr5_cont);
    lv_obj_t * img3 = lv_img_create(scr5_cont);
    lv_obj_t * img4 = lv_img_create(scr5_cont);
    lv_obj_t * img5 = lv_img_create(scr5_cont);

    lv_img_set_src(img1, &img_clock);
    lv_img_set_src(img2, &img_lora);
    lv_img_set_src(img3, &img_sd_card);
    lv_img_set_src(img4, &img_setting);
    lv_img_set_src(img5, &img_test);
    
    lv_obj_align(img1, LV_ALIGN_LEFT_MID, 10, 0);
    lv_obj_align(img2, LV_ALIGN_LEFT_MID, 150, 0);
    lv_obj_align(img3, LV_ALIGN_LEFT_MID, 300, 0);
    lv_obj_align(img4, LV_ALIGN_LEFT_MID, 450, 0);
    lv_obj_align(img5, LV_ALIGN_LEFT_MID, 600, 0);

    lv_obj_add_flag(img1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img4, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img5, LV_OBJ_FLAG_CLICKABLE);
}
static void entry0(void) { }
static void exit0(void) { }
static void destroy0(void) { }

static scr_lifecycle_t screen0 = {
    .create = epd_create0,
    .entry =   entry0,
    .exit  =   exit0,
    .destroy = destroy0,
};

void ui_epd47_entry(void)
{
    scr_mgr_init();
    scr_mgr_set_bg_color(EPD_COLOR_BG);
    scr_mgr_register(SCREEN0_ID, &screen0);

    scr_mgr_switch(SCREEN0_ID, false); // set root screen
    scr_mgr_set_anim(LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT, LV_SCR_LOAD_ANIM_OVER_LEFT);
}