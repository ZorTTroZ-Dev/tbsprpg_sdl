/**
 * @file audio_sdl.c
 */

#include "../audio.h"
#include "audio_sdl.h"
#include <SDL2/SDL_mixer.h>

#include "../../utilities/defines.h"
#include "../../utilities/logger.h"

static Mix_Music *music = NULL;

int audio_sdl_init(struct audio_cfg *cfg)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		log_write(LOG_TAG_ERR,
			  "SDL_mixer could not initialize! SDL_mixer Error:");
		log_write(LOG_TAG_ERR, Mix_GetError());
		return FUNC_FAILURE;
	}

	music = Mix_LoadMUS(
		"resources/music/1-Behind-space-seamless.mp3");
	if(music == NULL) {
		log_write(LOG_TAG_ERR, "Failed to load beat music! SDL_mixer Error:");
		log_write(LOG_TAG_ERR, Mix_GetError());
		Mix_Quit();
		return FUNC_FAILURE;
	}

	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		Mix_PlayMusic( music, -1 );
	}

	return FUNC_SUCCESS;
}

void audio_sdl_close()
{
	Mix_FreeMusic(music);
	Mix_Quit();
}
