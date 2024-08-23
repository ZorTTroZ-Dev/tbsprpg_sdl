/**
 * @file input.h
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

struct input_cfg {
	uint8_t tgt_cps; // cycles per second
};

extern int input_init(struct input_cfg *cfg);
extern void *input_thread(void *args);

#endif //INPUT_H
