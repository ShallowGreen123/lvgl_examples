/************************************************************************
 * FilePath     : ui_base.h
 * Author       : GX.Duan
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_examples.git
 ************************************************************************/
#ifndef __UI_PORT_EPD47_H__
#define __UI_PORT_EPD47_H__

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
#if UI_EPD47_DISPALY

/*********************************************************************************
 *                                   MACROS
 * *******************************************************************************/

/*********************************************************************************
 *                                  TYPEDEFS
 * *******************************************************************************/

/*********************************************************************************
 *                              GLOBAL PROTOTYPES
 * *******************************************************************************/
void clock_get_time(uint16_t *hour, uint16_t *minute, uint16_t *second);
void clock_get_data(uint16_t *year, uint16_t *month, uint16_t *data, uint16_t *week);

// battery
/* 25896 */
bool battery_25896_is_vaild(void);
bool battery_25896_is_chr(void);
const char * battery_25896_get_VSYS_ST(void);
const char * battery_25896_get_VBUS_ST(void);
const char * battery_25896_get_CHG_ERR(void);
float battery_25896_get_VBUS(void);
float battery_25896_get_VSYS(void);
float battery_25896_get_VBAT(void);
float battery_25896_get_ICHG(void);
float battery_25896_get_TEMP(void);
float battery_25896_get_TSPCT(void);
/* 27220 */
bool battery_27220_is_vaild(void);
bool battery_27220_is_chr(void);
float battery_27220_get_VOLT(void);
float battery_27220_get_VOLT_CHG(void);
float battery_27220_get_CURR_ARG(void);
float battery_27220_get_CURR_INS(void);
float battery_27220_get_CURR_STD(void);
float battery_27220_get_CURR_CHG(void);
float battery_27220_get_TEMP(void);
float battery_27220_get_BATT_CAP(void);
float battery_27220_get_BATT_CAP_FULL(void);

#endif /* UI_EPD47_DISPALY */

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif /* __UI_PORT_EPD47_H__ */
