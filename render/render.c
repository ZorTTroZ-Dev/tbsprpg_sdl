/**
* @file render.c
*/

#include "render.h"
#include "sdl/render_sdl.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"

#include <stdio.h>
#include <string.h>

#define UNKNOWN_CORE -1
#define SDL_CORE 0

static int core_type;
static int tgt_fps;

/**
 * @brief initialize render subsystem
 * @param cfg pointer to struct render_cfg
 * @return 0 on success 1 on failure
 */
int render_init(struct render_cfg *cfg)
{
	core_type = UNKNOWN_CORE;
	if (strcmp(cfg->core, SDL_LIBRARY_CORE) == 0) {
		core_type = SDL_CORE;
	}
	tgt_fps = cfg->tgt_fps;

	switch (core_type) {
	case SDL_CORE:
		return render_sdl_init(cfg);
	default:
		return FUNC_FAILURE;
	}
}

/**
 * @brief close render subsystem
 */
void render_close()
{
	switch (core_type) {
	case SDL_CORE:
		render_sdl_close();
		break;
	default:
		break;
	}
}

/**
 * @brief main method of render subsystem thread
 * @param args void pointer arguments to thread
 * @return void pointer result of thread
 */
void *render_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting render thread");
	return NULL;
}
