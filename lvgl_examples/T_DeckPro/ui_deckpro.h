/************************************************************************
 * FilePath     : ui_base.h
 * Author       : GX.Duan
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_examples.git
 ************************************************************************/
#ifndef __UI_DECKPRO_H__
#define __UI_DECKPRO_H__

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************
 *                                  INCLUDES
 * *******************************************************************************/
#include "../lvgl_app.h"

/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/
#if UI_DECKPRO_DISPALY

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/
#define DECKPRO_COLOR_BG lv_color_white()
#define DECKPRO_COLOR_FG lv_color_black()

#define UI_WIFI_SCAN_ITEM_MAX 13

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/
typedef void (*ui_indev_read_cb)(int);

struct menu_btn {
    uint16_t idx;
    const void *icon;
    const char *name;
    lv_coord_t pos_x;
    lv_coord_t pos_y; 
};

typedef struct _ui_setting
{
    const char *name;
    lv_obj_t *obj;
    lv_obj_t *st;
    void (*set_cb)(bool);
    bool (*get_cb)(void);
}_ui_setting_handle;

typedef struct _ui_test {
    const char *name;
    bool (*cb)(void);
} ui_test_handle;

typedef struct {
    char name[16];
    int rssi;
}ui_wifi_scan_info_t;

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void ui_deckpro_entry(void);

#endif /* UI_DECKPRO_DISPALY */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*  __UI_DECKPRO_H__*/
