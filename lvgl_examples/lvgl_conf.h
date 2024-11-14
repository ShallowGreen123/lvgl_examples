

#ifndef LVGL_CONF_H
#define LVGL_CONF_H

/**
 * Set macro USED_MY_DEMO to 0 to enable lv_demo_widgets()
 */
#define USED_MY_DEMO 1 //
#if USED_MY_DEMO

// ❗❗❗ -------------- Please select one below -------------- ❗❗❗
#define UI_BASE_DISPALY        0
#define UI_EPD47_DISPALY       0
#define UI_EMBED_PN532_DISPALY 1
#define UI_DECKPRO_DISPALY     0

// Source path
#if UI_BASE_DISPALY
#define FILE_SYSTEM_PATH "./../lvgl_examples/ui_base/assets"
#elif UI_EPD47_DISPALY
#define FILE_SYSTEM_PATH "./../lvgl_examples/T_EPD47_S3/assets"
#elif UI_EMBED_PN532_DISPALY 
#define FILE_SYSTEM_PATH "./../lvgl_examples/T_Embed_PN532/assets"
#elif UI_DECKPRO_DISPALY
#define FILE_SYSTEM_PATH "./../lvgl_examples/T_DeckPro/assets"
#endif

// Validity judgment
#if (UI_DECKPRO_DISPALY +     \
     UI_EPD47_DISPALY +       \
     UI_EMBED_PN532_DISPALY + \
     UI_BASE_DISPALY) != 1
#error "Please enable one macro that display the LVGL"
#endif

#endif
#endif
