/**
 * @file game.c
 */

#include "game.h"
#include "utilities/defines.h"
#include "utilities/threading.h"
#include "render/render.h"

#include <stdint.h>

#define MAX_THREADS 4
#define MIN_THREADS 2

#define SIMULATION_THREAD 0
#define RENDER_THREAD 1
#define AUDIO_THREAD 2
#define UTIL_THREAD 3

static pthread_t *threads;

static int launch_threads(uint8_t num_threads)
{
	if (num_threads == 0) {
		num_threads = threading_get_num_procs() - 1;
	}
	if (num_threads > MAX_THREADS)
		num_threads = MAX_THREADS;
	if (num_threads < MIN_THREADS)
		num_threads = MIN_THREADS;

	threads = calloc(num_threads, sizeof(pthread_t));
	if (threads == NULL) {
		return FUNC_FAILURE;
	}

	if (num_threads >= 2) { // create sim and renderer thread
		// int created = pthread_create(&threads[RENDER_THREAD], NULL, )
	}

	if (num_threads >= 3) { // create audio thread
	}

	if (num_threads >= 4) { // create utility thread
	}

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
	launch_threads(cfg->num_threads);
	return FUNC_SUCCESS;
}
