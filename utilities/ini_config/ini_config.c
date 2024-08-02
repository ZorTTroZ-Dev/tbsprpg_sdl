/**
 * @file ini_config.c
 */

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "../ini_config.h"
#include "../defines.h"
#include "../logger.h"
#include "../strutils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct inicfg_setting {
	char *key;
	char *trimmed_key;
	char *value;
	char *trimmed_value;
	struct inicfg_setting *next;
};

struct inicfg_section {
	char *section_name;
	struct inicfg_setting *settings;
	struct inicfg_section *next;
};

static struct inicfg_section *inicfg_config = NULL;

/**
 * @brief Create a new section
 * @param sectionname char pointer new section name
 * @param namelen int length of section name
 * @return return pointer to new section or NULL on failure
 */
static struct inicfg_section *new_section(const char *sectionname, int namelen)
{
	char *section_name = calloc(namelen + 1, 1);
	if (section_name == NULL) {
		free(section_name);
		return NULL;
	}
	memcpy(section_name, sectionname, namelen);
	*(section_name + namelen) = '\0';
	struct inicfg_section *newsection =
		malloc(sizeof(struct inicfg_section));
	if (newsection == NULL) {
		free(section_name);
		free(newsection);
		return NULL;
	}
	newsection->section_name = section_name;
	newsection->settings = NULL;
	newsection->next = NULL;
	return newsection;
}

/**
 * @brief Parse then create new setting
 * @param settingstr char pointer of string representing setting
 * @param len int length of setting string
 * @return pointer to allocated setting struct or NULL on failure
 */
static struct inicfg_setting *new_setting(const char *settingstr, int len)
{
	char *buffer = calloc(len + 1, 1);
	memcpy(buffer, settingstr, len);
	buffer[len] = '\0';

	char *eqsn = strchr(buffer, '=');
	if (eqsn == NULL) {
		free(buffer);
		return NULL; // malformed setting no equal sign
	}

	int idx = eqsn - buffer;

	char *key = calloc(idx + 1, 1);
	if (key == NULL) {
		free(buffer);
		free(key);
		return NULL;
	}
	memcpy(key, buffer, idx);

	char *val = calloc(len - idx, 1);
	if (val == NULL) {
		free(buffer);
		free(key);
		free(val);
		return NULL;
	}
	memcpy(val, eqsn + 1, len - idx - 1);

	struct inicfg_setting *setting = malloc(sizeof(struct inicfg_setting));
	setting->key = key;
	setting->trimmed_key = strtrim(key);
	setting->value = val;
	setting->trimmed_value = strtrim(val);
	setting->next = NULL;

	free(buffer);

	return setting;
}

/**
 * @brief Free the allocated memory for the given setting
 * @param setting setting to free memory of
 */
static void free_setting(struct inicfg_setting *setting)
{
	while (setting != NULL) {
		free(setting->key);
		setting->key = NULL;
		free(setting->value);
		setting->value = NULL;
		struct inicfg_setting *ns = setting->next;
		free(setting);
		setting = ns;
	}
}

/**
 * @brief Free the allocated memory for the given section
 * @param section section to free memory of
 */
static void free_section(struct inicfg_section *section)
{
	while (section != NULL) {
		free(section->section_name);
		section->section_name = NULL;
		free_setting(section->settings);
		struct inicfg_section *ns = section->next;
		free(section);
		section = ns;
	}
}

/**
 * @brief Parse the contents of the buffer build ini file model in memory
 * @param buffer pointer to char of contents to parse
 * @return return 0 on success 1 on failure
 */
static int parse_config(char *buffer)
{
	bool comment = false;
	bool section = false;
	bool closetoken = false;
	bool tokenize = false;
	bool setting = false;

	struct inicfg_section *cursection = NULL;
	char *token = NULL;
	int token_len = 0;

	// TODO: Refactor
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
			struct inicfg_section *newsection =
				new_section(token, token_len);
			if (newsection == NULL)
				goto parse_failure_exit;
			newsection->next = cursection;
			cursection = newsection;
			section = false;
			token = NULL;
			token_len = 0;
			continue;
		}

		if (*p != '\n' && *(p + 1) != '\0') {
			tokenize = true;
		} else if (*(p + 1) == '\0') {
			tokenize = true;
			closetoken = true;
			setting = true;
		} else if (*p == '\n' && cursection != NULL && token_len > 0) {
			closetoken = true;
			setting = true;
		}

		if (tokenize) {
			if (token == NULL) {
				token = p;
				token_len = 1;
			} else {
				token_len++;
			}
			tokenize = false;
		}

		if (setting) {
			struct inicfg_setting *newsetting =
				new_setting(token, token_len);
			if (newsetting == NULL) {
				goto parse_failure_exit;
			}
			if (cursection == NULL) {
				free_setting(newsetting);
				goto parse_failure_exit;
			}
			newsetting->next = cursection->settings;
			cursection->settings = newsetting;
			setting = false;
		}

		if (closetoken) {
			token = NULL;
			token_len = 0;
			closetoken = false;
		}
	}

	inicfg_config = cursection;
	return FUNC_SUCCESS;

parse_failure_exit:
	free_section(cursection);
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

	char *buffer = NULL;
	// read file in to memory
	fseek(cfgfile, 0, SEEK_END);
	const int sz = ftell(cfgfile);
	if (sz == 0)
		goto success_exit;
	fseek(cfgfile, 0, SEEK_SET);
	buffer = calloc(1, sz + 1);
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
	if (buffer != NULL)
		free(buffer);
	return FUNC_SUCCESS;

failure_exit:
	if (buffer != NULL)
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
 */
void inicfg_close()
{
	free_section(inicfg_config);
}
