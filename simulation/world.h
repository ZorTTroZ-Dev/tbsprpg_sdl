/**
* @file world.h
*/

#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @struct world_file_header
 * @brief header for binary world file
 */
struct world_file_header {
	uint8_t version;
	uint16_t length;
	uint16_t width;
	uint16_t height;
};

struct world_tile {
	uint16_t texture_id;
};

// walls will have to exist in the object layer
// walls look to be exactly two tiles high
struct world {
	struct world_tile *tile_map; //!< world tile map
};

extern int world_open(char *world_file_path, uint8_t bootstrap);
extern void world_close();

#endif //WORLD_H
