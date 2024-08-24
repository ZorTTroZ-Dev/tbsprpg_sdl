/**
 * @file game.h
 */

#ifndef GAME_H
#define GAME_H

#include "../render/render.h"
#include "../audio/audio.h"
#include "../simulation/simulation.h"

#include <stdbool.h>
#include <stdint.h>

#define GAME_CORE_SDL "sdl"

struct game_cfg {
	uint8_t render_fps;
	uint8_t sim_cps;
	uint8_t audio_cps;
	uint8_t input_cps;
	char *core;
	char *render_core;
	char *audio_core;
	char *input_core;
};

struct game {
	bool shutdown;
	struct render_frame *frames;
	struct audio_track *tracks;
	struct sim_world *world;
	struct sim_object *updated_objs;
};

extern int game_start(const struct game_cfg *cfg);
extern int game_stop();

#endif //GAME_H
