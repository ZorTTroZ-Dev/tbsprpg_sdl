/**
 * @file game_sdl.c
 */

#include "game_sdl.h"
#include "../../utilities/defines.h"
#include "../../utilities/logger.h"

#include <SDL2/SDL.h>
#include <string.h>

/**
 * @brief initialize required SDL libraries
 * @param cfg pointer to struct game_cfg
 * @return 0 on success 1 on failure
 */
int game_sdl_init(const struct game_cfg *cfg)
{
	uint32_t subsystems = 0;
	if (!strcmp(cfg->render_core, SDL_LIBRARY_CORE))
		subsystems = subsystems | SDL_INIT_VIDEO;
	if (!strcmp(cfg->audio_core, SDL_LIBRARY_CORE))
		subsystems = subsystems | SDL_INIT_AUDIO;
	if (!strcmp(cfg->input_core, SDL_LIBRARY_CORE))
		subsystems = subsystems | SDL_INIT_EVENTS;
	if (SDL_Init(subsystems) < 0) {
		log_write(LOG_TAG_ERR, "SDL could not initialize! SDL_Error: ");
		log_write(LOG_TAG_ERR, SDL_GetError());
		return FUNC_FAILURE;
	}
	return FUNC_SUCCESS;
}

/**
 * @brief close SDL libraries
 * @return 0 on success 1 on failure
 */
int game_sdl_quit()
{
	SDL_Quit();
	return FUNC_SUCCESS;
}