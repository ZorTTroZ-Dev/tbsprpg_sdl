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
#include <ctype.h>
#include <string.h>

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
	bool section = false;
	// bool setting = false;

	struct inicfg_section *cursection = NULL;
	char *token = NULL;
	int token_len = 0;

	for (char *p = buffer; *p != '\0'; *p++) {
		if (*p == '[') {
			section = true;
			continue;
		}
		if (*p == '#') {
			comment = true;
			continue;
		}

		if (comment && *p == '\n') {
			comment = false;
			token = NULL;
			token_len = 0;
			continue;
		}

		if (section && *p == ']' && token != NULL && token_len > 0) {
			char *section_name = calloc(1, token_len);
			if (section_name == NULL) {
				free(section_name);
				goto parse_failure_exit;
			}
			memcpy(section_name, token, token_len);
			struct inicfg_section *newsection =
				malloc(sizeof(struct inicfg_section));
			if (newsection == NULL) {
				free(newsection);
				goto parse_failure_exit;
			}
			newsection->section_name = section_name;
			newsection->settings = NULL;
			newsection->next = cursection;
			cursection = newsection;
			section = false;
			token = NULL;
			token_len = 0;
			continue;
		}

		if (*p != '\n' && *(p + 1) != '\0') {
			if (token == NULL) {
				token = p;
				token_len = 1;
			} else {
				token_len++;
			}
		} else if (*(p + 1) == '\0') {
			if (token == NULL) {
				token = p;
				token_len = 1;
			} else {
				token_len++;
			}
			token = NULL;
			token_len = 0;
			printf("token contains key/value\n");
		} else if (*p == '\n' && cursection != NULL && token_len > 0) {
			// TODO: make sure contains equal sign
			//	set key set value add setting to the section
			token = NULL;
			token_len = 0;
			printf("token contains key/value\n");
		}
	}

parse_success_exit:
	return FUNC_SUCCESS;
parse_failure_exit:
	// TODO: Walk section list free memory
	return FUNC_FAILURE;
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
