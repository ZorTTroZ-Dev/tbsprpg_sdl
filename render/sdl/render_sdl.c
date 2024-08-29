/**
* @file render_sdl.c
*/

#include "render_sdl.h"
#include "../../utilities/defines.h"
#include <SDL.h>
#include <stdio.h>

static SDL_Window *window = NULL;

int render_sdl_init(struct render_cfg *cfg)
{
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, 640, 480,
				  SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL Error: %s\n",
		       SDL_GetError());
		return FUNC_FAILURE;
	}
	return FUNC_SUCCESS;
}

void render_sdl_close()
{
	SDL_DestroyWindow(window);
}
