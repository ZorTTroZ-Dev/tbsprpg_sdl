/**
 * @file ini_config.h
 */

#ifndef INI_CONFIG_H
#define INI_CONFIG_H

#define INICFG_CONFIG_FILE_PATH "config.ini"

extern int inicfg_open();
extern void inicfg_getstring(const char *section, const char *key, char *value);
extern void inicfg_getint(const char *section, const char *key, int *value);
extern void inicfg_close();

#endif //INI_CONFIG_H
