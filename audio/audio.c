/**
* @file audio.c
*/

#include "audio.h"
#include "sdl/audio_sdl.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"

#include <stdio.h>
#include <string.h>

#define UNKNOWN_CORE -1
#define SDL_CORE 0

static int core_type;

/**
 * @brief initialize audio subsystem
 * @param cfg pointer to struct audio_cfg
 * @return 0 on success 1 on failure
 */
int audio_init(struct audio_cfg *cfg)
{
	core_type = UNKNOWN_CORE;
	if (strcmp(cfg->core, SDL_LIBRARY_CORE) == 0) {
		core_type = SDL_CORE;
	}

	switch (core_type) {
	case SDL_CORE:
		return audio_sdl_init(cfg);
	default:
		return FUNC_FAILURE;
	}
}

/**
 * @brief close audio subsystem
 */
void audio_close()
{
	switch (core_type) {
	case SDL_CORE:
		audio_sdl_close();
		break;
	default:
		break;
	}
}

/**
 * @brief main method of audio subsystem thread
 * @param args void pointer to thread arguments
 * @return void pointer of thread result
 */
void *audio_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting audio thread");
	return NULL;
}
