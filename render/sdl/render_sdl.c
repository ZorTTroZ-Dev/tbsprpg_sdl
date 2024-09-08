/**
* @file render_sdl.c
*/

#include "render_sdl.h"
#include "../../utilities/defines.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

int render_sdl_init(struct render_cfg *cfg)
{
	window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, 800, 600,
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

	// just for testing lets load an image and display it.
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not be initialized! SDL_image Error: %s\n",
		       IMG_GetError());
		return FUNC_FAILURE;
	}

	// TEMPORARY CODE
	SDL_Surface *surface = IMG_Load("resources/textures/boom.png");
	if (surface == NULL) {
		printf("Unable to load image! SDL_image Error: %s\n",
		       IMG_GetError());
	}

	//Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		printf("Unable to create texture! SDL Error: %s\n",
		       SDL_GetError());
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surface);

	return FUNC_SUCCESS;
}

void render_sdl_close()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int render_sdl_frame(struct render_frame *frame, float interpolation)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	// SDL_Rect fillRect = { 800 / 4, 600 / 4, 800 / 2, 600 / 2 };
	// SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	// SDL_RenderFillRect(renderer, &fillRect);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	return FUNC_SUCCESS;
}
