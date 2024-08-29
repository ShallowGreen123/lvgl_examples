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
#include "ui_deckpro.h"

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

void ui_disp_full_refr(void);

// [ screen 1 ] --- lora
#define LORA_MODE_SEND 0
#define LORA_MODE_RECV 1
float ui_lora_get_freq(void);
int ui_lora_get_mode(void);
void ui_lora_set_mode(int mode);
void ui_lora_send(const char *str);
bool ui_lora_get_recv(const char **str, int *rssi);
void ui_lora_set_recv_flag(void);

// [ screen 2 ] --- setting
void ui_setting_set_language(int language);
void ui_setting_set_keypad_light(bool on);
void ui_setting_set_motor_status(bool on);
void ui_setting_set_gps_status(bool on);
void ui_setting_set_lora_status(bool on);
void ui_setting_set_gyro_status(bool on);
void ui_setting_set_a7682_status(bool on);

int ui_setting_get_language(void);
bool ui_setting_get_keypad_light(void);
bool ui_setting_get_motor_status(void);
bool ui_setting_get_gps_status(void);  
bool ui_setting_get_lora_status(void); 
bool ui_setting_get_gyro_status(void); 
bool ui_setting_get_a7682_status(void);

// [ screen 3 ] --- GPS
void ui_GPS_print_info(void);
void ui_GPS_get_info(float *lat, float *lon, float *speed, float *alt, float *accuracy,
             int *vsat,  int *usat,  int *year,    int *month, int *day,
             int *hour,  int *min,   int *sec);

// [ screen 4 ] --- Wifi Scan
void ui_wifi_get_scan_info(ui_wifi_scan_info_t *list, int list_len);

// [ screen 5 ] --- Test
bool ui_sd_is_vaild(void);
bool ui_lora_is_vaild(void);
bool ui_keypad_is_vaild(void);
bool ui_bq25896_is_vaild(void);
bool ui_bq27220_is_vaild(void);
bool ui_ltr553_is_vaild(void);

// [ screen 6 ] --- Battery
// BQ25896
bool ui_batt_25896_is_chg(void);
float ui_batt_25896_get_vbus(void);
float ui_batt_25896_get_vsys(void);
float ui_batt_25896_get_vbat(void);
float ui_batt_25896_get_volt_targ(void);
float ui_batt_25896_get_chg_curr(void);
float ui_batt_25896_get_pre_curr(void);
const char * ui_batt_25896_get_chg_st(void);
const char * ui_batt_25896_get_vbus_st(void);
const char * ui_batt_25896_get_ntc_st(void);


#endif /* UI_DECKPOR_DISPALY */
#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif /* __UI_PORT_DECKPOR_H__ */
