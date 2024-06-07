#include "lvgl_app.h"
#include "ui_base/ui_base.h"
#include "T_EPD47_S3/ui_epd47.h"
#include "T_Embed_PN532/ui_embed_pn532.h"
#include "T_DeckPro/ui_deckpro.h"


/************************************************
 * UI ENTRY
************************************************/
void lvgl_app_init(void)
{
#if UI_BASE_DISPALY
    ui_base_entry();
#elif UI_EPD47_DISPALY
    ui_epd47_entry();           // https://github.com/Xinyuan-LilyGO/T-EPD47-S3.git
#elif UI_EMBED_PN532_DISPALY 
    ui_embed_pn532_entry();     // https://github.com/Xinyuan-LilyGO/T-Embed-PN532.git
#elif UI_DECKPRO_DISPALY
    ui_deckpro_entry();         //
#endif
}
