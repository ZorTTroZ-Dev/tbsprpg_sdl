/**
* @file simulation.h
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdint.h>

struct sim_cfg {
	uint8_t tgt_cps; // cycles per second
};

struct sim_object {
	uint64_t id;
};

struct sim_world {
	struct sim_object *objects;
};

extern int sim_init(struct sim_cfg *cfg);
extern void sim_close();
extern void *sim_thread(void *args);

#endif //SIMULATION_H
