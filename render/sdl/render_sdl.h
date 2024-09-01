/**
 * @file render_sdl.h
 */

#ifndef RENDER_SDL_H
#define RENDER_SDL_H

#include "../render.h"

extern int render_sdl_init(struct render_cfg *cfg);
extern void render_sdl_close();
extern int render_sdl_frame(struct render_frame *frame, float interpolation);

#endif //RENDER_SDL_H
