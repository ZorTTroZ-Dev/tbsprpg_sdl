/**
* @file timing.c
*/

#include "../timing.h"
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <time.h>
#endif

/**
 * @brief get time in ms since system boot
 * @return time in ms since system startup
 */
uint64_t timing_get_time()
{
#ifdef _WIN32
	return GetTickCount64();
#elif __linux__
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_nsec;
#endif
}
