/**
* @file simulation.h
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdint.h>

/**
 * @struct sim_cfg
 * @brief simulation subsystem configuration
 */
struct sim_cfg {
	uint8_t tgt_cps; //!< target cycles per second of simulation thread
};

/**
 * @brief object in game world
 */
struct sim_object {
	uint64_t id;
};

/**
 * @brief representation of game world
 */
struct sim_world {
	struct sim_object *objects; //!< objects in the game world
};

extern int sim_init(struct sim_cfg *cfg);
extern void sim_close();
extern void *sim_thread(void *args);

#endif //SIMULATION_H
