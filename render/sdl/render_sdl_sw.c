/**
* @file render_sdl_sw.c
*/

#include "render_sdl_sw.h"
#include "sdl_utils.h"
#include "../../utilities/defines.h"
#include "../../utilities/logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Surface *window_surface = NULL;
static SDL_Surface *image = NULL;

/**
 * @brief Initialize software SDL renderer, create a new window and get its surface
 * @param cfg pointer to render_cfg renderer configuration
 * @return int 0 on success 1 on failure
 */
int render_sdl_sw_init(struct render_cfg *cfg)
{
	window = sdl_create_window(cfg);
	if (!window)
		return FUNC_FAILURE;

	window_surface = SDL_GetWindowSurface(window);
	if (window_surface == NULL) {
		log_write(LOG_TAG_ERR,
			  "Window surface could not be created! SDL Error: ");
		log_write(LOG_TAG_ERR, SDL_GetError());
		return FUNC_FAILURE;
	}

	SDL_FillRect(window_surface, NULL,
		     SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));

	//Update the surface
	SDL_UpdateWindowSurface(window);

	// just for testing lets load an image and display it.
	// this code will eventually go to an image loading system
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

/**
 * @brief Close the software SDL renderer
 */
void render_sdl_sw_close()
{
	SDL_FreeSurface(image);
	SDL_DestroyWindow(window);
}

/**
 * @brief Render one frame using SDL software renderer
 * @param frame pointer to struct render_frame that is the frame to render
 * @param interpolation float how much to interpolate since given frame
 * @return in 0 on success 1 on failure
 */
int render_sdl_sw_frame(struct render_frame *frame, float interpolation)
{
	SDL_BlitSurface(image, NULL, window_surface, NULL);
	SDL_UpdateWindowSurface(window);
	return FUNC_SUCCESS;
}
