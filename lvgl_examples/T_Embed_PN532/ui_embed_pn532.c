

#include "ui_embed_pn532.h"

#if UI_EMBED_PN532  

//************************************[ Other fun ]******************************************
#if 1
static bool prompt_is_busy = false;
static lv_timer_t *prompt_time;
static lv_obj_t *prompt_label;

static void prompt_label_timer(lv_timer_t *t)
{
    lv_obj_del((lv_obj_t *)t->user_data);
    lv_timer_del(t);
    prompt_is_busy = false;
}

static void prompt_create(const char *str, uint16_t time)
{
    prompt_label = lv_label_create(lv_layer_top());
    lv_obj_set_width(prompt_label, LCD_HOR_SIZE * 0.8);
    lv_label_set_text(prompt_label, str);
    lv_label_set_long_mode(prompt_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_radius(prompt_label, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(prompt_label, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(prompt_label, 3, LV_PART_MAIN);
    lv_obj_set_style_text_font(prompt_label, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_obj_set_style_bg_color(prompt_label, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_text_color(prompt_label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_align(prompt_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_center(prompt_label);
    prompt_time = lv_timer_create(prompt_label_timer, time, prompt_label);
    prompt_is_busy = true;
}

static void prompt_info(const char *str, uint16_t time)
{
    if(prompt_is_busy == false){
        prompt_create(str, time);
    } else {
        lv_obj_del(prompt_label);
        lv_timer_del(prompt_time);
        prompt_is_busy = false;

        prompt_create(str, time);
    }
}

static void scr_back_btn_create(lv_obj_t *parent, lv_event_cb_t cb)
{
    lv_obj_t * btn = lv_btn_create(parent);
    // lv_group_add_obj(lv_group_get_default(), btn);
    lv_obj_set_style_pad_all(btn, 0, 0);
    lv_obj_set_height(btn, 20);
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 8, 8);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_remove_style(btn, NULL, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(btn, 0, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(btn, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label2 = lv_label_create(btn);
    lv_obj_align(label2, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_color(label2, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text(label2, " " LV_SYMBOL_LEFT " ");
}

#endif
//************************************[ screen 0 ]****************************************** menu
#if 1
#define MENU_PROPORTION     (0.55)
#define MENU_LAB_PROPORTION (1 - MENU_PROPORTION)

static lv_obj_t *item_cont;
static lv_obj_t *menu_cont;
static lv_obj_t *menu_icon;
static lv_obj_t *menu_icon_lab;
static lv_obj_t *menu_time_lab;

static int fouce_item = 0;
static int hour = 10;
static int minute = 19;
static int second = 0;
static const char *name_buf[] = { 
    "<- Lora"   ,
    "<- WS2812" , 
    "<- NFC"    , 
    "<- Battery", 
    "<- Wifi"   ,
    "<- Other"  ,
    "<- Setting"
};

static void entry0_anim(void);
static void switch_scr0_anim(int user_data);

// event
static void scr0_btn_event_cb(lv_event_t * e)
{   
    int data = (int)e->user_data;

    if(e->code == LV_EVENT_CLICKED){
        
        fouce_item = data;
        switch (fouce_item)
        {
            case 0: switch_scr0_anim(SCREEN2_ID); break; // ID2 --- lora
            case 1: switch_scr0_anim(SCREEN1_ID); break; // ID1 --- ws2812
            case 2: switch_scr0_anim(SCREEN3_ID); break; // ID3 --- nfc
            case 3: switch_scr0_anim(SCREEN5_ID); break; // ID2 --- battery
            case 4: switch_scr0_anim(SCREEN6_ID); break; // ID5 --- wifi 
            case 5: switch_scr0_anim(SCREEN7_ID); break; // ID2 --- other
            case 6: switch_scr0_anim(SCREEN4_ID); break; // ID4 --- setting
            default:
                break;
        }
    }

    if(e->code == LV_EVENT_FOCUSED){
        switch (data)
        { 
            case 0: 
                lv_img_set_src(menu_icon, "A:/img_lora_32.png"); 
                lv_obj_set_style_img_recolor(menu_icon, lv_palette_main(LV_PALETTE_CYAN), LV_PART_MAIN);
                lv_obj_set_style_img_recolor_opa(menu_icon, LV_OPA_100, LV_PART_MAIN);
                break; 
            case 1: 
                lv_img_set_src(menu_icon, "A:/img_light_32.png"); 
                lv_obj_set_style_img_recolor_opa(menu_icon, LV_OPA_0, LV_PART_MAIN);
                break;    
            case 2: 
                lv_img_set_src(menu_icon, "A:/img_nfc_32.png");
                lv_obj_set_style_img_recolor(menu_icon, lv_palette_main(LV_PALETTE_CYAN), LV_PART_MAIN);
                lv_obj_set_style_img_recolor_opa(menu_icon, LV_OPA_100, LV_PART_MAIN);
                break;      
            case 3: 
                lv_img_set_src(menu_icon, "A:/img_battery_32.png"); 
                lv_obj_set_style_img_recolor_opa(menu_icon, LV_OPA_0, LV_PART_MAIN);
                break;  
            case 4: 
                lv_img_set_src(menu_icon, "A:/img_wifi_32.png");
                lv_obj_set_style_img_recolor_opa(menu_icon, LV_OPA_0, LV_PART_MAIN);
                break;     
            case 5: 
                lv_img_set_src(menu_icon, "A:/img_setting_32.png"); 
                lv_obj_set_style_img_recolor_opa(menu_icon, LV_OPA_0, LV_PART_MAIN);
                break;  
            case 6: 
                lv_img_set_src(menu_icon, "A:/img_setting_32.png"); 
                lv_obj_set_style_img_recolor_opa(menu_icon, LV_OPA_0, LV_PART_MAIN);
                break;  
            default:
                break;
        }
        lv_label_set_text(menu_icon_lab, ((char*)name_buf[data] + 3));
    }
}

static void anim_x_cb(void * var, int32_t v) {
    lv_obj_set_x(var, v);
}

static void anim_x1_cb(void * var, int32_t v) {
    lv_obj_set_x(var, v);
}

static void anim_ready_cb(struct _lv_anim_t *a){
    // indev_enabled(true);
}

static void switch_scr0_anim_ready_cb(struct _lv_anim_t *a){
    // indev_enabled(true);
    scr_mgr_switch((int)a->user_data, false);
}

static void entry0_anim(void)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, item_cont);
    lv_anim_set_values(&a, LCD_HOR_SIZE*MENU_PROPORTION, 0);
    lv_anim_set_time(&a, 600);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
    lv_anim_set_exec_cb(&a, anim_x_cb);
    // lv_anim_set_ready_cb(&a, anim_ready_cb);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 400);
    lv_anim_set_var(&a, menu_cont);
    lv_anim_set_values(&a, -LCD_HOR_SIZE*MENU_LAB_PROPORTION, 0);
    lv_anim_set_exec_cb(&a, anim_x1_cb);
    lv_anim_start(&a);
}

static void switch_scr0_anim(int user_data)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, item_cont);
    lv_anim_set_values(&a, 0, LCD_HOR_SIZE*MENU_PROPORTION);
    lv_anim_set_time(&a, 500);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
    lv_anim_set_exec_cb(&a, anim_x_cb);
    lv_anim_set_ready_cb(&a, switch_scr0_anim_ready_cb);
    lv_anim_set_user_data(&a, (void *)user_data);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 500);
    lv_anim_set_var(&a, menu_cont);
    lv_anim_set_values(&a, 0, -LCD_HOR_SIZE*MENU_LAB_PROPORTION);
    lv_anim_set_exec_cb(&a, anim_x1_cb);
    lv_anim_start(&a);
}

static void scroll_event_cb(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = (lv_obj_get_height(cont) ) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for(i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) {
            x = r;
        }
        else {
            x =  (diff_y * 0.866);
        }
        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

static void create0(lv_obj_t *parent) 
{
    menu_cont = lv_obj_create(parent);
    lv_obj_set_size(menu_cont, LCD_HOR_SIZE*MENU_LAB_PROPORTION, LCD_VER_SIZE);
    lv_obj_set_scrollbar_mode(menu_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_align(menu_cont, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_bg_color(menu_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_pad_all(menu_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(menu_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(menu_cont, 0, LV_PART_MAIN);

    menu_icon = lv_img_create(menu_cont);
    lv_obj_center(menu_icon);
    
    menu_icon_lab = lv_label_create(menu_cont);
    lv_obj_set_width(menu_icon_lab, LCD_HOR_SIZE * MENU_LAB_PROPORTION);
    lv_obj_set_style_text_align(menu_icon_lab, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(menu_icon_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(menu_icon_lab, &Font_Mono_Bold_18, LV_PART_MAIN);
    // lv_label_set_text(menu_icon_lab, "battery");
    lv_obj_align_to(menu_icon_lab, menu_cont, LV_ALIGN_BOTTOM_MID, 5, -25);
    
    menu_time_lab = lv_label_create(menu_cont);
    lv_obj_set_width(menu_time_lab, LCD_HOR_SIZE * MENU_LAB_PROPORTION);
    lv_obj_align(menu_time_lab, LV_ALIGN_TOP_MID, 5, 25);
    lv_obj_set_style_text_align(menu_time_lab, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(menu_time_lab, &Font_Mono_Bold_18, LV_PART_MAIN);
    // lv_obj_set_style_text_font(menu_time_lab, &lv_font_montserrat_26, LV_PART_MAIN);
    lv_label_set_recolor(menu_time_lab, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text_fmt(menu_time_lab, "#EE781F %02d# #C0C0C0 :# #AFCA31 %02d#", hour, minute);

    ////////////////////////////////////////////////
    item_cont = lv_obj_create(parent);
    lv_obj_set_size(item_cont, LCD_HOR_SIZE * MENU_PROPORTION, LCD_VER_SIZE);
    lv_obj_set_align(item_cont, LV_ALIGN_RIGHT_MID);
    lv_obj_set_flex_flow(item_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_bg_color(item_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_border_width(item_cont, 0, LV_PART_MAIN);
    lv_obj_add_event_cb(item_cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_style_radius(item_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_clip_corner(item_cont, true, 0);
    lv_obj_set_scroll_dir(item_cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(item_cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(item_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_row(item_cont, 10, LV_PART_MAIN);

    int buf_len = sizeof(name_buf)/sizeof(name_buf[0]);

    uint32_t i;
    for(i = 0; i < buf_len; i++) {
        lv_obj_t * btn = lv_btn_create(item_cont);
        lv_obj_set_width(btn, lv_pct(100));
        lv_obj_set_style_radius(btn, 10, LV_PART_MAIN);
        lv_obj_set_style_bg_color(btn, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
        lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
        lv_obj_set_style_shadow_width(btn, 0, LV_PART_MAIN);
        lv_obj_remove_style(btn, NULL, LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_width(btn, 2, LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_color(btn, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
        lv_obj_set_style_bg_img_opa(btn, LV_OPA_100, LV_PART_MAIN);
        lv_obj_add_event_cb(btn, scr0_btn_event_cb, LV_EVENT_CLICKED, (void *)i);
        lv_obj_add_event_cb(btn, scr0_btn_event_cb, LV_EVENT_FOCUSED, (void *)i);

        lv_obj_t * label = lv_label_create(btn);
        lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
        lv_obj_set_style_text_font(label, &Font_Mono_Bold_14, LV_PART_MAIN);
        lv_label_set_text(label, name_buf[i]);
    }
    /*Update the buttons position manually for first*/
    lv_event_send(item_cont, LV_EVENT_SCROLL, NULL);

    /*Be sure the fist button is in the middle*/
    lv_obj_scroll_to_view(lv_obj_get_child(item_cont, 0), LV_ANIM_OFF);

    lv_group_focus_obj(lv_obj_get_child(item_cont, fouce_item));

    lv_group_set_wrap(lv_group_get_default(), false);
}
static void entry0(void) {   
    entry0_anim();
}
static void exit0(void) {    printf("exit0\n");

    // for(int i = 0; i < lv_obj_get_child_cnt(item_cont); i++){
    //     lv_group_remove_obj(lv_obj_get_child(item_cont, i));
    // }
    // lv_group_remove_all_objs(lv_group_get_default());
}
static void destroy0(void) { printf("destroy0\n");
    // lv_obj_del(lv_obj_get_parent(item_cont));
    // lv_obj_del(menu_cont);
}

static scr_lifecycle_t screen0 = {
    .create = create0,
    .entry = entry0,
    .exit  = exit0,
    .destroy = destroy0,
};
#endif
//************************************[ screen 1 ]****************************************** ws2812
#if 1
static lv_obj_t *scr1_cont;
static lv_obj_t *light_acr;

static int ws2812_light = 10;
static lv_color_t ws2812_color ={.full = 0xF800};
static int ui_light_mode = 0;

static void entry1_anim(lv_obj_t *obj);
static void exit1_anim(int user_data, lv_obj_t *obj);

static void colorwheel_focus_event(lv_event_t *e)
{
    lv_obj_t *tgt = lv_event_get_target(e);
    lv_obj_t *label = lv_event_get_user_data(e);

    if(e->code == LV_EVENT_CLICKED){
        if (!lv_obj_has_flag(tgt, LV_OBJ_FLAG_CHECKABLE)) {
            lv_obj_clear_flag(tgt, LV_OBJ_FLAG_CHECKABLE);
            lv_group_set_editing(lv_group_get_default(), false);
        } else {
            lv_obj_add_flag(tgt, LV_OBJ_FLAG_CHECKABLE);
            lv_group_set_editing(lv_group_get_default(), true);
        }
    }
    else if(e->code == LV_EVENT_VALUE_CHANGED){
        ws2812_color = lv_colorwheel_get_rgb(tgt);

        lv_color32_t c32;
        uint8_t buf[3];
        c32.full = lv_color_to32(ws2812_color);
        buf[0] = c32.ch.red;
        buf[1] = c32.ch.green;
        buf[2] = c32.ch.blue;

        lv_label_set_text_fmt(label, "0x%02X%02X%02X", buf[0], buf[1], buf[2]);
        lv_obj_set_style_bg_color(light_acr, ws2812_color, LV_PART_KNOB);
        lv_obj_set_style_arc_color(light_acr, ws2812_color, LV_PART_INDICATOR);
        // lv_msg_send(MSG_WS2812_COLOR, &colorwheel_buf);
        // printf("full=0x%x, r=0x%x, g=0x%x, b=0x%x\n",c.full, c.ch.red, c.ch.green, c.ch.blue);
    }
}

static void value_changed_event_cb(lv_event_t * e)
{
    lv_obj_t * arc = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);

    ws2812_light = lv_arc_get_value(arc);
    lv_label_set_text_fmt(label, "%d", ws2812_light);
    // ws2812_set_light(ws2812_light);
}

static void scr1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        // scr_mgr_set_anim(LV_SCR_LOAD_ANIM_FADE_OUT, -1, -1);
        // scr_mgr_switch(SCREEN0_ID, false);
        exit1_anim(SCREEN0_ID, scr1_cont);
    }
}

static void ws2812_mode_event_cb(lv_event_t * e)
{
    lv_obj_t *tgt = (lv_obj_t *)e->target;
    lv_obj_t *lab = (lv_obj_t *)e->user_data;
    if(e->code == LV_EVENT_CLICKED){
        ui_light_mode++;
        ui_light_mode &= 0x3;
        switch (ui_light_mode)
        {
            case 0: lv_label_set_text(lab, " OFF ");    break;
            case 1: lv_label_set_text(lab, " demo1 "); break;
            case 2: lv_label_set_text(lab, " demo2 "); break;
            case 3: lv_label_set_text(lab, " demo3 "); break;
            default:
                break;
        }
        // ws2812_set_mode(mode);
        if(ui_light_mode == 0){
            // vTaskSuspend(ws2812_handle);
        } else {
            // vTaskResume(ws2812_handle);
        }
    }
}

static void anim1_x_cb(void * var, int32_t v) {
    lv_obj_set_style_opa((lv_obj_t *)var, v, LV_PART_MAIN);
}

static void anim1_ready_cb(struct _lv_anim_t *a) {
    scr_mgr_switch((int)a->user_data, false);
}

static void entry1_anim(lv_obj_t *obj)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, LV_OPA_0, LV_OPA_100);
    lv_anim_set_time(&a, 200);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_exec_cb(&a, anim1_x_cb);
    lv_anim_start(&a);
}

static void exit1_anim(int user_data, lv_obj_t *obj)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, LV_OPA_100, LV_OPA_0);
    lv_anim_set_time(&a, 200);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_exec_cb(&a, anim1_x_cb);
    lv_anim_set_ready_cb(&a, anim1_ready_cb);
    lv_anim_set_user_data(&a, (void *)user_data);
    lv_anim_start(&a);
}

static void create1(lv_obj_t *parent)
{   
    scr1_cont = lv_obj_create(parent);
    lv_obj_set_size(scr1_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr1_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr1_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr1_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr1_cont, 0, LV_PART_MAIN);

    lv_obj_t *colorwheel = lv_colorwheel_create(scr1_cont, true);
    lv_obj_set_size(colorwheel, 100, 100);
    lv_obj_set_style_arc_width(colorwheel, 6, LV_PART_MAIN);
    lv_obj_set_style_arc_width(colorwheel, 6, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(colorwheel, 6, LV_PART_KNOB);
    lv_obj_set_style_pad_all(colorwheel, 0, LV_PART_KNOB);  // remove KNOB style
    lv_obj_align(colorwheel, LV_ALIGN_RIGHT_MID, -35, 0);
    lv_colorwheel_set_rgb(colorwheel, ws2812_color);
    lv_obj_set_style_outline_pad(colorwheel, 4, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_radius(colorwheel, LV_RADIUS_CIRCLE, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(colorwheel, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(colorwheel, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_group_add_obj(lv_group_get_default(), colorwheel);
    lv_obj_t * label = lv_label_create(colorwheel);
    lv_obj_center(label);
    lv_label_set_text(label, "color");
    lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_add_event_cb(colorwheel, colorwheel_focus_event, LV_EVENT_CLICKED, label);
    lv_obj_add_event_cb(colorwheel, colorwheel_focus_event, LV_EVENT_VALUE_CHANGED, label);
    // lv_event_send(colorwheel, LV_EVENT_VALUE_CHANGED, NULL);

    /*Create an Arc*/
    light_acr = lv_arc_create(scr1_cont);
    lv_obj_set_size(light_acr, 100, 100);
    lv_obj_remove_style(light_acr, NULL, LV_PART_KNOB); // remove KNOB style
    lv_obj_align(light_acr, LV_ALIGN_LEFT_MID, 35, 0);
    lv_obj_set_style_bg_color(light_acr, ws2812_color, LV_PART_KNOB);
    lv_obj_set_style_arc_color(light_acr, ws2812_color, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(light_acr, 6, LV_PART_MAIN);
    lv_obj_set_style_arc_width(light_acr, 10, LV_PART_INDICATOR);
    lv_arc_set_rotation(light_acr, 90);
    lv_arc_set_bg_angles(light_acr, 0, 360);
    lv_arc_set_range(light_acr, 0, 255);
    lv_arc_set_value(light_acr, ws2812_light);
    lv_obj_set_style_outline_pad(light_acr, 4, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_radius(light_acr, LV_RADIUS_CIRCLE, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(light_acr, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(light_acr, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_group_add_obj(lv_group_get_default(), light_acr);
    lv_obj_t * label1 = lv_label_create(light_acr);
    lv_obj_center(label1);
    lv_obj_set_style_text_color(label1, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_add_event_cb(light_acr, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, label1);

    /*Manually update the label for the first time*/
    lv_event_send(light_acr, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t * mode_btn = lv_btn_create(scr1_cont);
    // lv_group_add_obj(lv_group_get_default(), mode_btn);
    lv_obj_set_style_pad_all(mode_btn, 0, 0);
    lv_obj_set_height(mode_btn, 30);
    lv_obj_align(mode_btn, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_border_color(mode_btn, lv_color_hex(EMBED_PN532_COLOR_BORDER), LV_PART_MAIN);
    lv_obj_set_style_border_width(mode_btn, 1, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(mode_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(mode_btn, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_remove_style(mode_btn, NULL, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(mode_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(mode_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(mode_btn, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_obj_t * mode_lab = lv_label_create(mode_btn);
    lv_obj_set_style_text_color(mode_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_align(mode_lab, LV_ALIGN_LEFT_MID, 0, 0);
    if(ui_light_mode== 0) {
        lv_label_set_text(mode_lab, " OFF ");
    } else {
        lv_label_set_text_fmt(mode_lab, " demo%d ", ui_light_mode);
    }
    lv_obj_add_event_cb(mode_btn, ws2812_mode_event_cb, LV_EVENT_CLICKED, mode_lab);
    lv_event_send(mode_btn, LV_EVENT_VALUE_CHANGED, mode_lab);


    // back btn
    scr_back_btn_create(scr1_cont, scr1_btn_event_cb);
}

static void entry1(void) {
    entry1_anim(scr1_cont);
}
static void exit1(void) {}
static void destroy1(void) {
}

static scr_lifecycle_t screen1 = {
    .create = create1,
    .entry = entry1,
    .exit = exit1,
    .destroy = destroy1,
};
#endif
//************************************[ screen 2 ]****************************************** lora
#if 1
static lv_obj_t *scr2_cont;
static lv_obj_t *lora_kb;
static lv_obj_t *lora_recv_ta;
static lv_obj_t *lora_recv_lab;
static lv_obj_t *lora_send_ta;
static lv_obj_t *lora_send_lab;
static lv_obj_t *lora_mode_btn;
static lv_timer_t *lora_recv_timer;
static int lora_recv_cnt = 0;
static int lora_send_cnt = 0;
static int lora_mode = 0;

static void entry2_anim(lv_obj_t *obj)
{
    entry1_anim(obj);
}

static void exit2_anim(int user_data, lv_obj_t *obj)
{
    exit1_anim(user_data, obj);
}

static void lora_recv_event(lv_timer_t *t)
{
    // if(lora_recv_success) {
    //     lora_recv_success = 0;
        lora_recv_cnt++;
        // for(int i = 0; i < lv_textarea_get_cursor_pos(lora_recv_ta); i++){
        //     lv_textarea_del_char(lora_recv_ta);
        // }
        lv_textarea_set_text(lora_recv_ta, " ");
        lv_label_set_text_fmt(lora_recv_lab, "recv:%d", lora_recv_cnt);
        // lv_textarea_add_text(lora_recv_ta, lora_recv_str.c_str());
    // }
}

static void mode_sw_event(lv_event_t *e)
{
    lv_obj_t *tgt =  (lv_obj_t *)e->target;
    lv_obj_t *data = (lv_obj_t *)e->user_data;
    
    if(e->code == LV_EVENT_CLICKED) {
        switch (lora_mode)
        {
            case 0: lora_mode = 1; lv_label_set_text(data, "recv"); break;
            case 1: lora_mode = 0; lv_label_set_text(data, "send"); break;
        default: break;
        }
    }
}
    

static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
        /*Focus on the clicked text area*/
        if(lora_kb != NULL) lv_keyboard_set_textarea(lora_kb, ta);
    }

    else if(code == LV_EVENT_READY) {
        LV_LOG_USER("Ready, current text: %s", lv_textarea_get_text(ta));
        uint32_t max_length = lv_textarea_get_cursor_pos(ta);
        if(max_length != 0){
            lora_send_cnt++;
            for(int i = 0; i < max_length; i++){
                lv_textarea_del_char(ta);
            }
            lv_label_set_text_fmt(lora_send_lab, "send:%d", lora_send_cnt);
        }
    }
}

static void scr2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        // scr_mgr_set_anim(LV_SCR_LOAD_ANIM_FADE_OUT, -1, -1);
        // scr_mgr_switch(SCREEN0_ID, false);
        exit2_anim(SCREEN0_ID, scr2_cont);
    }
}

static void create2(lv_obj_t *parent) {
    scr2_cont = lv_obj_create(parent);
    lv_obj_set_size(scr2_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr2_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr2_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr2_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr2_cont, 0, LV_PART_MAIN);

    lora_recv_ta = lv_textarea_create(scr2_cont);
    lv_obj_set_size(lora_recv_ta, 150, 60);
    lv_obj_set_style_border_width(lora_recv_ta, 1, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(lora_recv_ta, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(lora_recv_ta, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_text_color(lora_recv_ta, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_border_color(lora_recv_ta, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_textarea_set_text(lora_recv_ta, "");
    lv_obj_align(lora_recv_ta, LV_ALIGN_TOP_LEFT, 6, 30);
    lv_textarea_set_placeholder_text(lora_recv_ta, "Hello");
    lv_obj_add_event_cb(lora_recv_ta, ta_event_cb, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(lora_recv_ta);

    /*Create a label and position it above the text box*/
    lora_recv_lab = lv_label_create(scr2_cont);
    lv_obj_set_style_text_color(lora_recv_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text_fmt(lora_recv_lab, "recv:%d", lora_recv_cnt);
    lv_obj_align_to(lora_recv_lab, lora_recv_ta, LV_ALIGN_OUT_TOP_MID, 0, -5);

    lora_mode_btn = lv_btn_create(scr2_cont);
    lv_obj_set_height(lora_mode_btn, 20);
    lv_obj_set_style_shadow_width(lora_mode_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_row(lora_mode_btn, 0, LV_PART_MAIN);
    lv_obj_align(lora_mode_btn, LV_ALIGN_TOP_MID, 0, 6);
    lv_obj_t *mode_lab = lv_label_create(lora_mode_btn);
    lv_obj_center(mode_lab);
    switch (lora_mode)
    {
        case 0: lv_label_set_text(mode_lab, "send"); break;
        case 1: lv_label_set_text(mode_lab, "recv"); break;
        default: break;
    }
    lv_obj_add_event_cb(lora_mode_btn, mode_sw_event, LV_EVENT_CLICKED, mode_lab);

    /*Create the one-line mode text area*/
    lora_send_ta = lv_textarea_create(scr2_cont);
    lv_obj_set_size(lora_send_ta, 150, 60);
    lv_obj_set_style_border_width(lora_send_ta, 1, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(lora_send_ta, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(lora_send_ta, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_text_color(lora_send_ta, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_border_color(lora_send_ta, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_textarea_set_one_line(lora_send_ta, false);
    lv_textarea_set_password_mode(lora_send_ta, false);
    lv_obj_add_event_cb(lora_send_ta, ta_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(lora_send_ta, LV_ALIGN_TOP_RIGHT, -6, 30);
    lv_group_remove_obj(lora_send_ta);

    /*Create a label and position it above the text box*/
    lora_send_lab = lv_label_create(scr2_cont);
    lv_obj_set_style_text_color(lora_send_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_label_set_text_fmt(lora_send_lab, "send:%d", lora_send_cnt);
    lv_obj_align_to(lora_send_lab, lora_send_ta, LV_ALIGN_OUT_TOP_MID, 0, -5);

    /*Create a keyboard*/
    lora_kb = lv_keyboard_create(scr2_cont);
    lv_obj_set_style_border_width(lora_kb, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_BORDER), LV_PART_MAIN);
    lv_obj_remove_style(lora_kb, NULL, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(lora_kb, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_bg_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_ITEMS);
    lv_obj_set_style_bg_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_ITEMS);
    lv_obj_set_style_text_color(lora_kb, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_size(lora_kb,  LV_HOR_RES, LV_VER_RES / 2 - 10);
    lv_keyboard_set_textarea(lora_kb, lora_recv_ta); /*Focus it on one of the text areas to start*/
    lv_event_send(lora_recv_ta, LV_EVENT_FOCUSED, NULL);

    // lv_keyboard_set_textarea(lora_kb, lora_send_ta); /*Focus it on one of the text areas to start*/
    // lv_event_send(lora_send_ta, LV_EVENT_FOCUSED, NULL);

    // back btn
    scr_back_btn_create(scr2_cont, scr2_btn_event_cb);
}
static void entry2(void) {
    entry2_anim(scr2_cont);
    lv_group_set_wrap(lv_group_get_default(), true);
    lora_recv_timer = lv_timer_create(lora_recv_event, 1000, NULL);
}
static void exit2(void) {
    lv_timer_del(lora_recv_timer);
    lora_recv_timer = NULL;
    lv_group_set_wrap(lv_group_get_default(), false);
}
static void destroy2(void) { 
}

static scr_lifecycle_t screen2 = {
    .create = create2,
    .entry = entry2,
    .exit  = exit2,
    .destroy = destroy2,
};
#endif
//************************************[ screen 3 ]****************************************** nfc
#if 1
static lv_obj_t *scr3_cont;
static lv_obj_t *nfc_led;
static lv_obj_t *nfc_ledlab;
static lv_timer_t *nfc_chk_timer = NULL;

static void nfc_chk_timer_event(lv_timer_t *t)
{
    static bool flag = false;

    if(flag) {
        lv_led_on(nfc_led);
    }else{
        lv_led_off(nfc_led);
    }
    flag = !flag;
}

static void entry3_anim(lv_obj_t *obj)
{
    entry1_anim(obj);
}

static void exit3_anim(int user_data, lv_obj_t *obj)
{
    exit1_anim(user_data, obj);
}

static void scr3_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        // scr_mgr_set_anim(LV_SCR_LOAD_ANIM_FADE_OUT, -1, -1);
        // scr_mgr_switch(SCREEN0_ID, false);
        exit3_anim(SCREEN0_ID, scr3_cont);
    }
}


static void aboutui_screen_label_create(lv_obj_t *parent, const char *left_data, const char *right_data)
{
    lv_obj_t *ui_aboutpane = lv_obj_create(parent);
    lv_obj_set_width(ui_aboutpane, 222);
    lv_obj_set_height(ui_aboutpane, 40);
    lv_obj_set_align(ui_aboutpane, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_aboutpane, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_aboutpane, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_aboutpane, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_aboutpane, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_aboutpane, lv_color_hex(0xB4B4B4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_aboutpane, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_aboutpane, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_aboutpane, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_aboutlabel5 = lv_label_create(ui_aboutpane);
    lv_obj_set_width(ui_aboutlabel5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_aboutlabel5, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_aboutlabel5, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_aboutlabel5, left_data);
    lv_obj_set_style_text_color(ui_aboutlabel5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_aboutlabe = lv_label_create(ui_aboutpane);
    lv_obj_set_width(ui_aboutlabe, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_aboutlabe, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_aboutlabe, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_aboutlabe, right_data);
    lv_obj_set_style_text_color(ui_aboutlabe, lv_color_hex(0x787878), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_aboutlabe, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void create3(lv_obj_t *parent) {
    scr3_cont = lv_obj_create(parent);
    lv_obj_set_size(scr3_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr3_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr3_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr3_cont, 0, LV_PART_MAIN);

    
    lv_obj_t *lable = lv_label_create(scr3_cont);
    lv_obj_set_style_text_color(lable, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_align(lable, LV_ALIGN_TOP_MID, 0, 5);

    nfc_led  = lv_led_create(scr3_cont);
    lv_obj_set_size(nfc_led, 16, 16);
    lv_obj_align(nfc_led, LV_ALIGN_TOP_RIGHT, -10, 5);
    lv_led_off(nfc_led);

    nfc_ledlab = lv_label_create(scr3_cont);
    lv_obj_set_style_text_color(nfc_ledlab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_align_to(nfc_ledlab, nfc_led, LV_ALIGN_OUT_LEFT_MID, -6, 0);
    lv_label_set_text(nfc_ledlab, "xx -");

    uint32_t verisondata = 0x320101;
    uint32_t chip = (verisondata >> 24) & 0xFF;
    uint32_t verH = (verisondata >> 16) & 0xFF;
    uint32_t verL = (verisondata >>  8) & 0xFF;
    lv_label_set_text_fmt(lable, "PN5%x   ver: %d.%d", 0x32, 1, 6);

    lv_obj_t * list = lv_list_create(scr3_cont);
    lv_obj_set_size(list, LV_HOR_RES, 135);
    lv_obj_align(list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(list, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_pad_row(list, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(list, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(list, 0, LV_PART_MAIN);

    for(int btn_cnt = 1; btn_cnt <= 6; btn_cnt++) {
        char buf[32];
        lv_snprintf(buf, sizeof(buf), "Track %d", (int)btn_cnt);
        lv_list_add_btn(list, LV_SYMBOL_AUDIO, buf);
    }

    lv_list_add_btn(list, NULL, "0123456789012345678901234567890123");

    for(int i = 0; i < lv_obj_get_child_cnt(list); i++){
        lv_obj_t *item = lv_obj_get_child(list, i);
        lv_obj_set_height(item, 30);
        lv_obj_set_style_bg_color(item, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
        // lv_obj_set_style_text_font(item, &lv_font_montserrat_18, LV_PART_MAIN);
        lv_obj_set_style_text_color(item, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
        lv_obj_set_style_text_opa(item, LV_OPA_90, LV_PART_MAIN);
        lv_obj_remove_style(item, NULL, LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_color(item, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_width(item, 2, LV_STATE_FOCUS_KEY);
        // lv_obj_add_event_cb(item, list_item_event, LV_EVENT_CLICKED, (void *)i);
    }

    // back btn
    scr_back_btn_create(scr3_cont, scr3_btn_event_cb);
}
static void entry3(void) {  
    entry3_anim(scr3_cont);
    nfc_chk_timer = lv_timer_create(nfc_chk_timer_event, 500, NULL);
}
static void exit3(void) {    
    lv_timer_del(nfc_chk_timer);
    nfc_chk_timer = NULL;
}
static void destroy3(void) { 
}

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
static lv_obj_t *setting_list;
static lv_obj_t *theme_label;
static lv_obj_t *scr4_btn;
static lv_obj_t *scr4_btn_clt;

static void entry4_anim(lv_obj_t *obj)
{
    entry1_anim(obj);
}

static void exit4_anim(int user_data, lv_obj_t *obj)
{
    exit1_anim(user_data, obj);
}

static void scr4_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        // scr_mgr_set_anim(LV_SCR_LOAD_ANIM_FADE_OUT, -1, -1);
        // scr_mgr_switch(SCREEN0_ID, false);
        exit4_anim(SCREEN0_ID, scr4_cont);
    }
}


static void transform_angle_cb(void * var, int32_t v) {
    lv_obj_set_style_transform_angle((lv_obj_t *)var, v , LV_PART_MAIN);
}

static void transform_angle_anim(lv_obj_t *obj, int angle)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, angle*1800, (angle+1) * 1800);
    lv_anim_set_time(&a, 500);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_set_exec_cb(&a, transform_angle_cb);
    lv_anim_start(&a);
}

static void scr4_btn_clt_event(lv_event_t * e)
{
    static int angle = 0;
    if(e->code == LV_EVENT_CLICKED){
        
        lv_obj_set_style_transform_pivot_x(scr4_cont, LV_HOR_RES/2, LV_PART_MAIN);
        lv_obj_set_style_transform_pivot_y(scr4_cont, LV_VER_RES/2, LV_PART_MAIN);
        transform_angle_anim(scr4_cont, angle);
        angle++;
        angle &= 0x3;
        lv_obj_invalidate(scr4_cont);
        // lv_obj_align(scr4_btn, LV_ALIGN_LEFT_MID, 10, 0);
    }
}

static void create4(lv_obj_t *parent) {
    scr4_cont = lv_obj_create(parent);
    lv_obj_set_size(scr4_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr4_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr4_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr4_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr4_cont, 0, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(scr4_cont);
    lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_16, LV_PART_MAIN);
    lv_label_set_text(label, "Setting");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    setting_list = lv_list_create(scr4_cont);
    lv_obj_set_size(setting_list, LV_HOR_RES, 135);
    lv_obj_align(setting_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(setting_list, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_pad_top(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_row(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(setting_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(setting_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(setting_list, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(setting_list, 0, LV_PART_MAIN);

    lv_obj_t *setting1 = lv_list_add_btn(setting_list, NULL, "- Rotatoion");
    lv_obj_t *setting2 = lv_list_add_btn(setting_list, NULL, "- Deep Sleep");
    lv_obj_t *setting3 = lv_list_add_btn(setting_list, NULL, "- UI Theme");
    lv_obj_t *setting4 = lv_list_add_btn(setting_list, NULL, "- System Sound");
    lv_obj_t *setting5 = lv_list_add_btn(setting_list, NULL, "- About System");

    scr4_btn = lv_btn_create(scr4_cont);
    lv_obj_set_size(scr4_btn, 100, 50);
    lv_obj_align(scr4_btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t *label1 = lv_label_create(scr4_btn);
    lv_label_set_text(label1, "Bottom");


    scr4_btn_clt = lv_btn_create(scr4_cont);
    lv_obj_set_size(scr4_btn_clt, 100, 50);
    lv_obj_align(scr4_btn_clt, LV_ALIGN_RIGHT_MID, -10, 0);
    lv_obj_add_event_cb(scr4_btn_clt, scr4_btn_clt_event, LV_EVENT_CLICKED, NULL);

    // back btn
    scr_back_btn_create(scr4_cont, scr4_btn_event_cb);
}

static void entry4(void) {
    entry4_anim(scr4_cont);
}
static void exit4(void) {    
}
static void destroy4(void) {
}

static scr_lifecycle_t screen4 = {
    .create = create4,
    .entry = entry4,
    .exit  = exit4,
    .destroy = destroy4,
};
#endif
//************************************[ screen 5 ]****************************************** battery
#if 1

static lv_obj_t *scr5_cont;

static void entry5_anim(lv_obj_t *obj)
{
    entry1_anim(obj);
}

static void exit5_anim(int user_data, lv_obj_t *obj)
{
    exit1_anim(user_data, obj);
}

static void scr5_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        // scr_mgr_set_anim(LV_SCR_LOAD_ANIM_FADE_OUT, -1, -1);
        // scr_mgr_switch(SCREEN0_ID, false);
        exit5_anim(SCREEN0_ID, scr5_cont);
    }
}

static void tabview_clk_event(lv_event_t *e)
{
    int u = (int)e->user_data;
    if(e->code == LV_EVENT_CLICKED) {
        printf("tabview_clk_event: %d\n", u);
    }
}

static void create5(lv_obj_t *parent) {
    scr5_cont = lv_obj_create(parent);
    lv_obj_set_size(scr5_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr5_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr5_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr5_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr5_cont, 0, LV_PART_MAIN);
    lv_obj_set_flex_flow(scr5_cont, LV_FLEX_FLOW_ROW_WRAP);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * img1 = lv_img_create(scr5_cont);
    lv_obj_t * img2 = lv_img_create(scr5_cont);
    lv_obj_t * img3 = lv_img_create(scr5_cont);
    lv_obj_t * img4 = lv_img_create(scr5_cont);
    lv_obj_t * img5 = lv_img_create(scr5_cont);

    lv_img_set_src(img1, "A:/img_nfc_32.png");
    lv_img_set_src(img2, "A:/img_nfc_32.png");
    lv_img_set_src(img3, "A:/img_nfc_32.png");
    lv_img_set_src(img4, "A:/img_nfc_32.png");
    lv_img_set_src(img5, "A:/img_nfc_32.png");

    lv_obj_add_flag(img1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img4, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img5, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(img1, tabview_clk_event, LV_EVENT_CLICKED, (void *)1);
    lv_obj_add_event_cb(img2, tabview_clk_event, LV_EVENT_CLICKED, (void *)2);
    lv_obj_add_event_cb(img3, tabview_clk_event, LV_EVENT_CLICKED, (void *)3);
    lv_obj_add_event_cb(img4, tabview_clk_event, LV_EVENT_CLICKED, (void *)4);
    lv_obj_add_event_cb(img5, tabview_clk_event, LV_EVENT_CLICKED, (void *)5);

    // back btn
    scr_back_btn_create(scr5_cont, scr5_btn_event_cb);
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
static lv_obj_t *wifi_config_btn;
static lv_obj_t *wifi_help_btn;
static lv_obj_t *wifi_st_lab = NULL;
static lv_obj_t *ip_lab;
static lv_obj_t *ssid_lab;
static lv_obj_t *pwd_lab;
static lv_obj_t *config_state_lab;

static bool wifi_is_connect = true;

static void wifi_info_label_create(void);

void entry6_anim(lv_obj_t *obj)
{
    entry1_anim(obj);
}

void exit6_anim(int user_data, lv_obj_t *obj)
{
    exit1_anim(user_data, obj);
}


static void wifi_help_event(lv_event_t *e)
{
    if(e->code == LV_EVENT_CLICKED) {
        prompt_info(" You need to download 'EspTouch' to configure WiFi.", 1000);
    }
}

static void wifi_config_event_handler(lv_event_t *e)
{
    static int step = 0;
    lv_event_code_t code  = lv_event_get_code(e);

    if(code != LV_EVENT_CLICKED) {
        return;
    }

    if(wifi_is_connect){
        prompt_info(" WiFi is connected do not need to configure WiFi.", 1000);
        return;
    }

}

static void scr6_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        // scr_mgr_set_anim(LV_SCR_LOAD_ANIM_FADE_OUT, -1, -1);
        // scr_mgr_switch(SCREEN0_ID, false);
        exit6_anim(SCREEN0_ID, scr6_cont);
    }
}

static void wifi_info_label_create(void)
{   
    ip_lab = lv_label_create(scr6_cont);
    lv_obj_set_style_text_color(ip_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(ip_lab, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text_fmt(ip_lab, "ip: %s", "WiFi.localIP().toString()");
    lv_obj_align_to(ip_lab, wifi_st_lab, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    ssid_lab = lv_label_create(scr6_cont);
    lv_obj_set_style_text_color(ssid_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(ssid_lab, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text_fmt(ssid_lab, "ssid: %s", "wifi_ssid");
    lv_obj_align_to(ssid_lab, ip_lab, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    pwd_lab = lv_label_create(scr6_cont);
    lv_obj_set_style_text_color(pwd_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(pwd_lab, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text_fmt(pwd_lab, "pswd: %s", "wifi_password");
    lv_obj_align_to(pwd_lab, ssid_lab, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
}

static void create6(lv_obj_t *parent) {
    scr6_cont = lv_obj_create(parent);
    lv_obj_set_size(scr6_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr6_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr6_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr6_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr6_cont, 0, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(scr6_cont);
    lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_16, LV_PART_MAIN);
    lv_label_set_text(label, "Wifi config");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    wifi_st_lab = lv_label_create(scr6_cont);
    lv_obj_set_style_text_color(wifi_st_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(wifi_st_lab, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(wifi_st_lab, (wifi_is_connect == true ? "Wifi Connect" : "Wifi Disconnect"));
    lv_obj_align(wifi_st_lab, LV_ALIGN_TOP_LEFT, 5, 40);

    if(wifi_is_connect) {
        wifi_info_label_create();
    }

    wifi_config_btn = lv_btn_create(scr6_cont);
    lv_obj_set_size(wifi_config_btn, 100, 40);
    lv_obj_set_style_border_width(wifi_config_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(wifi_config_btn, 0, LV_PART_MAIN);
    lv_obj_remove_style(wifi_config_btn, NULL, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(wifi_config_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(wifi_config_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(wifi_config_btn, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_obj_align(wifi_config_btn, LV_ALIGN_TOP_RIGHT, -20 , 40);
    lv_obj_t *config_lab = lv_label_create(wifi_config_btn);
    lv_obj_center(config_lab);
    lv_obj_set_style_text_color(config_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(config_lab, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(config_lab, "config");
    lv_obj_add_event_cb(wifi_config_btn, wifi_config_event_handler, LV_EVENT_CLICKED, NULL);

    wifi_help_btn = lv_btn_create(scr6_cont);
    lv_obj_set_size(wifi_help_btn, 100, 40);
    lv_obj_set_style_border_width(wifi_help_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(wifi_help_btn, 0, LV_PART_MAIN);
    lv_obj_remove_style(wifi_help_btn, NULL, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(wifi_help_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(wifi_help_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(wifi_help_btn, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_obj_align(wifi_help_btn, LV_ALIGN_BOTTOM_RIGHT, -20 , -40);
    lv_obj_t *help_lab = lv_label_create(wifi_help_btn);
    lv_obj_center(help_lab);
    lv_obj_set_style_text_color(help_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(help_lab, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(help_lab, "help");
    lv_obj_add_event_cb(wifi_help_btn, wifi_help_event, LV_EVENT_CLICKED, NULL);

    // back btn
    scr_back_btn_create(scr6_cont, scr6_btn_event_cb);
}
static void entry6(void) {   }
static void exit6(void) {   }
static void destroy6(void) { 
}

static scr_lifecycle_t screen6 = {
    .create = create6,
    .entry = entry6,
    .exit  = exit6,
    .destroy = destroy6,
};
#endif
//************************************[ screen 7 ]****************************************** other(IR、MIC、SD)
// --------------------- screen 7.1 --------------------- IR
#if 1
static lv_obj_t *scr7_1_cont;

static void entry7_1_anim(lv_obj_t *obj) { entry1_anim(obj); }
static void exit7_1_anim(int user_data, lv_obj_t *obj) { exit1_anim(user_data, obj); }

static void scr7_1_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        exit7_1_anim(SCREEN7_ID, scr7_1_cont);
    }
}

static void create7_1(lv_obj_t *parent) 
{   
    scr7_1_cont = lv_obj_create(parent);
    lv_obj_set_size(scr7_1_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr7_1_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr7_1_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr7_1_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr7_1_cont, 0, LV_PART_MAIN);

    lv_obj_t *info = lv_label_create(scr7_1_cont);
    lv_obj_set_width(info, LCD_HOR_SIZE * 0.9);
    lv_obj_set_style_text_color(info, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(info, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_long_mode(info, LV_LABEL_LONG_WRAP);
    lv_label_set_text(info, "Turn on the phone's infrared remote control and search for LG TV remote control to control the device");
    lv_obj_center(info);

    lv_obj_t *label = lv_label_create(scr7_1_cont);
    lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(label, "Infrared");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    // back bottom
    scr_back_btn_create(scr7_1_cont, scr7_1_btn_event_cb);
}
static void entry7_1(void) {
    entry7_1_anim(scr7_1_cont);
}
static void exit7_1(void) {}
static void destroy7_1(void) {}

static scr_lifecycle_t screen7_1 = {
    .create = create7_1,
    .entry = entry7_1,
    .exit  = exit7_1,
    .destroy = destroy7_1,
};
#endif
// --------------------- screen 7.2 --------------------- MIC
#if 1
static lv_obj_t *scr7_2_cont;
static lv_obj_t *mic_btn;

static bool recode_sta = false;

static void entry7_2_anim(lv_obj_t *obj) { entry1_anim(obj); }
static void exit7_2_anim(int user_data, lv_obj_t *obj) { exit1_anim(user_data, obj); }

static void mic_start_recode_event(lv_event_t *e)
{
    if(e->code == LV_EVENT_VALUE_CHANGED) {
        if(recode_sta == false) {
            recode_sta = true;
            prompt_info("Start recording", 1000);
        } else {
            recode_sta = false;
            prompt_info("Stop recording", 1000);
        }
    }
}

static void scr7_2_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        exit7_2_anim(SCREEN7_ID, scr7_2_cont);
    }
}

static void create7_2(lv_obj_t *parent) 
{   
    scr7_2_cont = lv_obj_create(parent);
    lv_obj_set_size(scr7_2_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr7_2_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr7_2_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr7_2_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr7_2_cont, 0, LV_PART_MAIN);

    lv_obj_t *mic_info = lv_label_create(scr7_2_cont);
    lv_obj_set_style_text_color(mic_info, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(mic_info, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_obj_set_width(mic_info, LCD_HOR_SIZE);
    lv_label_set_long_mode(mic_info, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_radius(mic_info, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(mic_info, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_pad_hor(mic_info, 3, LV_PART_MAIN);
    lv_obj_set_style_text_align(mic_info, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_align(mic_info, LV_ALIGN_TOP_MID, 0, 40);
    lv_label_set_text(mic_info, "Press \'start\' to record the audio of 10s. No operation "
                                "can be performed during the recording, and the recording is saved to the SD card.");

    mic_btn = lv_btn_create(scr7_2_cont);
    lv_obj_set_size(mic_btn, 80, 40);
    lv_obj_set_style_border_width(mic_btn, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(mic_btn, 0, LV_PART_MAIN);
    lv_obj_remove_style(mic_btn, NULL, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(mic_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(mic_btn, 2, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(mic_btn, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
    lv_obj_align(mic_btn, LV_ALIGN_BOTTOM_MID, 0 , -15);
    lv_obj_t *mic_lab = lv_label_create(mic_btn);
    lv_obj_center(mic_lab);
    lv_obj_set_style_text_color(mic_lab, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(mic_lab, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(mic_lab, "start");
    lv_obj_add_flag(mic_btn, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(mic_btn, mic_start_recode_event, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *label = lv_label_create(scr7_2_cont);
    lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(label, "Microphone");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    // back bottom
    scr_back_btn_create(scr7_2_cont, scr7_2_btn_event_cb);
}
static void entry7_2(void) {
    entry7_2_anim(scr7_2_cont);
}
static void exit7_2(void) {}
static void destroy7_2(void) {}

static scr_lifecycle_t screen7_2 = {
    .create = create7_2,
    .entry = entry7_2,
    .exit  = exit7_2,
    .destroy = destroy7_2,
};
#endif
// --------------------- screen 7.3 --------------------- SD
#if 1
static lv_obj_t *scr7_3_cont;
static lv_obj_t *sd_err_info;
static lv_obj_t *sd_slider;
static lv_obj_t *sd_total;
static lv_obj_t *sd_used;

static bool ui_sd_flag = true;
static int ui_sd_type = 0;



static void entry7_3_anim(lv_obj_t *obj) { entry1_anim(obj); }
static void exit7_3_anim(int user_data, lv_obj_t *obj) { exit1_anim(user_data, obj); }

static void scr7_3_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        exit7_3_anim(SCREEN7_ID, scr7_3_cont);
    }
}

static void create7_3(lv_obj_t *parent) 
{
    scr7_3_cont = lv_obj_create(parent);
    lv_obj_set_size(scr7_3_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr7_3_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr7_3_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr7_3_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr7_3_cont, 0, LV_PART_MAIN);

    sd_err_info = lv_label_create(scr7_3_cont);
    lv_obj_set_width(sd_err_info, LCD_HOR_SIZE * 0.9);
    lv_obj_set_style_text_color(sd_err_info, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(sd_err_info, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_long_mode(sd_err_info, LV_LABEL_LONG_WRAP);


    static lv_style_t style_bg;
    static lv_style_t style_indic;
    lv_style_init(&style_bg);
    lv_style_set_border_color(&style_bg, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON));
    lv_style_set_border_width(&style_bg, 2);
    lv_style_set_pad_all(&style_bg, 6); /*To make the indicator smaller*/
    lv_style_set_radius(&style_bg, 6);
    lv_style_set_anim_time(&style_bg, 1000);
    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON));
    lv_style_set_radius(&style_indic, 3);

    sd_slider = lv_bar_create(scr7_3_cont);
    lv_obj_remove_style_all(sd_slider);  /*To have a clean start*/
    lv_obj_add_style(sd_slider, &style_bg, 0);
    lv_obj_add_style(sd_slider, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(sd_slider, LCD_HOR_SIZE * 0.9, 20);
    lv_obj_center(sd_slider);

    sd_total = lv_label_create(scr7_3_cont);
    lv_obj_set_width(sd_total, LCD_HOR_SIZE * 0.4);
    lv_obj_set_style_text_color(sd_total, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(sd_total, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_long_mode(sd_total, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(sd_total, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_obj_align_to(sd_total, sd_slider, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 5);

    sd_used = lv_label_create(scr7_3_cont);
    lv_obj_set_width(sd_used, LCD_HOR_SIZE * 0.4);
    lv_obj_set_style_text_color(sd_used, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(sd_used, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_long_mode(sd_used, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(sd_used, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_align_to(sd_used, sd_slider, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);


    lv_obj_t *label = lv_label_create(scr7_3_cont);
    lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(label, "TF Card");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    // back bottom
    scr_back_btn_create(scr7_3_cont, scr7_3_btn_event_cb);
}
static void entry7_3(void) {
    entry7_3_anim(scr7_3_cont);

    if(ui_sd_flag) {
        lv_label_set_text(sd_err_info, "SD type: MMC");
        lv_obj_align(sd_err_info, LV_ALIGN_TOP_LEFT, 20, 50);
        lv_label_set_text(sd_total, "32G total");
        lv_label_set_text(sd_used, "256M used");
        lv_bar_set_value(sd_slider, 1, LV_ANIM_ON);

        lv_obj_add_flag(sd_err_info, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_label_set_text(sd_err_info, "No sd card is detected. Insert the sd card and restart the device.");
        lv_obj_center(sd_err_info);

        lv_obj_add_flag(sd_slider, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(sd_total, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(sd_used, LV_OBJ_FLAG_HIDDEN);
    }
}
static void exit7_3(void) {}
static void destroy7_3(void) {}

static scr_lifecycle_t screen7_3 = {
    .create = create7_3,
    .entry = entry7_3,
    .exit  = exit7_3,
    .destroy = destroy7_3,
};
#endif
// --------------------- screen 7 ----------------------- 
#if 1
static lv_obj_t *scr7_cont;
static lv_obj_t *other_list;

static void entry7_anim(lv_obj_t *obj) { entry1_anim(obj); }
static void exit7_anim(int user_data, lv_obj_t *obj) { exit1_anim(user_data, obj); }

static void other_list_event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    int user_data = (int)e->user_data;
    if(code == LV_EVENT_CLICKED) {
        switch (user_data)
        {
            case 0: // Infrared
                scr_mgr_switch(SCREEN7_1_ID, false);
                // prompt_info("  IR underdevelopment", 1000);
                break;
            case 1: // Microphone
                scr_mgr_switch(SCREEN7_2_ID, false);
                // prompt_info("  MIC underdevelopment", 1000);
                break;
            case 2: // TF Card
                scr_mgr_switch(SCREEN7_3_ID, false);
                // prompt_info("  SD underdevelopment", 1000);
                break;
            default:
                break;
        }
    }
}

static void scr7_btn_event_cb(lv_event_t * e)
{
    if(e->code == LV_EVENT_CLICKED){
        // scr_mgr_set_anim(LV_SCR_LOAD_ANIM_FADE_OUT, -1, -1);
        // scr_mgr_switch(SCREEN0_ID, false);
        exit7_anim(SCREEN0_ID, scr7_cont);
    }
}

static void create7(lv_obj_t *parent) 
{
    scr7_cont = lv_obj_create(parent);
    lv_obj_set_size(scr7_cont, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(scr7_cont, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(scr7_cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(scr7_cont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(scr7_cont, 0, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(scr7_cont);
    lv_obj_set_style_text_color(label, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &Font_Mono_Bold_14, LV_PART_MAIN);
    lv_label_set_text(label, "Other device");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    other_list = lv_list_create(scr7_cont);
    lv_obj_set_size(other_list, LV_HOR_RES, 135);
    lv_obj_align(other_list, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(other_list, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
    lv_obj_set_style_pad_row(other_list, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(other_list, 0, LV_PART_MAIN);
    // lv_obj_set_style_outline_pad(other_list, 2, LV_PART_MAIN);
    lv_obj_set_style_border_width(other_list, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(other_list, 0, LV_PART_MAIN);

    lv_obj_t *setting1 = lv_list_add_btn(other_list, NULL, " - Infrared");
    lv_obj_t *setting2 = lv_list_add_btn(other_list, NULL, " - Microphone");
    lv_obj_t *setting3 = lv_list_add_btn(other_list, NULL, " - TF Card");

    for(int i = 0; i < lv_obj_get_child_cnt(other_list); i++) {
        lv_obj_t *item = lv_obj_get_child(other_list, i);
        lv_obj_set_style_text_font(item, &Font_Mono_Bold_14, LV_PART_MAIN);
        lv_obj_set_style_bg_color(item, lv_color_hex(EMBED_PN532_COLOR_FOCUS_ON), LV_STATE_FOCUS_KEY);
        lv_obj_set_style_bg_color(item, lv_color_hex(EMBED_PN532_COLOR_BG), LV_PART_MAIN);
        lv_obj_set_style_text_color(item, lv_color_hex(EMBED_PN532_COLOR_TEXT), LV_PART_MAIN);
        lv_obj_add_event_cb(item, other_list_event, LV_EVENT_CLICKED, (void *)i);
    }

    // back btn
    scr_back_btn_create(scr7_cont, scr7_btn_event_cb);
}
static void entry7(void) { 
    entry7_anim(scr7_cont);
}
static void exit7(void) {   }
static void destroy7(void) { 
}

static scr_lifecycle_t screen7 = {
    .create = create7,
    .entry = entry7,
    .exit  = exit7,
    .destroy = destroy7,
};
#endif
//******************************************************************************
void ui_embed_pn532_entry(void)
{
    // scr_mrg_init();

    // DataModelInit();
    // ScrMgrInit();
    // ScrMgrSwitchScr(GUI_MIAN_SCR_ID, true);
    

    scr_mgr_init();
    scr_mgr_set_bg_color(EMBED_PN532_COLOR_BG);
    scr_mgr_register(SCREEN0_ID, &screen0);
    scr_mgr_register(SCREEN1_ID, &screen1);
    scr_mgr_register(SCREEN2_ID, &screen2);
    scr_mgr_register(SCREEN3_ID, &screen3);
    scr_mgr_register(SCREEN4_ID, &screen4);
    scr_mgr_register(SCREEN5_ID, &screen5);
    scr_mgr_register(SCREEN6_ID, &screen6);
    scr_mgr_register(SCREEN7_ID, &screen7);
    scr_mgr_register(SCREEN7_1_ID, &screen7_1); //   -IR
    scr_mgr_register(SCREEN7_2_ID, &screen7_2); //   -MIC
    scr_mgr_register(SCREEN7_3_ID, &screen7_3); //   -TF Card

    scr_mgr_switch(SCREEN0_ID, false);

    // lv_example_chart_2();

    // lv_timer_create(screen_sw_test_timer_cb, 1000, NULL);

    // lv_example_msg_3();

}

#endif // UI_EMBED_PN532  
