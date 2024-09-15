/**
* @file render_sdl.c
*/

#include "render_sdl.h"
#include "sdl_utils.h"
#include "../../utilities/defines.h"
#include "../../utilities/logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

/**
 * @brief Initialize hardware SDL renderer, create a new window and get its surface
 * @param cfg pointer to render_cfg renderer configuration
 * @return int 0 on success 1 on failure
 */
int render_sdl_init(struct render_cfg *cfg)
{
	window = sdl_create_window(cfg);
	if (!window)
		return FUNC_FAILURE;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		log_write(LOG_TAG_ERR,
			  "Renderer could not be created! SDL Error: ");
		log_write(LOG_TAG_ERR, SDL_GetError());
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

/**
 * @brief Close the hardware SDL renderer
 */
void render_sdl_close()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

/**
 * @brief Render one frame using SDL hardware renderer
 * @param frame pointer to struct render_frame that is the frame to render
 * @param interpolation float how much to interpolate since given frame
 * @return in 0 on success 1 on failure
 */
int render_sdl_frame(struct render_frame *frame, float interpolation)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	return FUNC_SUCCESS;
}
