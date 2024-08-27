/**
* @file audio.h
*/

#ifndef AUDIO_H
#define AUDIO_H
#include <stdint.h>

struct audio_cfg {
	uint8_t tgt_cps; // cycles per second
};

struct audio_track {
	uint64_t volume;
};

extern int audio_init(struct audio_cfg *cfg);
extern void audio_close();
extern void *audio_thread(void *args);

#endif //AUDIO_H
