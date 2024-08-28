/**
* @file input.c
*/

#include "input.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"
#include "sdl/input_sdl.h"

#include <string.h>

#define UNKNOWN_CORE -1
#define SDL_CORE 0

static int core_type;
static int tgt_cps;

/**
 * @brief initialize input subsystem
 * @param cfg pointer to struct input_cfg
 * @return 0 on success 1 on failure
 */
int input_init(struct input_cfg *cfg)
{
	core_type = UNKNOWN_CORE;
	if (strcmp(cfg->core, SDL_LIBRARY_CORE) == 0) {
		core_type = SDL_CORE;
	}
	tgt_cps = cfg->tgt_cps;
	return FUNC_SUCCESS;
}

/**
 * @brief close input subsystem
 */
void input_close()
{
}

/**
 * @brief loop to poll events from system and update objects in world
 * @param game pointer to struct game
 * @return 0 on success 1 on failure
 */
int input_handle_input(struct game *game)
{
	switch (core_type) {
	case UNKNOWN_CORE:
		log_write(LOG_TAG_ERR, "input core not properly set");
		return FUNC_FAILURE;
	case SDL_CORE:
		return input_sdl_handle_input(game, tgt_cps);
	default:
		log_write(LOG_TAG_ERR, "unknown input core");
		return FUNC_FAILURE;
	}
}
