#include "utilities/ini_config.h"
#include "utilities/logger.h"

#include <stddef.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
	if (log_open(LOG_DEBUG) > 0) {
		return 1;
	}
	log_write(LOG_TAG_INFO, "logger initialized");
	log_write(LOG_TAG_INFO, "tbsprpg_sdl starting up");

	inicfg_open();

	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n",
		       SDL_GetError());
	} else {
		//Create window
		window = SDL_CreateWindow("tbsprpg sdl",
					  SDL_WINDOWPOS_UNDEFINED,
					  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
					  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n",
			       SDL_GetError());
		} else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL,
				     SDL_MapRGB(screenSurface->format, 0xFF,
						0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Hack to get window to stay up
			SDL_Event e;
			bool quit = false;
			while (quit == false) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT)
						quit = true;
				}
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	SDL_Quit();

	inicfg_close();

	log_write(LOG_TAG_INFO, "tbsprpg_sdl shutting down");
	log_close();
	log_write(LOG_TAG_INFO, "logger destroyed");
	return 0;
}
