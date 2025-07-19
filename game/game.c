/**
 * @file game.c
 */

#include "game.h"
#include "../utilities/defines.h"
#include "../utilities/threading.h"
#include "../input/input.h"
#include "../utilities/logger.h"
#include "../utilities/timing.h"
#include "sdl/game_sdl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 3

#define SIMULATION_THREAD 0
#define AUDIO_THREAD 1

static pthread_t threads[NUM_THREADS]; //!< array of threads in game

struct game *game; //!< game state

/**
 * @brief Launch all subsystem threads and call their appropriate start methods
 * @return return 0 on success 1 on failure
 */
static int launch_threads()
{
	log_write(LOG_TAG_INFO, "launching simulation thread");
	int rval = pthread_create(&threads[SIMULATION_THREAD], NULL, sim_thread,
				  game);
	if (rval != FUNC_SUCCESS) {
		log_write(LOG_TAG_ERR, "failed to create simulation thread");
		return FUNC_FAILURE;
	}

	// TODO add thread for resource management

	log_write(LOG_TAG_INFO, "launching audio thread");
	rval = pthread_create(&threads[AUDIO_THREAD], NULL, audio_thread, game);
	if (rval != FUNC_SUCCESS) {
		log_write(LOG_TAG_ERR, "failed to create audio thread");
		return FUNC_FAILURE;
	}

	return FUNC_SUCCESS;
}

/**
 * @brief initialize the render subsystem
 * @param cfg pointer to struct game_cfg
 * @return return 0 on success 1 on failure
 */
static int init_render(const struct game_cfg *cfg)
{
	struct render_cfg rcfg;
	rcfg.core = cfg->render_core;
	rcfg.renderer = cfg->render_renderer;
	return render_init(&rcfg);
}

/**
 * @brief initialize the simulation subsystem
 * @param cfg pointer to struct game_cfg
 * @return return 0 on success 1 on failure
 */
static int init_simulation(const struct game_cfg *cfg)
{
	struct sim_cfg scfg;
	scfg.tgt_cps = cfg->sim_cps;
	return sim_init(&scfg);
}

/**
 * @brief initialize the audio subsystem
 * @param cfg pointer to struct game_cfg
 * @return return 0 on success 1 on failure
 */
static int init_audio(const struct game_cfg *cfg)
{
	struct audio_cfg acfg;
	acfg.tgt_cps = cfg->audio_cps;
	acfg.core = cfg->audio_core;
	return audio_init(&acfg);
}

/**
 * @brief initialize the input subsystem
 * @param cfg pointer to struct game_cfg
 * @return return 0 on success 1 on failure
 */
static int init_input(const struct game_cfg *cfg)
{
	struct input_cfg icfg;
	icfg.core = cfg->input_core;
	return input_init(&icfg);
}

/**
 * @brief check if the given core is SDL
 * @param core pointer to char name of core
 * @return results of strcmp to see if core is SDL
 */
static bool is_sdl(const char *core)
{
	return strcmp(core, SDL_LIBRARY_CORE) == 0;
}

/**
 * @brief initialize the game
 * @param cfg pointer to struct game_cfg
 * @return 0 on success 1 on failure
 */
static int init_game(const struct game_cfg *cfg)
{
	game = malloc(sizeof(struct game));
	if (game == NULL) {
		return FUNC_FAILURE;
	}
	game->shutdown = false;
	if (is_sdl(cfg->core)) {
		return game_sdl_init(cfg);
	}
	return FUNC_FAILURE;
}

/**
 * @brief clean up game for shutdown
 * @param cfg pointer to struct game_cfg
 * @return 0 on success 1 on failure
 */
static int quit_game(const struct game_cfg *cfg)
{
	if (game != NULL)
		free(game);
	if (is_sdl(cfg->core)) {
		return game_sdl_quit();
	}
	return FUNC_FAILURE;
}

/**
 * @brief initialze the thread array to known values
 */
static void init_threads()
{
	for (int i = 0; i < NUM_THREADS; i++) {
#ifdef _WIN32
		threads[i] = NULL;
#else
		threads[i] = 0;
#endif
	}
}

/**
 * @brief join any valid threads that have been created
 */
static void join_threads()
{
	for (int i = 0; i < NUM_THREADS; i++) {
#ifdef _WIN32
		if (threads[i] != NULL)
			pthread_join(threads[i], NULL);
#else
		if (threads[i] != 0)
			pthread_join(threads[i], NULL);
#endif
	}
}

/**
 * @brief close any open subsystems
 */
static void close_subsystems()
{
	render_close();
	sim_close();
	audio_close();
	input_close();
}

/**
 * @brief initialize all of the subsystems
 * @param cfg pointer to struct game_cfg
 * @return 0 on success 1 on failure
 */
static int init_subsystems(const struct game_cfg *cfg)
{
	log_write(LOG_TAG_INFO, "initializing renderer");
	int result = init_render(cfg);
	if (result != FUNC_SUCCESS)
		goto func_failure;

	log_write(LOG_TAG_INFO, "initializing simulation");
	result = init_simulation(cfg);
	if (result != FUNC_SUCCESS)
		goto func_failure;

	log_write(LOG_TAG_INFO, "initializing audio");
	result = init_audio(cfg);
	if (result != FUNC_SUCCESS)
		goto func_failure;

	log_write(LOG_TAG_INFO, "initializing input");
	result = init_input(cfg);
	if (result != FUNC_SUCCESS)
		goto func_failure;

	return FUNC_SUCCESS;
func_failure:
	log_write(LOG_TAG_INFO, "subsystem initialization failed");
	close_subsystems();
	return FUNC_FAILURE;
}

/**
 * @brief main game loop handle input and rendering
 * @param tgt_fps uint8_t target frames per second in loop
 */
static void loop(uint8_t tgt_fps)
{
	int result = 0;
	uint32_t fps_time = timing_get_time();
	uint32_t cycle = 0;
	float fps = 0;
	const float mspercycle = (float)1000 / tgt_fps;
	while (!game->shutdown) {
		const uint64_t start = timing_get_time();

		// DO STUFF
		result = input_handle_input(game); // handle events
		if (result == FUNC_FAILURE) {
			game->shutdown = true;
		}
		result = render_render_frames(game->frames); // render frames
		if (result == FUNC_FAILURE) {
			game->shutdown = true;
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
	printf("RENDER/INPUT FPS: %f\n", fps);
}

/**
 * @brief start the game, initialize all of the subsystems, launch threads and handle input
 * @param cfg pointer to struct game_cfg
 * @return 0 on success 1 on failure
 */
int game_start(const struct game_cfg *cfg)
{
	init_threads();

	log_write(LOG_TAG_INFO, "initializing game");
	if (init_game(cfg) != FUNC_SUCCESS) {
		log_write(LOG_TAG_ERR, "game initialization failed");
		if (game != NULL)
			free(game);
		return FUNC_FAILURE;
	}

	if (init_subsystems(cfg) != FUNC_SUCCESS) {
		quit_game(cfg);
		return FUNC_FAILURE;
	}

	// start threads
	if (launch_threads() != FUNC_SUCCESS) {
		quit_game(cfg);
		close_subsystems();
		join_threads();
		return FUNC_FAILURE;
	}

	loop(cfg->game_fps);

	join_threads();
	log_write(LOG_TAG_INFO, "threads closed");

	close_subsystems();
	log_write(LOG_TAG_INFO, "subsystems closed");

	quit_game(cfg);
	log_write(LOG_TAG_INFO, "game quit");
	return FUNC_SUCCESS;
}
