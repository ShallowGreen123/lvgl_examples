

#include "ui_epd47_port.h"

#if UI_EPD47_DISPALY

void clock_get_time(uint16_t *hour, uint16_t *minute, uint16_t *second)
{
    if(hour) *hour = 10;
    if(minute) *minute = 19;
    if(second) *second = 50;
}

void clock_get_data(uint16_t *year, uint16_t *month, uint16_t *data, uint16_t *week)
{
    if(year) *year = 2024;
    if(month) *month = 5;
    if(data) *data = 24;
    if(week) *week = 4;     // 0-6  
}


//************************************[ screen 5 ]****************************************** battery
/* 25896 */
bool battery_25896_is_vaild(void)
{
    return true;
}

bool battery_25896_is_chr(void)
{
    return false;
}

char * battery_25896_get_VSYS_ST(void)
{
    return "Nomal";
}
char * battery_25896_get_VBUS_ST(void) 
{
    return "Nomal";
}
char * battery_25896_get_CHG_ERR(void)
{
    return "Nomal";
}
float battery_25896_get_VBUS(void)
{
    static float vsys = 0;
    vsys+=0.1;
    return 4.23+vsys;
}
float battery_25896_get_VSYS(void) 
{
    static float vsys = 0;
    vsys+=0.2;
    return 4.23+vsys;
}
float battery_25896_get_VBAT(void)
{
    static float vsys = 0;
    vsys+=0.3;
    return 4.23+vsys;
}
float battery_25896_get_ICHG(void)
{
    static float vsys = 0;
    vsys+=0.4;
    return 4.23+vsys;
}
float battery_25896_get_TEMP(void)
{
    static float vsys = 0;
    vsys+=0.5;
    return 4.23+vsys;
}
float battery_25896_get_TSPCT(void)
{
    static float vsys = 0;
    vsys=0.6;
    return 4.23+vsys;
}


/* 27220 */
bool battery_27220_is_vaild(void)
{
    return true;
}

bool battery_27220_is_chr(void)
{
    return false;
}

float battery_27220_get_VOLT(void)
{
    static float vsys = 0;
    vsys+=0.01;
    return 4.23+vsys;
}
float battery_27220_get_VOLT_CHG(void)
{
    static float vsys = 0;
    vsys+=0.02;
    return 4.23+vsys;
}
float battery_27220_get_CURR_ARG(void)
{
    static float vsys = 0;
    vsys+=0.03;
    return 4.23+vsys;
}
float battery_27220_get_CURR_INS(void)
{
    static float vsys = 0;
    vsys+=0.04;
    return 4.23+vsys;
}
float battery_27220_get_CURR_STD(void)
{
    static float vsys = 0;
    vsys+=0.05;
    return 4.23+vsys;
}
float battery_27220_get_CURR_CHG(void)
{
    static float vsys = 0;
    vsys+=0.06;
    return 4.23+vsys;
}
float battery_27220_get_TEMP(void)
{
    static float vsys = 0;
    vsys+=0.07;
    return 4.23+vsys;
}
float battery_27220_get_BATT_CAP(void)
{
    static float vsys = 0;
    vsys+=0.08;
    return 4.23+vsys;
}
float battery_27220_get_BATT_CAP_FULL(void)
{
    static float vsys = 0;
    vsys+=0.09;
    return 4.23+vsys;
}


#endif


