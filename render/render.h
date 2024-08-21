/**
 * @file render.h
 */

#ifndef RENDER_H
#define RENDER_H
#include <stdint.h>

struct render_cfg {
	uint8_t tgt_fps;
};

struct render_frame {
	uint64_t frame_time;
};

extern int render_init(struct render_cfg *cfg);
extern void *render_thread(void *args);

#endif //RENDER_H
