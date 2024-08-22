/**
 * @file game.c
 */

#include "game.h"
#include "utilities/defines.h"
#include "utilities/threading.h"
#include "render/render.h"

#include <stdint.h>

#define NUM_THREADS 4

#define SIMULATION_THREAD 0
#define RENDER_THREAD 1
#define AUDIO_THREAD 2
#define INPUT_THREAD 3

static pthread_t threads[NUM_THREADS];

static int launch_threads()
{
	return FUNC_SUCCESS;
}

static int init_render(struct game_cfg *cfg)
{
	struct render_cfg rcfg;
	rcfg.tgt_fps = cfg->render_fps;
	return render_init(&rcfg);
}

int game_start(struct game_cfg *cfg)
{
	// initialize all of the subsystems
	init_render(cfg);

	// start threads
	launch_threads();
	return FUNC_SUCCESS;
}
