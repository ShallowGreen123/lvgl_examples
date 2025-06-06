/************************************************************************
 * FilePath     : ui_base.h
 * Author       : GX.Duan
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_examples.git
 ************************************************************************/
#ifndef __UI_EPD47H__
#define __UI_EPD47H__

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
#if UI_EPD47_DISPALY

#define T5_EPER_S3_SF_VER "v1.0 24.12.03"

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/
#define EPD_COLOR_BG          0xffffff
#define EPD_COLOR_FG          0x000000
#define EPD_COLOR_FOCUS_ON    0x91B821
#define EPD_COLOR_TEXT        0x000000
#define EPD_COLOR_BORDER      0xBBBBBB
#define EPD_COLOR_PROMPT_BG   0x1e1e00
#define EPD_COLOR_PROMPT_TXT  0xfffee6

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/
enum{
    UI_SETTING_TYPE_SW,
    UI_SETTING_TYPE_SUB,
};

typedef struct _ui_setting
{
    const char *name;
    int type;
    void (*set_cb)(int);
    const char* (*get_cb)(int *);
    int sub_id;
    lv_obj_t *obj;
    lv_obj_t *st;
} ui_setting_handle;

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void ui_epd47_entry(void);

#endif /* UI_EPD47_DISPALY */

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif /* __UI_EPD47H__ */
