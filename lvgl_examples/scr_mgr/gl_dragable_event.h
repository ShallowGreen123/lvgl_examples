/************************************************************************
 * FilePath     : gl_dragable_event.h
 * Author       : GX.Duan
 * LastEditors  : ShallowGreen123 2608653986@qq.com
 * Copyright (c): 2022 by GX.Duan, All Rights Reserved.
 * Github       : https://github.com/ShallowGreen123/lvgl_examples.git
 ************************************************************************/

#ifndef GL_GRAGABLE_EVENT_H
#define GL_GRAGABLE_EVENT_H

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl_app.h"

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void gl_set_dragable(lv_obj_t *obj, lv_anim_ready_cb_t rdy_cb);
bool gl_has_drag_flag(void);
void gl_clear_drag_flag(void);

#endif
