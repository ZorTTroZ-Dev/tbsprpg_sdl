/**
* @file render_sdl.c
*/

#include "render_sdl.h"
#include "../../utilities/defines.h"
#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

int render_sdl_init(struct render_cfg *cfg)
{
	window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, 640, 480,
				  SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL Error: %s\n",
		       SDL_GetError());
		return FUNC_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n",
		       SDL_GetError());
		return FUNC_FAILURE;
	}
	return FUNC_SUCCESS;
}

void render_sdl_close()
{
	SDL_DestroyWindow(window);
}

int render_sdl_frame(struct render_frame *frame, float interpolation)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_Rect fillRect = { 640 / 4, 480 / 4, 640 / 2, 480 / 2 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &fillRect);
	SDL_RenderPresent(renderer);
	return FUNC_SUCCESS;
}
