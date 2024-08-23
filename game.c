/**
 * @file game.c
 */

#include "game.h"
#include "utilities/defines.h"
// #include "utilities/threading.h"
#include "input/input.h"

#define NUM_THREADS 4

#define SIMULATION_THREAD 0
#define RENDER_THREAD 1
#define AUDIO_THREAD 2
#define INPUT_THREAD 3

// static pthread_t threads[NUM_THREADS];

static int launch_threads()
{
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

int game_start(const struct game_cfg *cfg)
{
	// initialize all of the subsystems
	init_render(cfg);
	init_simulation(cfg);
	init_audio(cfg);
	init_input(cfg);

	// start threads
	launch_threads();

	// wait for everything to end

	return FUNC_SUCCESS;
}
