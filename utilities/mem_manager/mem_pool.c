/**
 * @file mem_pool.c
*/

#include "../defines.h"
#include "../logger.h"
#include "../mem_manager.h"

#include <stdlib.h>

/**
 * @struct mmgr_pool_chunk
 * @brief individual chunk in memory pool
 */
struct mmgr_pool_chunk_hdr {
	uint32_t size; //!< size of the data pointer in chunk
	uint32_t used; //!< size of object contained
	struct mmgr_pool_chunk_hdr *next; //!< pointer to next chunk
	struct mmgr_mem_pool *pool; //!< pointer to pool this chunk belongs to
};

/**
 * @struct mmgr_mem_pool
 * @brief memory pool
 */
struct mmgr_mem_pool {
	uint32_t chunk_size; //!< chunk size for this pool
	uint32_t num_chunks; //!< how many chunks this pool contains
	uint32_t num_used_chunks; //!< how many chunks are in use
	struct mmgr_pool_chunk_hdr *chunks; //!< pointer to first chunk
	struct mmgr_pool_chunk_hdr *free; //!< pointer to first free chunk
	struct mmgr_mem_pool *next; //!< pointer to next pool
};

/**
 * @struct mmgr_pool_complex
 * @brief container for all of the memory pools
 */
struct mmgr_pool_complex {
	uint32_t num_pools; //!< how many pools are there
	struct mmgr_mem_pool *pools; //!< pointer to first pool
};

static struct mmgr_pool_complex *pools = NULL; //!< pointer to the pools

static const uint32_t chunk_hdr_size = sizeof(struct mmgr_pool_chunk_hdr);

static struct mmgr_mem_pool *new_pool(uint32_t chunk_size, uint32_t num_chunks)
{
	if (chunk_size == 0 || num_chunks == 0)
		return NULL;

	struct mmgr_mem_pool *pool = malloc(sizeof(struct mmgr_mem_pool));
	if (pool == NULL)
		return NULL;

	pool->chunk_size = chunk_size;
	pool->num_chunks = num_chunks;
	pool->num_used_chunks = 0;

	// allocate and setup chunks
	const uint32_t chunk_step = chunk_size + chunk_hdr_size;
	char *chunks = calloc(num_chunks, chunk_step);
	if (chunks == NULL) {
		free(pool);
		return NULL;
	}
	for (int i = 0; i < num_chunks; i++) {
		char *chunk_ptr = chunks + (i * chunk_step);
		struct mmgr_pool_chunk_hdr *chunk =
			(struct mmgr_pool_chunk_hdr *)chunk_ptr;
		chunk->size = chunk_size;
		chunk->used = 0;
		chunk->pool = pool;
		chunk->next = NULL;

		// not the last chunk
		if (i + 1 != num_chunks)
			chunk->next = chunk + chunk_step;
	}
	pool->chunks = (struct mmgr_pool_chunk_hdr *)chunks;
	pool->free = (struct mmgr_pool_chunk_hdr *)chunks;

	return pool;
}

int mmgr_pool_open(const struct mmgr_pool_cfg *config)
{
	if (config->num_pools < 1)
		return FUNC_SUCCESS;

	pools = malloc(sizeof(struct mmgr_pool_complex));
	if (pools == NULL)
		goto mmgr_pool_init_failure;
	pools->num_pools = config->num_pools;
	pools->pools = NULL;

	for (int i = 0; i < config->num_pools; i++) {
		struct mmgr_mem_pool *pool = new_pool(config->chunk_sizes[i],
						      config->chunk_counts[i]);
		if (pool == NULL)
			goto mmgr_pool_init_failure;

		pool->next = pools->pools;
		pools->pools = pool;
	}

	return FUNC_SUCCESS;

mmgr_pool_init_failure:
	mmgr_pool_close();
	log_write(LOG_TAG_ERR, "failed to initialize memory pools");
	return FUNC_FAILURE;
}

void free_pools(struct mmgr_mem_pool *pool)
{
	while (pool != NULL) {
		free(pool->chunks);
		struct mmgr_mem_pool *npool = pool->next;
		free(pool);
		pool = npool;
	}
}

void mmgr_pool_close()
{
	if (pools != NULL) {
		free_pools(pools->pools);
		pools->num_pools = 0;
		free(pools);
	}
}
