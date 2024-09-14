/**
* @file render_sdl_sw.h
 */

#ifndef RENDER_SDL_SW_H
#define RENDER_SDL_SW_H

#include "../render.h"

extern int render_sdl_sw_init(struct render_cfg *cfg);
extern void render_sdl_sw_close();
extern int render_sdl_sw_frame(struct render_frame *frame, float interpolation);

#endif //RENDER_SDL_SW_H
