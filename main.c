#include "utilities/ini_config.h"

#include <stdio.h>
#include "utilities/logger.h"

int main(void)
{
	if (log_open(LOG_DEBUG) > 0) {
		return 1;
	}
	log_write(LOG_TAG_INFO, "logger initialized");
	log_write(LOG_TAG_INFO, "tbsprpg_sdl starting up");

	inicfg_open();
	inicfg_close();

	log_write(LOG_TAG_INFO, "tbsprpg_sdl shutting down");
	log_close();
	log_write(LOG_TAG_INFO, "logger destroyed");
	return 0;
}
