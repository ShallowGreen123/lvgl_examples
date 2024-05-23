/************************************************************************
 * FilePath     : ui_base.h
 * Author       : GX.Duan
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_examples.git
 ************************************************************************/
#ifndef UI_EMBED_PN532_H
#define UI_EMBED_PN532_H

/*********************************************************************************
 *                                  INCLUDES
 * *******************************************************************************/
#include "../lvgl_app.h"

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************
 *                                   DEFINES
 * *******************************************************************************/
#if UI_EMBED_PN532_DISPALY   
/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/

#define EMBED_PN532_COLOR_BG          0xffffff
#define EMBED_PN532_COLOR_FOCUS_ON    0x91B821
#define EMBED_PN532_COLOR_TEXT        0x161823
#define EMBED_PN532_COLOR_BORDER      0xBBBBBB
#define EMBED_PN532_COLOR_PROMPT_BG   0x1e1e00
#define EMBED_PN532_COLOR_PROMPT_TXT  0xfffee6

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void ui_embed_pn532_entry(void);
#endif // UI_EMBED_PN532_DISPALY 

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* UI_EMBED_PN532_H */
