/**
 * @file render.h
 */

#ifndef RENDER_H
#define RENDER_H
#include <stdint.h>
#include "../utilities/geometry.h"
#include <SFML/Graphics.h>

/**
 * @struct render_cfg
 * @brief render subsystem configuration object
 */
struct render_cfg {
	uint8_t tgt_fps; //!< target render frames per second
	char *core; //!< core library to use for rendering
};

/**
 * @struct render_obj
 * @brief object to be rendered
 */
struct render_obj {
	struct geo_point *pos; //!< position to render object
	struct geo_point *prev_pos; //!< position of object in previous frame
};

/**
 * @struct render_frame
 * @brief frame to render to screen
 */
struct render_frame {
	uint64_t frm_tm; //!< point in time represented by frame
	uint64_t prev_frm_tm; //!< point in time of previous frame
	struct render_obj *objects; //!< objects to render
};

/**
 * @struct render_renderer
 * @brief renderer for render system
 */
struct render_renderer {
	sfRenderWindow *sfml_window; //!< sfml core window
};

extern int render_init(struct render_cfg *cfg,
		       struct render_renderer **renderer);
extern void render_close();
extern void *render_thread(void *args);

#endif //RENDER_H
