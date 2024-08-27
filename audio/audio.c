/**
* @file audio.c
*/

#include "audio.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"

#include <stdio.h>

int audio_init(struct audio_cfg *cfg)
{
	return FUNC_SUCCESS;
}

void audio_close()
{
}

void *audio_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting audio thread");
	return NULL;
}
