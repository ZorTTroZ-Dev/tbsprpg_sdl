/**
 * @file input_sdl.c
 */

#include "../../game/game.h"
#include "../../utilities/defines.h"
#include "../../utilities/timing.h"

#include <SDL.h>
#include <stdio.h>

/**
 * @brief SDL version of input handling loop
 * @param game pointer to struct game
 * @param tgt_cps int target cycles per secon
 * @return 0 on success 1 on failure
 */
int input_sdl_handle_input(struct game *game, int tgt_cps)
{
	uint32_t cps_time = timing_get_time();
	uint32_t cycle = 0;
	float cps = 0;
	const uint32_t mspercycle = 1000 / tgt_cps;
	SDL_Event event;
	while (!game->shutdown) {
		const uint64_t start = timing_get_time();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				game->shutdown = true;
		}
		const uint64_t end = timing_get_time();
		const uint64_t sleep = mspercycle - (end - start);
		if (sleep > 0) {
			timing_msleep(sleep);
		}

		// calculate cycles per second
		cycle++;
		if (cycle == 100) {
			const uint32_t cps_end_time = timing_get_time();
			cps = cycle / (float)((cps_end_time - cps_time) / 1000);
			cps_time = cps_end_time;
			cycle = 0;
		}
	}
	printf("%f\n", cps);

	return FUNC_SUCCESS;
}
