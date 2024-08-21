
#include "ui_esp32p4.h"

#if UI_ESP32_P4_DISPALY

#include <stdio.h>

typedef enum
{
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;

static lv_obj_t *chart1;
static lv_obj_t *chart2;
static lv_obj_t *chart3;
static lv_chart_series_t *ser1;
static lv_chart_series_t *ser2;
static lv_chart_series_t *ser3;
static lv_chart_series_t *ser4;
static lv_style_t style_icon;
static disp_size_t disp_size = DISP_LARGE;
static const lv_font_t *font_normal;

static void color_changer_anim_cb(void *var, int32_t v)
{
    lv_obj_t *obj = var;
    lv_coord_t max_w = lv_obj_get_width(lv_obj_get_parent(obj)) - LV_DPX(20);
    lv_coord_t w;

    if (disp_size == DISP_SMALL)
    {
        w = lv_map(v, 0, 256, LV_DPX(52), max_w);
        lv_obj_set_width(obj, w);
        lv_obj_align(obj, LV_ALIGN_BOTTOM_RIGHT, -LV_DPX(10), -LV_DPX(10));
    }
    else
    {
        w = lv_map(v, 0, 256, LV_DPX(60), max_w);
        lv_obj_set_width(obj, w);
        lv_obj_align(obj, LV_ALIGN_BOTTOM_RIGHT, -LV_DPX(10), -LV_DPX(10));
    }

    if (v > LV_OPA_COVER)
        v = LV_OPA_COVER;

    uint32_t i;
    for (i = 0; i < lv_obj_get_child_cnt(obj); i++)
    {
        lv_obj_set_style_opa(lv_obj_get_child(obj, i), v, 0);
    }
}

static void color_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_FOCUSED)
    {
        lv_obj_t *color_cont = lv_obj_get_parent(obj);
        if (lv_obj_get_width(color_cont) < LV_HOR_RES / 2)
        {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 0, 256);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        }
    }
    else if (code == LV_EVENT_CLICKED)
    {
        lv_palette_t *palette_primary = lv_event_get_user_data(e);
        lv_palette_t palette_secondary = (*palette_primary) + 3; /*Use another palette as secondary*/
        if (palette_secondary >= _LV_PALETTE_LAST)
            palette_secondary = 0;
#if LV_USE_THEME_DEFAULT
        lv_theme_default_init(NULL, lv_palette_main(*palette_primary), lv_palette_main(palette_secondary),
                              LV_THEME_DEFAULT_DARK, font_normal);
#endif
        lv_color_t color = lv_palette_main(*palette_primary);
        lv_style_set_text_color(&style_icon, color);
        lv_chart_set_series_color(chart1, ser1, color);
        lv_chart_set_series_color(chart2, ser3, color);
    }
}

static void color_changer_event_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        lv_obj_t *color_cont = lv_event_get_user_data(e);
        if (lv_obj_get_width(color_cont) < LV_HOR_RES / 2)
        {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 0, 256);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        }
        else
        {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 256, 0);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        }
    }
}

static void color_changer_create(lv_obj_t *parent)
{
    static lv_palette_t palette[] = {
        LV_PALETTE_BLUE, LV_PALETTE_GREEN, LV_PALETTE_BLUE_GREY, LV_PALETTE_ORANGE,
        LV_PALETTE_RED, LV_PALETTE_PURPLE, LV_PALETTE_TEAL, _LV_PALETTE_LAST};

    lv_obj_t *color_cont = lv_obj_create(parent);
    lv_obj_remove_style_all(color_cont);
    lv_obj_set_flex_flow(color_cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(color_cont, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(color_cont, LV_OBJ_FLAG_FLOATING);

    lv_obj_set_style_bg_color(color_cont, lv_color_white(), 0);
    lv_obj_set_style_pad_right(color_cont, disp_size == DISP_SMALL ? LV_DPX(47) : LV_DPX(55), 0);
    lv_obj_set_style_bg_opa(color_cont, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(color_cont, LV_RADIUS_CIRCLE, 0);

    if (disp_size == DISP_SMALL)
        lv_obj_set_size(color_cont, LV_DPX(52), LV_DPX(52));
    else
        lv_obj_set_size(color_cont, LV_DPX(60), LV_DPX(60));

    lv_obj_align(color_cont, LV_ALIGN_BOTTOM_RIGHT, -LV_DPX(10), -LV_DPX(10));

    uint32_t i;
    for (i = 0; palette[i] != _LV_PALETTE_LAST; i++)
    {
        lv_obj_t *c = lv_btn_create(color_cont);
        lv_obj_set_style_bg_color(c, lv_palette_main(palette[i]), 0);
        lv_obj_set_style_radius(c, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_opa(c, LV_OPA_TRANSP, 0);
        lv_obj_set_size(c, 20, 20);
        // lv_obj_add_event_cb(c, color_event_cb, LV_EVENT_ALL, &palette[i]);
        lv_obj_clear_flag(c, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    }

    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(btn, lv_color_white(), LV_STATE_CHECKED);
    lv_obj_set_style_pad_all(btn, 10, 0);
    lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_add_event_cb(btn, color_changer_event_cb, LV_EVENT_ALL, color_cont);
    lv_obj_set_style_shadow_width(btn, 0, 0);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_TINT, 0);

    if (disp_size == DISP_SMALL)
    {
        lv_obj_set_size(btn, LV_DPX(42), LV_DPX(42));
        lv_obj_align(btn, LV_ALIGN_BOTTOM_RIGHT, -LV_DPX(15), -LV_DPX(15));
    }
    else
    {
        lv_obj_set_size(btn, LV_DPX(50), LV_DPX(50));
        lv_obj_align(btn, LV_ALIGN_BOTTOM_RIGHT, -LV_DPX(15), -LV_DPX(15));
    }
}

// *****************************************************************************

lv_obj_t *hover_btn;
bool hover_cont_is_open = false;

void Hover_btn_anim(lv_anim_t *a)
{
    lv_coord_t x = lv_obj_get_x(hover_btn);
    lv_coord_t y = lv_obj_get_y(hover_btn);

    if (!gl_has_drag_flag())
    {
        printf("Hover x=%d, y=%d\n", x, y);
    }
}

static void hover_cont_anim_cb(void *var, int32_t v)
{
    lv_obj_t *obj = var;
    lv_coord_t max_w = lv_obj_get_width(lv_obj_get_parent(obj)) - LV_DPX(20);
    lv_coord_t h;
    lv_coord_t hover_cont_max_h = LV_VER_RES - LV_DPX(400);

    lv_coord_t x = lv_obj_get_x(hover_btn);
    lv_coord_t y = lv_obj_get_y(hover_btn);

    h = lv_map(v, 0, 256, LV_DPX(52), hover_cont_max_h);
    lv_obj_set_height(obj, h);
    lv_obj_align_to(obj, hover_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, -LV_DPX(50));
}

static void hover_hidden_time(lv_timer_t *t)
{
    lv_obj_add_flag((lv_obj_t *)t->user_data, LV_OBJ_FLAG_HIDDEN);
    lv_timer_del(t);
}

static void hover_btn_event(lv_event_t *e)
{
    if (e->code == LV_EVENT_CLICKED && gl_has_drag_flag() == false)
    {
        lv_obj_t *hover_cont = lv_event_get_user_data(e);

        if (hover_cont_is_open == false)
        {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, hover_cont);
            lv_anim_set_exec_cb(&a, hover_cont_anim_cb);
            lv_anim_set_values(&a, 0, 256);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
            lv_obj_clear_flag(hover_cont, LV_OBJ_FLAG_HIDDEN);
            hover_cont_is_open = true;
            gl_disable_drag(hover_cont_is_open);
        }
        else
        {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, hover_cont);
            lv_anim_set_exec_cb(&a, hover_cont_anim_cb);
            lv_anim_set_values(&a, 256, 0);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
            lv_timer_create(hover_hidden_time, 210, e->user_data);
            hover_cont_is_open = false;
            gl_disable_drag(hover_cont_is_open);
        }
    }
}

lv_obj_t *hover_create(lv_obj_t *parent)
{
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_remove_style_all(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(cont, LV_OBJ_FLAG_FLOATING);
    lv_obj_add_flag(cont, LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_bg_color(cont, lv_color_black(), 0);
    lv_obj_set_style_pad_right(cont, disp_size == DISP_SMALL ? LV_DPX(47) : LV_DPX(55), 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0);

    if (disp_size == DISP_SMALL)
        lv_obj_set_size(cont, LV_DPX(52), LV_DPX(52));
    else
        lv_obj_set_size(cont, LV_DPX(60), LV_DPX(60));

    lv_obj_align(cont, LV_ALIGN_BOTTOM_RIGHT, -LV_DPX(10), -LV_DPX(10));

    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(btn, lv_color_white(), LV_STATE_CHECKED);
    lv_obj_set_style_pad_all(btn, 10, 0);
    lv_obj_set_style_radius(btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_add_event_cb(btn, hover_btn_event, LV_EVENT_ALL, cont);
    lv_obj_set_style_shadow_width(btn, 0, 0);
    lv_obj_set_style_bg_img_src(btn, LV_SYMBOL_TINT, 0);

    lv_obj_set_size(btn, LV_DPX(50), LV_DPX(50));

    lv_obj_align_to(cont, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, -LV_DPX(55));

    gl_set_dragable(btn, Hover_btn_anim);

    return btn;
}

void ui_esp32p4_entry(void)
{
    hover_btn = hover_create(lv_scr_act());
}
#endif
