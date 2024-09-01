/**
 * @file input_sdl.c
 */

#include "../../game/game.h"
#include "../../utilities/defines.h"

#include <SDL2/SDL.h>

static SDL_Event event;

/**
 * @brief SDL version of input handling loop
 * @param game pointer to struct game
 * @return 0 on success 1 on failure
 */
int input_sdl_handle_input(struct game *game)
{
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT)
			game->shutdown = true;
	}
	return FUNC_SUCCESS;
}
