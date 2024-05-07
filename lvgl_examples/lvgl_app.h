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
#include "../lvgl/lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/
#define USED_MY_DEMO

//❗❗❗ -------------- Please select one below -------------- ❗❗❗
// #define UI_BASE_DISPALY
#define UI_EPD47_DISPALY 

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/
#ifdef UI_BASE_DISPALY
#define LCD_HOR_SIZE 240
#define LCD_VER_SIZE 240
#elif defined UI_EPD47_DISPALY
#define LCD_HOR_SIZE 960
#define LCD_VER_SIZE 540
#endif

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/
enum {
    SCREEN0_ID = 0,
    SCREEN1_ID,
    SCREEN2_ID,
    SCREEN3_ID,
    SCREEN4_ID,
    SCREEN5_ID,
    SCREEN6_ID,
    SCREEN7_ID,
    SCREEN7_1_ID,
    SCREEN7_2_ID,
    SCREEN7_3_ID,
};

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void lvgl_app_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* LV_DEMO_INIT_H */
