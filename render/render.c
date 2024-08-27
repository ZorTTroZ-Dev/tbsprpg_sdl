/**
* @file render.c
*/

#include "render.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"

#include <stdio.h>

/**
 * @brief initialize render subsystem
 * @param cfg pointer to struct render_cfg
 * @return 0 on success 1 on failure
 */
int render_init(struct render_cfg *cfg)
{
	return FUNC_SUCCESS;
}

/**
 * @brief close render subsystem
 */
void render_close()
{
}

/**
 * @brief main method of render subsystem thread
 * @param args void pointer arguments to thread
 * @return void pointer result of thread
 */
void *render_thread(void *args)
{
	log_write(LOG_TAG_INFO, "starting render thread");
	return NULL;
}
