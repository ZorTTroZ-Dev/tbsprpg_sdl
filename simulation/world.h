/**
* @file world.h
*/

#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>
#include <stdint.h>

#define WORLD_WIDTH 50
#define WORLD_HEIGHT 50
#define WORLD_DEPTH 20

struct world_tile {
	uint16_t texture_id;
	bool transition;
	// may need a flag to say if there is a wall on this tile
};

struct world_object {
	uint16_t texture_id;
};

struct world_object_list {
	struct world_object *object;
	struct world_object_list *next;
};

// walls will have to exist in the object layer
// walls look to be exactly two tiles high
// do objects just have a global coordinate, I may have to give stuff a z coordinate
struct world {
	struct world_tile *tile_map[WORLD_DEPTH][WORLD_WIDTH]
				   [WORLD_HEIGHT]; //!< 3d array world tile map
	struct world_object_list *
		level_objects[WORLD_DEPTH]; //!< list of objects sorted by level
	struct world_object *objects; //!< array of all objects in world
};

extern int world_open();
extern void world_close();

#endif //WORLD_H
