

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
static int lora_mode = LORA_MODE_SEND;
static float lora_freq = 850.0;

float ui_lora_get_freq(void)
{
    return lora_freq;
}

int ui_lora_get_mode(void)
{
    return lora_mode;
}
void ui_lora_set_mode(int mode)
{
    lora_mode = mode;
}
void ui_lora_send(const char *str)
{
    printf("send-> %s\n", str);
}
bool ui_lora_get_recv(const char **str, int *rssi)
{
    static int data = 0;
    static char buf[32];
    lv_snprintf(buf, 32, "DeckPro #%d", data++);

    *str = buf;
    *rssi = lv_rand(-100, 0);
    return true;
}
void ui_lora_set_recv_flag(void)
{
    
}
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

//************************************[ screen 4 ]****************************************** Wifi Scan
void ui_wifi_get_scan_info(ui_wifi_scan_info_t *list, int list_len)
{
    for(int i = 0; i < list_len; i++)
    {
        printf("list:%d\n", sizeof(*list));
        char buf[16];
        lv_snprintf(buf, 16, "hello#%d", lv_rand(0, 30));
        strncpy(list[i].name, buf, 16);
        list[i].rssi = lv_rand(-120, 0);
    }
}
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

//************************************[ screen 7 ]****************************************** Input
int ui_input_get_touch_coord(int *x, int *y)
{
    *x = lv_rand(0, LCD_HOR_SIZE);
    *y = lv_rand(0, LCD_VER_SIZE);
    return 1;
}
int ui_input_get_keypay_val(int *v)
{
    *v = lv_rand(0, LCD_VER_SIZE);
    return 1;
}

void ui_input_set_keypay_flag(void)
{
    
}

int ui_other_get_LTR(int *ch0, int *ch1, int *ps)
{
    if(ch0 != NULL) *ch0 = lv_rand(0, LCD_VER_SIZE);
    if(ch1 != NULL) *ch1 = lv_rand(0, LCD_VER_SIZE);
    if(ps  != NULL) *ps  = lv_rand(0, LCD_VER_SIZE);
    return 1;
}

int ui_other_get_gyro(float *gyro_x, float *gyro_y, float *gyro_z)
{
    if(gyro_x != NULL) *gyro_x = lv_rand(0, LCD_VER_SIZE);
    if(gyro_y != NULL) *gyro_y = lv_rand(0, LCD_VER_SIZE);
    if(gyro_z != NULL) *gyro_z = lv_rand(0, LCD_VER_SIZE);
    return 1;
}

#endif