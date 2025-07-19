/**
* @file render.c
*/

#include "render.h"
#include "sdl/render_sdl.h"
#include "sdl/render_sdl_sw.h"
#include "../utilities/defines.h"
#include "../utilities/logger.h"
#include "../game/game.h"
#include "../utilities/timing.h"

#include <stdio.h>
#include <string.h>

#define UNKNOWN_CORE -1
#define SDL_CORE 0

#define UNKNOWN_RENDERER -1
#define SDL_HW_RENDERER 0
#define SDL_SW_RENDERER 1

static int core_type;
static int renderer_type;

/**
 * @brief initialize render subsystem
 * @param cfg pointer to struct render_cfg
 * @return 0 on success 1 on failure
 */
int render_init(struct render_cfg *cfg)
{
	core_type = UNKNOWN_CORE;
	if (strcmp(cfg->core, SDL_LIBRARY_CORE) == 0) {
		core_type = SDL_CORE;
	}
	renderer_type = UNKNOWN_RENDERER;
	if (strcmp(cfg->renderer, SDL_LIBRARY_RENDERER_SW) == 0) {
		renderer_type = SDL_SW_RENDERER;
	}
	if (strcmp(cfg->renderer, SDL_LIBRARY_RENDERER_HW) == 0) {
		renderer_type = SDL_HW_RENDERER;
	}

	switch (renderer_type) {
	case SDL_HW_RENDERER:
		return render_sdl_init(cfg);
	case SDL_SW_RENDERER:
		return render_sdl_sw_init(cfg);
	default:
		return FUNC_FAILURE;
	}
}

/**
 * @brief close render subsystem
 */
void render_close()
{
	switch (renderer_type) {
	case SDL_HW_RENDERER:
		render_sdl_close();
		break;
	case SDL_SW_RENDERER:
		render_sdl_sw_close();
		break;
	default:
		break;
	}
}

/**
 * @brief render frames attached to the game object
 * @param frames list of frames to render
 * @return int 0 on success 1 on failure
 */
int render_render_frames(struct render_frame *frames)
{
	// render frame
	switch (renderer_type) {
	case UNKNOWN_RENDERER:
		log_write(LOG_TAG_ERR, "render core not properly set");
		return FUNC_FAILURE;
		break;
	case SDL_HW_RENDERER:
		render_sdl_frame(NULL, 0.0f);
		break;
	case SDL_SW_RENDERER:
		render_sdl_sw_frame(NULL, 0.0f);
		break;
	default:
		log_write(LOG_TAG_ERR, "unknown render core");
		return FUNC_FAILURE;
		break;
	}

	return FUNC_SUCCESS;
}
