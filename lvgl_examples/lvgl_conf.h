

#ifndef LVGL_CONF_H
#define LVGL_CONF_H

/**
 * Set macro USED_MY_DEMO to 0 to enable lv_demo_widgets()
*/
#define USED_MY_DEMO  1 // 
#if USED_MY_DEMO

//❗❗❗ -------------- Please select one below -------------- ❗❗❗
#define UI_BASE_DISPALY    0
#define UI_EPD47_DISPALY   0
#define UI_EMBED_PN532     1



//
#if (UI_BASE_DISPALY+UI_EPD47_DISPALY+UI_EMBED_PN532) != 1
#error "Please enable one macro that display the LVGL"
#endif

#endif
#endif
