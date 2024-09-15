/**
 * @file sdl_utils.h
 */

#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include "../render.h"

SDL_Window *sdl_create_window(struct render_cfg *cfg);

#endif //SDL_UTILS_H
