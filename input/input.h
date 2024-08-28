/**
 * @file input.h
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

#include "../game/game.h"

/**
 * @struct input_cfg
 * @brief input subsystem config object
 */
struct input_cfg {
	uint8_t tgt_cps; //!< input subsystem thread target cycles per second
	char *core; //!< core library to use to process input
};

extern int input_init(struct input_cfg *cfg);
extern void input_close();
extern int input_handle_input(struct game *game);

#endif //INPUT_H
