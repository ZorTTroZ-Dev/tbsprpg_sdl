/**
* @file render.c
*/

#include "render.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"

#include <stdio.h>

int render_init(struct render_cfg *cfg)
{
	return FUNC_SUCCESS;
}

void *render_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting render thread");
	return NULL;
}
