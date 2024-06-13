

#include "ui_deckpro_port.h"

#if UI_DECKPRO_DISPALY

// extern 
volatile int default_language = DEFAULT_LANGUAGE_EN;
volatile int default_keypad_light = false;
volatile int default_motor_status = false;
volatile int default_gps_status = true;
volatile int default_lora_status = true;
volatile int default_gyro_status = true;
volatile int default_a7682_status = true;
// ----

void ui_disp_full_refr(void)
{
    printf("[disp] ui_disp_full_refr\n");
}
//************************************[ screen 0 ]****************************************** menu
//************************************[ screen 1 ]****************************************** lora
//************************************[ screen 2 ]****************************************** setting
// set function

// DEFAULT_LANGUAGE_CN、DEFAULT_LANGUAGE_EN
void ui_setting_set_language(int language)
{
    default_language = language;
}
void ui_setting_set_keypad_light(bool on)
{
    default_keypad_light = on;
}
void ui_setting_set_motor_status(bool on)
{
    default_motor_status = on;
}
void ui_setting_set_gps_status(bool on)
{
    default_gps_status = on;
}
void ui_setting_set_lora_status(bool on)
{
    default_lora_status = on;
}
void ui_setting_set_gyro_status(bool on)
{
    default_gyro_status = on;
}
void ui_setting_set_a7682_status(bool on)
{
    default_a7682_status = on;
}

// get function
int ui_setting_get_language(void)
{
    return default_language;
}
bool ui_setting_get_keypad_light(void)
{
    return default_keypad_light;
}
bool ui_setting_get_motor_status(void)
{
    return default_motor_status;
}
bool ui_setting_get_gps_status(void)
{
    return default_gps_status;
}
bool ui_setting_get_lora_status(void)
{
    return default_lora_status;
}
bool ui_setting_get_gyro_status(void)
{
    return default_gyro_status;
}
bool ui_setting_get_a7682_status(void)
{
    return default_a7682_status;
}
//************************************[ screen 3 ]****************************************** GPS
void ui_GPS_print_info(void)
{

}
void ui_GPS_get_info(float *lat, float *lon, float *speed, float *alt, float *accuracy,
             int *vsat,  int *usat,  int *year,    int *month, int *day,
             int *hour,  int *min,   int *sec)
{
    static int idx = 0;
    *lat      = idx;
    *lon      = idx;
    *speed    = idx;
    *alt      = idx;
    *accuracy = idx;
    *vsat     = idx;
    *usat     = idx;
    *year     = idx;
    *month    = idx;
    *day      = idx;
    *hour     = idx;
    *min      = idx;
    *sec      = idx;
    idx++;
}

//************************************[ screen 4 ]****************************************** SD card
//************************************[ screen 5 ]****************************************** Test
bool ui_sd_is_vaild(void)
{
    return true;
}
bool ui_lora_is_vaild(void)
{
    return false;
}
bool ui_keypad_is_vaild(void)
{
    return false;
}
bool ui_bq25896_is_vaild(void)
{
    return false;
}
bool ui_bq27220_is_vaild(void)
{
    return false;
}
bool ui_ltr553_is_vaild(void)
{
    return false;
}

//************************************[ screen 6 ]****************************************** Battery
// BQ25896
bool ui_batt_25896_is_chg(void)
{
    return true;
}
float ui_batt_25896_get_vbus(void)
{
    return 4.5;
}
float ui_batt_25896_get_vsys(void)
{
    return 4.5;
}
float ui_batt_25896_get_vbat(void)
{
    return 4.5;
}
float ui_batt_25896_get_volt_targ(void)
{
    return 4.5;
}
float ui_batt_25896_get_chg_curr(void)
{
    return 4.5;
}
float ui_batt_25896_get_pre_curr(void)
{
    return 4.5;
}
const char * ui_batt_25896_get_chg_st(void)
{
    return "hello";
}
const char * ui_batt_25896_get_vbus_st(void)
{
    return "hello";
}
const char * ui_batt_25896_get_ntc_st(void)
{
    return "hello";
}

#endif