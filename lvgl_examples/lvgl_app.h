/************************************************************************
 * FilePath     : lvgl_examples.h
 * Author       : GX.Duan
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_examples.git
 ************************************************************************/
#ifndef LV_DEMO_INIT_H
#define LV_DEMO_INIT_H

/*********************************************************************************
 *                                  INCLUDES
 * *******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "lvgl_conf.h"
#include "../lvgl/lvgl.h"
#include "scr_mgr/scr_mrg.h"
#include "scr_mgr/gl_dragable_event.h"

#include "ui_base/assets/assets.h" // Add some fonts
#include "ui_base/assets/lv_i18n.h"

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/


/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/
#if USED_MY_DEMO
    #if UI_BASE_DISPALY
        #define LCD_HOR_SIZE 240
        #define LCD_VER_SIZE 240
    #elif UI_EPD47_DISPALY
        // #define LCD_HOR_SIZE 960
        // #define LCD_VER_SIZE 540
        #define LCD_HOR_SIZE 540
        #define LCD_VER_SIZE 960
    #elif UI_EMBED_PN532_DISPALY 
        #define LCD_HOR_SIZE 320
        #define LCD_VER_SIZE 170
    #elif UI_DECKPRO_DISPALY 
        #define LCD_HOR_SIZE  240
        #define LCD_VER_SIZE  320
    #endif
#else
#define LCD_HOR_SIZE 800
#define LCD_VER_SIZE 600
#endif

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/
enum {
    SCREEN0_ID = 0,
    SCREEN1_ID,
    SCREEN2_ID,
    SCREEN2_1_ID,
    SCREEN2_2_ID,
    SCREEN3_ID,
    SCREEN4_ID,
    SCREEN4_1_ID,
    SCREEN4_2_ID,
    SCREEN5_ID,
    SCREEN6_ID,
    SCREEN7_ID,
    SCREEN7_1_ID,
    SCREEN7_2_ID,
    SCREEN7_3_ID,
    SCREEN8_ID,
    SCREEN9_ID,
    SCREEN10_ID,
};

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void lvgl_app_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_DEMO_INIT_H */
