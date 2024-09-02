/**
 * @file render_sfml.c
 */

#include "render_sfml.h"
#include "../../utilities/defines.h"
#include "../../utilities/logger.h"

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

static sfRenderWindow *window;
static struct render_renderer *sfml_renderer;

int render_sfml_init(struct render_cfg *cfg, struct render_renderer **renderer)
{
	sfml_renderer = malloc(sizeof(struct render_renderer));
	if (sfml_renderer == NULL) {
		log_write(LOG_TAG_ERR, "render_sdl_init: malloc failed");
		return FUNC_FAILURE;
	}
	const sfVideoMode mode = { 800, 600, 32 };
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose,
				       NULL);
	if (window == NULL) {
		free(sfml_renderer);
		printf("SFML Window could not be created!\n");
		return FUNC_FAILURE;
	}
	sfml_renderer->sfml_window = window;
	*renderer = sfml_renderer;
	return FUNC_SUCCESS;
}

void render_sfml_close()
{
	if (sfml_renderer != NULL) {
		free(sfml_renderer);
	}
	sfRenderWindow_destroy(window);
}

int render_sfml_frame(struct render_frame *frame, float interpolation)
{
	sfRenderWindow_setActive(window, sfTrue);
	// sfCircleShape *circle = sfCircleShape_create();
	// sfCircleShape_setRadius(circle, 100.0f);
	// sfCircleShape_setFillColor(circle, sfGreen);
	sfRenderWindow_clear(window, sfWhite);
	// sfRenderWindow_drawCircleShape(window, circle, NULL);
	sfRenderWindow_display(window);
	// sfCircleShape_destroy(circle);
	return FUNC_SUCCESS;
}
