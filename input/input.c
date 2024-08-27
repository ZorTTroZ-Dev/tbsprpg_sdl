/**
* @file input.c
*/

#include "input.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"

#include <stdio.h>

/**
 * @brief initialize input subsystem
 * @param cfg pointer to struct input_cfg
 * @return 0 on success 1 on failure
 */
int input_init(struct input_cfg *cfg)
{
	return FUNC_SUCCESS;
}

/**
 * @brief close input subsystem
 */
void input_close()
{
}

/**
 * @brief loop to poll events from system and update objects in world
 * @return 0 on success 1 on failure
 */
int handle_input()
{
	return FUNC_SUCCESS;
}
