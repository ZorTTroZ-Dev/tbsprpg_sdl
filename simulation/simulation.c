/**
* @file simulation.c
*/

#include "../utilities/defines.h"
#include "simulation.h"
#include "../utilities/logger.h"

#include <stdio.h>

/**
 * @brief initialize simulation subsystem
 * @param cfg pointer to sruct sim_cfg
 * @return 0 on success 1 on failure
 */
int sim_init(struct sim_cfg *cfg)
{
	return FUNC_SUCCESS;
}

/**
 * @brief close simulation subsystem
 */
void sim_close()
{
}

/**
 * @brief main method of simulation subsystem thread
 * @param args void pointer arguements to simulation thread
 * @return void pointer to result of simulation thread
 */
void *sim_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting simulation thread");
	return NULL;
}
