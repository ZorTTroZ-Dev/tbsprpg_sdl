/**
 * @file render_sfml.h
 */

#ifndef RENDER_SFML_H
#define RENDER_SFML_H

#include "../render.h"

extern int render_sfml_init(struct render_cfg *cfg,
			    struct render_renderer **renderer);
extern void render_sfml_close();
extern int render_sfml_frame(struct render_frame *frame, float interpolation);

#endif //RENDER_SFML_H
