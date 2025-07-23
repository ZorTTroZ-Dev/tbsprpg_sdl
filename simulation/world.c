/**
 * @file world.c
 */

#include "world.h"

#include "../utilities/defines.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static char *world_file_name = NULL;

int world_open()
{
	// allocate enough world tiles to fill out the world width * length * height
	// from the memory pool

	// open the world file, configured in ini

	// read tile info from world file, populate tile information

	// are we going to stream the world or put the whole world in memory, depends on size

	// how am I going to save or retrieve texture id
	// stored as tuple (sheet id, sheet x, sheet y)
	// get handle from texture manager
	return FUNC_SUCCESS;
}

void world_close()
{
}

int world_write()
{
	return FUNC_SUCCESS;
}
