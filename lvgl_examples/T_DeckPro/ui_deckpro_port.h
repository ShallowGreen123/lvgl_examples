/************************************************************************
 * FilePath     : ui_base.h
 * Author       : GX.Duan
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_examples.git
 ************************************************************************/
#ifndef __UI_PORT_DECKPOR_H__
#define __UI_PORT_DECKPOR_H__

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
#if UI_DECKPRO_DISPALY

// default language
#define DEFAULT_LANGUAGE_EN 0 // English
#define DEFAULT_LANGUAGE_CN 1 // Chinese

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void ui_set_default_language(int language);
int ui_get_default_language(void);


#endif /* UI_DECKPOR_DISPALY */

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif /* __UI_PORT_DECKPOR_H__ */
