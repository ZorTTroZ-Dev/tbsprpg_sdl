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

/**
 * @struct game_cfg
 * @brief Configuration settings for a game
 */
struct game_cfg {
	uint8_t render_fps; //!< target frames per second to render
	uint8_t sim_cps; //!< cycles per second simulation thread should run at
	uint8_t audio_cps; //!< cycles per second audio thread should run at
	uint8_t input_cps; //!< cycles per second input should be polled at
	char *core; //!< core game library, currently only sdl supported
	char *render_core; //!< core graphics library, currently only sdl supported
	char *audio_core; //!< core audio library, currently only sdl supported
	char *input_core; //!< core input library, currently only sdl supported
};

/**
 * @struct game
 * @brief top-level game objects
 */
struct game {
	bool shutdown; //!< should threads shutdown
	struct render_frame *frames; //!< queue of frames to render
	struct audio_track *tracks; //!< audio tracks queued for playback
	struct sim_world *world; //!< state of game world
	struct sim_object *
		updated_objs; //!< objects that have been updated by input since the last frame was generated
};

extern int game_start(const struct game_cfg *cfg);
extern int game_stop();

#endif //GAME_H
