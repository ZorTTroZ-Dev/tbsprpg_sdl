/**
* @file mem_pool.h
*/

#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stddef.h>

extern void *plalloc(size_t size);
extern void plfree(void *mem);

#endif //MEM_POOL_H
