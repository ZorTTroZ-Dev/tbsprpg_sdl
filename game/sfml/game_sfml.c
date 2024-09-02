/**
 * @file game_sfml.c
 */

#include "game_sfml.h"
#include "../../utilities/defines.h"

/**
 * @brief initialize required SFML libraries
 * @param cfg pointer to struct game_cfg
 * @return 0 on success 1 on failure
 */
int game_sfml_init(const struct game_cfg *cfg)
{
	return FUNC_SUCCESS;
}

/**
 * @brief close SFML libraries
 * @return 0 on success 1 on failure
 */
int game_sfml_quit()
{
	return FUNC_SUCCESS;
}
