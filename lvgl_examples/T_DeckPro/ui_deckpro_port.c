

#include "ui_deckpro_port.h"

#if UI_DECKPRO_DISPALY

volatile int default_language = DEFAULT_LANGUAGE_EN;

void ui_set_default_language(int language)
{
    default_language = language;
}

// DEFAULT_LANGUAGE_EN
// DEFAULT_LANGUAGE_CN
int ui_get_default_language(void)
{
    return default_language;
}


void ui_disp_full_refr(void)
{
    printf("[disp] ui_disp_full_refr\n");
}


#endif



