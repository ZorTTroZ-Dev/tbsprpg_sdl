/**
 * @file ini_config.c
 */

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "../ini_config.h"
#include "../defines.h"
#include "../logger.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct inicfg_setting {
	char *key;
	char *value;
	struct inicfg_setting *next;
};

struct inicfg_section {
	char *section_name;
	struct inicfg_setting *settings;
	struct inicfg_section *next;
};

static struct inicfg_section *inicfg_config = NULL;

static int parse_config(char *buffer)
{
	bool comment = false;
	for (char *p = buffer; *p != '\0'; *p++) {
		printf("%c", *p);
	}
	return FUNC_SUCCESS;
}

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
		log_write(LOG_TAG_ERR, "failed to open config file");
		return FUNC_FAILURE;
	}

	// read file in to memory
	fseek(cfgfile, 0, SEEK_END);
	const int sz = ftell(cfgfile);
	if (sz == 0)
		goto success_exit;
	fseek(cfgfile, 0, SEEK_SET);
	char *buffer = calloc(1, sz + 1);
	if (buffer == NULL) {
		goto failure_exit;
	}
	const int bytesread = fread(buffer, sizeof(char), sz, cfgfile);
	if (bytesread != sz) {
		goto failure_exit;
	}

	// parse it
	const int result = parse_config(buffer);
	if (result == FUNC_FAILURE) {
		goto failure_exit;
	}

success_exit:
	free(buffer);
	return FUNC_SUCCESS;

failure_exit:
	free(buffer);
	log_write(LOG_TAG_ERR, "failed to read config file");
	return FUNC_FAILURE;
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
