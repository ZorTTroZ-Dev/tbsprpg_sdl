#include "utilities/ini_config.h"
#include "utilities/logger.h"

#include <stddef.h>
#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (log_open(LOG_DEBUG) > 0) {
		return 1;
	}
	log_write(LOG_TAG_INFO, "logger initialized");
	log_write(LOG_TAG_INFO, "tbsprpg_sdl starting up");

	inicfg_open();

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n",
		       SDL_GetError());
	}

	SDL_Quit();

	inicfg_close();

	log_write(LOG_TAG_INFO, "tbsprpg_sdl shutting down");
	log_close();
	log_write(LOG_TAG_INFO, "logger destroyed");
	return 0;
}
