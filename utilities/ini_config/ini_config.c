/**
 * @file ini_config.c
 */

#include "../ini_config.h"
#include "../defines.h"

/**
 * @brief Open the default config ini file, parse the file and place it in
 *	memory for access.
 * @see inicfg_close
 * @return int - 0 on success 1 on failure
 */
int inicfg_open()
{
	return FUNC_SUCCESS;
}

/**
 * @brief Retrieve the value for the given key in the given section
 *	will point the value parameter to the key value, do not free
 *	the given value pointer.
 * @param section name of section to find key in
 * @param key name of key to get value for
 * @param value pointer to char that will contain the requested value
 * @return int - 0 on success 1 on failure
 */
int inicfg_getstring(char *section, char *key, char *value)
{
	return FUNC_SUCCESS;
}

/**
* @brief Retrieve the value for the given key in the given section
 *	will point the value parameter to the key value, do not free
 *	the given value pointer.
 * @param section name of section to find key in
 * @param key name of key to get value for
 * @param value pointer to int that will contain requested value
 * @return int - 0 on success 1 on failure
 */
int inicfg_getint(char *section, char *key, int *value)
{
	return FUNC_SUCCESS;
}

/**
 * @brief Free memory allocated from opening the default config ini file
 * @see inicfg_open
 * @return int - 0 on success 1 on failure
 */
int inicfg_close()
{
	return FUNC_SUCCESS;
}
