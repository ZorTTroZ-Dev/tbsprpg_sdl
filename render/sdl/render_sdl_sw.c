/**
* @file render_sdl_sw.c
*/

#include "render_sdl_sw.h"
#include "../../utilities/defines.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Surface *window_surface = NULL;
static SDL_Surface *image = NULL;

int render_sdl_sw_init(struct render_cfg *cfg)
{
	window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, 800, 600,
				  SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL Error: %s\n",
		       SDL_GetError());
		return FUNC_FAILURE;
	}

	window_surface = SDL_GetWindowSurface(window);
	if (window_surface == NULL) {
		printf("Window surface could not be created! SDL Error: %s\n", SDL_GetError());
		return FUNC_FAILURE;
	}

	SDL_FillRect( window_surface, NULL, SDL_MapRGB( window_surface->format, 0xFF, 0xFF, 0xFF ) );

	//Update the surface
	SDL_UpdateWindowSurface( window );

	// just for testing lets load an image and display it.
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not be initialized! SDL_image Error: %s\n",
		       IMG_GetError());
		return FUNC_FAILURE;
	}

	// TEMPORARY CODE
	image = IMG_Load("resources/textures/boom.png");
	if (image == NULL) {
		printf("Unable to load image! SDL_image Error: %s\n",
		       IMG_GetError());
	}

	return FUNC_SUCCESS;
}

void render_sdl_sw_close()
{
	SDL_FreeSurface(image);
	SDL_DestroyWindow(window);
}

int render_sdl_sw_frame(struct render_frame *frame, float interpolation)
{
	SDL_BlitSurface( image, NULL, window_surface, NULL );
	SDL_UpdateWindowSurface( window );
	return FUNC_SUCCESS;
}

