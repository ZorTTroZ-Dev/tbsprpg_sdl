/**
 * @file mem_manager.h
 */

#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H
#include <stdint.h>

/**
 * @struct mmgr_handle
 * @brief Handle for allocated data from memory manager
 */
struct mmgr_handle {
        uint32_t handle; //!< comprised of a magic number and a memory chunk id
        void *data; //!< pointer to allocated memory
};

extern void mmgr_alloc();
extern void mmgr_free();

// initialize the memory pools, needs to be called before allocating memory
// memory pool will consist of linked list of memory chunks in use
// and a linked list of memory chunks not in use a chunk will contain an id
// a link to the next chunk a pointer to the actual memory
extern void mmgr_pool_init();

#endif //MEM_MANAGER_H
