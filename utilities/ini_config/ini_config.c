/**
 * @file ini_config.c
 */

#include "../ini_config.h"
#include "../defines.h"

#include <stdio.h>

struct inicfg_setting {
	char *key;
	char *value;
};

struct inicfg_section {
	char *section_name;
	struct inicfg_setting *settings;
};

static struct inicfg_section *inicfg_config = NULL;

/**
 * @brief Open the default config ini file, parse the file and place it in
 *	memory for access.
 * @see inicfg_close
 * @return int - 0 on success 1 on failure
 */
int inicfg_open()
{
	// open the file
	FILE *cfgfile = fopen(INICFG_CONFIG_FILE_PATH, "r");

	// make sure we opened the file properly
	if (cfgfile == NULL) {
		return FUNC_FAILURE;
	}
	// parse the file in to memory
	// return status
	// if parsing fails need to deallocate memory
	return FUNC_SUCCESS;
}

/**
 * @brief Retrieve the value for the given key in the given section
 *	will point the value parameter to the key value, do not free
 *	the given value pointer.
 * @note This implementation is naive you may not want to retreive an ini setting
 *	during gameplay.
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
 * @note This implementation is naive you may not want to retreive an ini setting
 *	during gameplay.
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
