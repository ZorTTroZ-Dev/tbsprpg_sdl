/**
 * @file render.h
 */

#ifndef RENDER_H
#define RENDER_H
#include <stdint.h>
#include "../utilities/geometry.h"

struct render_cfg {
	uint8_t tgt_fps;
};

struct render_obj {
	struct geo_point *pos;
	struct geo_point *prev_pos;
};

struct render_frame {
	uint64_t frm_tm;
	uint64_t prev_frm_tm;
	struct render_obj *objects;
};

extern int render_init(struct render_cfg *cfg);
extern void render_close();
extern void *render_thread(void *args);

#endif //RENDER_H
