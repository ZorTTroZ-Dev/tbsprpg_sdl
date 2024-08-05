#include "utilities/ini_config.h"

#include <stdio.h>
#include "utilities/logger.h"
#include "utilities/mem_manager.h"
#include "utilities/mem_manager/mem_pool.h"

int main(void)
{
	if (log_open(LOG_DEBUG) > 0) {
		return 1;
	}
	log_write(LOG_TAG_INFO, "logger initialized");
	log_write(LOG_TAG_INFO, "tbsprpg_sdl starting up");

	inicfg_open();

	uint32_t sizes[] = { 4 };
	uint32_t counts[] = { 3 };
	struct mmgr_pool_cfg pool_cfg;
	pool_cfg.num_pools = 1;
	pool_cfg.chunk_sizes = sizes;
	pool_cfg.chunk_counts = counts;
	mmgr_pool_open(&pool_cfg);

	int *alloc_int = plalloc(sizeof(int));
	*alloc_int = 7;
	plfree(alloc_int);

	mmgr_pool_close();

	inicfg_close();

	log_write(LOG_TAG_INFO, "tbsprpg_sdl shutting down");
	log_close();
	log_write(LOG_TAG_INFO, "logger destroyed");
	return 0;
}
