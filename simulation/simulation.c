/**
* @file simulation.c
*/

#include "../utilities/defines.h"
#include "simulation.h"
#include "../utilities/logger.h"

#include <stdio.h>

int sim_init(struct sim_cfg *cfg)
{
	return FUNC_SUCCESS;
}

void *sim_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting simulation thread");
	return NULL;
}
