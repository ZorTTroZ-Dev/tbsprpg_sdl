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
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 3

#define SIMULATION_THREAD 0
#define RENDER_THREAD 1
#define AUDIO_THREAD 2

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

	log_write(LOG_TAG_INFO, "launching render thread");
	rval = pthread_create(&threads[RENDER_THREAD], NULL, render_thread,
			      game);
	if (rval != FUNC_SUCCESS) {
		log_write(LOG_TAG_ERR, "failed to create render thread");
		return FUNC_FAILURE;
	}

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
	rcfg.tgt_fps = cfg->render_fps;
	rcfg.core = cfg->render_core;
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
	icfg.tgt_cps = cfg->input_cps;
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

	// start handling events
	input_handle_input(game);

	join_threads();
	log_write(LOG_TAG_INFO, "threads closed");

	close_subsystems();
	log_write(LOG_TAG_INFO, "subsystems closed");

	quit_game(cfg);
	log_write(LOG_TAG_INFO, "game quit");
	return FUNC_SUCCESS;
}
