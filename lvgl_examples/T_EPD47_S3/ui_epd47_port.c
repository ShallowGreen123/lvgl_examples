
#if UI_EPD47_DISPALY
#include "ui_epd47_port.h"

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


bool battery_25896_is_chr(void)
{
    return true;
}

bool battery_27220_is_chr(void)
{
    return false;
}

#endif


