#include "utilities/ini_config.h"
#include "utilities/logger.h"
#include "game/game.h"

#include <stddef.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static void config_game(struct game_cfg *cfg)
{
	inicfg_getstring("game", "core", &(cfg->core));
	inicfg_getstring("input", "core", &(cfg->input_core));
	inicfg_getuint8_t("input", "cps", &(cfg->input_cps));
	inicfg_getstring("render", "core", &(cfg->render_core));
	inicfg_getuint8_t("render", "fps", &(cfg->render_fps));
	inicfg_getstring("audio", "core", &(cfg->audio_core));
	inicfg_getuint8_t("audio", "cps", &(cfg->audio_cps));
	inicfg_getuint8_t("simulation", "cps", &(cfg->sim_cps));
}

int main(int argc, char *argv[])
{
	if (log_open(LOG_DEBUG) > 0) {
		return 1;
	}
	log_write(LOG_TAG_INFO, "logger initialized");
	log_write(LOG_TAG_INFO, "tbsprpg_sdl starting up");

	inicfg_open();

	struct game_cfg gcfg;
	config_game(&gcfg);
	game_start(&gcfg);

	inicfg_close();

	log_write(LOG_TAG_INFO, "tbsprpg_sdl shutting down");
	log_close();
	log_write(LOG_TAG_INFO, "logger destroyed");
	return 0;
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
