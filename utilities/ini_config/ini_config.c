/**
 * @file ini_config.c
 */

#include "../ini_config.h"
#include "../defines.h"

/**
 * @brief Open the default config ini file, parse the file and place it in
 *	memory for access.
 * @see inicfg_close()
 * @return int - 0 on success 1 on failure
 */
int inicfg_open()
{
	return FUNC_SUCCESS;
}

/**
 * @brief Free memory allocated from opening the default config ini file
 * @see inicfg_open()
 * @return int - 0 on success 1 on failure
 */
int inicfg_close()
{
	return FUNC_SUCCESS;
}
