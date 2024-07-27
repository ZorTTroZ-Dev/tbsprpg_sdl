#include <stdio.h>
#include <stdlib.h>

#include "utilities/mem_manager.h"

int main(void)
{
	struct mmgr_handle *handle = malloc(sizeof(struct mmgr_handle));
	handle->handle = 42;
	printf("%d\n", handle->handle);
	free(handle);
	mmgr_alloc();
	printf("Hello World!\n");
	return 0;
}
