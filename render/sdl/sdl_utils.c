/**
 * @file sdl_utils.c
 */

#include <SDL2/SDL.h>
#include "sdl_utils.h"
#include "../../utilities/logger.h"

SDL_Window *sdl_create_window(struct render_cfg *cfg)
{
	SDL_Window *window = SDL_CreateWindow("SDL Window",
					      SDL_WINDOWPOS_UNDEFINED,
					      SDL_WINDOWPOS_UNDEFINED, 800, 600,
					      SDL_WINDOW_SHOWN);
	if (window == NULL) {
		log_write(LOG_TAG_ERR,
			  "Window could not be created! SDL Error: ");
		log_write(LOG_TAG_ERR, SDL_GetError());
		return NULL;
	}
	return window;
}
