/**
* @file render.c
*/

#include "render.h"
#include "sdl/render_sdl.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"
#include "../game/game.h"
#include "../utilities/timing.h"

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
	struct game *game = (struct game *)args;
	uint32_t fps_time = timing_get_time();
	uint32_t cycle = 0;
	float fps = 0;
	const float mspercycle = (float)1000 / tgt_fps;
	while (!game->shutdown) {
		const uint64_t start = timing_get_time();

		// render frame
		switch (core_type) {
		case UNKNOWN_CORE:
			log_write(LOG_TAG_ERR, "render core not properly set");
			game->shutdown = true;
			break;
		case SDL_CORE:
			render_sdl_frame(NULL, 0.0f);
			break;
		default:
			log_write(LOG_TAG_ERR, "unknown render core");
			game->shutdown = true;
			break;
		}

		const uint64_t end = timing_get_time();
		const int64_t sleep = mspercycle - (end - start);
		if (sleep > 0) {
			timing_msleep(sleep);
		}

		// calculate frames per second
		cycle++;
		if (cycle == 100) {
			const uint32_t fps_end_time = timing_get_time();
			fps = cycle / ((fps_end_time - fps_time) / (float)1000);
			fps_time = fps_end_time;
			cycle = 0;
		}
	}
	printf("RENDER FPS: %f\n", fps);
	return NULL;
}
