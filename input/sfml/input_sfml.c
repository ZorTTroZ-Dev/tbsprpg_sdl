/**
 * @file input_sfml.c
 */

#include "../../game/game.h"
#include "../../utilities/defines.h"
#include "input_sfml.h"

#include <SFML/Graphics.h>

static sfEvent event;

/**
 * @brief SFML version of input handling loop
 * @param game pointer to struct game
 * @return 0 on success 1 on failure
 */
int input_sfml_handle_input(struct game *game)
{
	sfRenderWindow *window = game->renderer->sfml_window;
	sfRenderWindow_setActive(window, sfFalse);
	while (sfRenderWindow_pollEvent(window, &event)) {
		if (event.type == sfEvtClosed)
			game->shutdown = true;
	}
	return FUNC_SUCCESS;
}
