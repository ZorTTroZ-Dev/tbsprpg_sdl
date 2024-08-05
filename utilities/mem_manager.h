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

/**
 * @struct mmgr_pool_cfg
 * @brief object for pool configuration
 */
struct mmgr_pool_cfg {
	uint16_t num_pools; //!< number of pools to create
	uint32_t *chunk_sizes; //!< size of chunk in each pool
	uint32_t *chunk_counts; //!< how many chunks in each pool
};

extern void mmgr_alloc();
extern void mmgr_free();
extern int mmgr_pool_open(const struct mmgr_pool_cfg *config);
extern void mmgr_pool_close();

#endif //MEM_MANAGER_H
