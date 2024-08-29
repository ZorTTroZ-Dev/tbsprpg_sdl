/**
* @file audio.c
*/

#include "audio.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"

#include <stdio.h>

/**
 * @brief initialize audio subsystem
 * @param cfg pointer to struct audio_cfg
 * @return 0 on success 1 on failure
 */
int audio_init(struct audio_cfg *cfg)
{
	return FUNC_SUCCESS;
}

/**
 * @brief close audio subsystem
 */
void audio_close()
{
}

/**
 * @brief main method of audio subsystem thread
 * @param args void pointer to thread arguemnts
 * @return void pointer of thread result
 */
void *audio_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting audio thread");
	return NULL;
}
