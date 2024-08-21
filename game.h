/**
 * @file game.h
 */

#ifndef GAME_H
#define GAME_H
#include <stdint.h>
#include "render/render.h"

struct game_cfg {
	uint8_t num_threads;
	uint8_t render_fps;
};

struct game {
	struct render_frame *frames;
};

extern int game_start(struct game_cfg *cfg);
extern int game_stop();

#endif //GAME_H
