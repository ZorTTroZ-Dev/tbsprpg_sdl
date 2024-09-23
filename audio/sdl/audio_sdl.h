/**
 * @file audio_sdl.h
 */

#ifndef AUDIO_SDL_H
#define AUDIO_SDL_H

#include "../audio.h"

extern int audio_sdl_init(struct audio_cfg *cfg);
extern void audio_sdl_close();
// extern int audio_sdl_frame(struct render_frame *frame, float interpolation);

#endif //AUDIO_SDL_H
