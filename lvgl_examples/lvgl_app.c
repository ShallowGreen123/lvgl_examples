#include "lvgl_app.h"
#include "ui_base/ui_base.h"
#include "T_EPD47_S3/ui_epd47.h"


/************************************************
 * UI ENTRY
************************************************/
void lvgl_app_init(void)
{
#if UI_BASE_DISPALY
    ui_base_entry();
#elif UI_EPD47_DISPALY
    ui_epd47_entry();
#endif
}
