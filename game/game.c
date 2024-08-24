/**
 * @file game.c
 */

#include "game.h"
#include "../utilities/defines.h"
#include "../utilities/threading.h"
#include "../input/input.h"
#include "../utilities/logger.h"
#include "sdl/game_sdl.h"

#include <stdio.h>
#include <string.h>

#define NUM_THREADS 3

#define SIMULATION_THREAD 0
#define RENDER_THREAD 1
#define AUDIO_THREAD 2

static pthread_t threads[NUM_THREADS];

static int launch_threads()
{
	log_write(LOG_TAG_INFO, "launching simulation thread");
	int rval = pthread_create(&threads[SIMULATION_THREAD], NULL, sim_thread,
				  NULL);
	if (rval != FUNC_SUCCESS) {
		log_write(LOG_TAG_ERR, "failed to create simulation thread");
	}

	log_write(LOG_TAG_INFO, "launching render thread");
	rval = pthread_create(&threads[RENDER_THREAD], NULL, render_thread,
			      NULL);
	if (rval != FUNC_SUCCESS) {
		log_write(LOG_TAG_ERR, "failed to create render thread");
	}

	log_write(LOG_TAG_INFO, "launching audio thread");
	rval = pthread_create(&threads[AUDIO_THREAD], NULL, audio_thread, NULL);
	if (rval != FUNC_SUCCESS) {
		log_write(LOG_TAG_ERR, "failed to create audio thread");
	}

	return FUNC_SUCCESS;
}

static int init_render(const struct game_cfg *cfg)
{
	struct render_cfg rcfg;
	rcfg.tgt_fps = cfg->render_fps;
	return render_init(&rcfg);
}

static int init_simulation(const struct game_cfg *cfg)
{
	struct sim_cfg scfg;
	scfg.tgt_cps = cfg->sim_cps;
	return sim_init(&scfg);
}

static int init_audio(const struct game_cfg *cfg)
{
	struct audio_cfg acfg;
	acfg.tgt_cps = cfg->audio_cps;
	return audio_init(&acfg);
}

static int init_input(const struct game_cfg *cfg)
{
	struct input_cfg icfg;
	icfg.tgt_cps = cfg->input_cps;
	return input_init(&icfg);
}

static bool is_sdl(const char *core)
{
	return strcmp(core, GAME_CORE_SDL) == 0;
}

static int init_game(const struct game_cfg *cfg)
{
	if (is_sdl(cfg->core)) {
		return game_sdl_init(cfg);
	}
	return FUNC_FAILURE;
}

static int quit_game(const struct game_cfg *cfg)
{
	if (is_sdl(cfg->core)) {
		return game_sdl_quit();
	}
	return FUNC_FAILURE;
}

int game_start(const struct game_cfg *cfg)
{
	// initialize the game
	log_write(LOG_TAG_INFO, "initializing game");
	init_game(cfg);

	// initialize all of the subsystems
	log_write(LOG_TAG_INFO, "initializing renderer");
	init_render(cfg);
	log_write(LOG_TAG_INFO, "initializing simulation");
	init_simulation(cfg);
	log_write(LOG_TAG_INFO, "initializing audio");
	init_audio(cfg);
	log_write(LOG_TAG_INFO, "initializing input");
	init_input(cfg);

	// start threads
	launch_threads();

	// start handling events

	// wait for everything to end
	pthread_join(threads[SIMULATION_THREAD], NULL);
	pthread_join(threads[RENDER_THREAD], NULL);
	pthread_join(threads[AUDIO_THREAD], NULL);
	log_write(LOG_TAG_INFO, "threads closed");

	log_write(LOG_TAG_INFO, "quiting game");
	quit_game(cfg);

	return FUNC_SUCCESS;
}
