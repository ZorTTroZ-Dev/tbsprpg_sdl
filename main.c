#include "utilities/ini_config.h"
#include "utilities/logger.h"
#include "game.h"

#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <time.h>
#endif

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#ifdef __linux__
static struct timespec ts;
#endif

uint64_t get_tick_count()
{
#ifdef _WIN32
	return GetTickCount64();
#elif __linux__
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_nsec;
#endif
}

// int run_game(int simfps)
// {
// 	srand(time(NULL));
// 	// how big of steps take to run simulation at 25fps
// 	uint32_t timestep = 1000 / simfps;
// 	// most simulation updates to run before rendering
// 	int max_sim_runs = 5;
//
// 	int sim_runs;
// 	float interpolation;
// 	uint64_t curtime = get_tick_count();
//
// 	int bigloops = 0;
//
// 	bool running = true;
// 	while (running && bigloops < 100) {
// 		sim_runs = 0;
// 		printf("Start %d %" PRIu64 " %" PRIu64 "\n", sim_runs, get_tick_count(), curtime);
// 		while (get_tick_count() > curtime && sim_runs < max_sim_runs) {
// 			// update the game
// 			Sleep((rand() % 2) + 1);
// 			curtime += timestep;
// 			sim_runs++;
// 			printf("Sim %d %" PRIu64 " %" PRIu64 "\n", sim_runs, get_tick_count(), curtime);
// 		}
//
// 		interpolation = (float)(get_tick_count() + timestep - curtime) /
// 				(float)timestep;
// 		printf("%.2f\n", interpolation);
// 		//render(interpolation);
// 		Sleep((rand() % 30) + 1);
// 		bigloops++;
// 	}
// 	// printf("%" PRIu64 "\n", get_tick_count());
// }

int main(int argc, char *argv[])
{
	if (log_open(LOG_DEBUG) > 0) {
		return 1;
	}
	log_write(LOG_TAG_INFO, "logger initialized");
	log_write(LOG_TAG_INFO, "tbsprpg_sdl starting up");

	inicfg_open();

	struct game_cfg gcfg;
	game_start(&gcfg);

	//run_game(25);

	// SDL_Window *window = NULL;
	// SDL_Surface *screenSurface = NULL;
	//
	// //Initialize SDL
	// if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	// 	printf("SDL could not initialize! SDL_Error: %s\n",
	// 	       SDL_GetError());
	// } else {
	// 	//Create window
	// 	window = SDL_CreateWindow("tbsprpg sdl",
	// 				  SDL_WINDOWPOS_UNDEFINED,
	// 				  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
	// 				  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// 	if (window == NULL) {
	// 		printf("Window could not be created! SDL_Error: %s\n",
	// 		       SDL_GetError());
	// 	} else {
	// 		//Get window surface
	// 		screenSurface = SDL_GetWindowSurface(window);
	//
	// 		//Fill the surface white
	// 		SDL_FillRect(screenSurface, NULL,
	// 			     SDL_MapRGB(screenSurface->format, 0xFF,
	// 					0xFF, 0xFF));
	//
	// 		//Update the surface
	// 		SDL_UpdateWindowSurface(window);
	//
	// 		//Hack to get window to stay up
	// 		SDL_Event e;
	// 		bool quit = false;
	// 		while (quit == false) {
	// 			while (SDL_PollEvent(&e)) {
	// 				if (e.type == SDL_QUIT)
	// 					quit = true;
	// 			}
	// 		}
	// 	}
	// }
	//
	// //Destroy window
	// SDL_DestroyWindow(window);
	//
	// SDL_Quit();

	inicfg_close();

	log_write(LOG_TAG_INFO, "tbsprpg_sdl shutting down");
	log_close();
	log_write(LOG_TAG_INFO, "logger destroyed");
	return 0;
}
