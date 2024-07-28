/**
 * @file ini_config.h
 */

#ifndef INI_CONFIG_H
#define INI_CONFIG_H

#define INICFG_CONFIG_FILE_PATH "config.ini"

extern int inicfg_open();
extern int inicfg_getstring();
extern int inicfg_getint();
extern int inicfg_close();

#endif //INI_CONFIG_H
