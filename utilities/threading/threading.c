/**
* @file threading.c
*/

#include "../threading.h"

#include "../defines.h"

// void ms_to_timespec(struct timespec *ts, unsigned int ms);

#ifdef _WIN32
typedef struct {
	void *(*start_routine)(void *);
	void *start_arg;
} win_thread_start_t;

static DWORD WINAPI win_thread_start(void *arg)
{
	win_thread_start_t *data = arg;
	void *(*start_routine)(void *) = data->start_routine;
	void *start_arg = data->start_arg;

	free(data);

	start_routine(start_arg);
	return FUNC_SUCCESS;
}

int pthread_create(pthread_t *thread, pthread_attr_t *attr,
		   void *(*start_routine)(void *), void *arg)
{
	win_thread_start_t *data;

	(void)attr;

	if (thread == NULL || start_routine == NULL)
		return 1;

	data = malloc(sizeof(*data));
	data->start_routine = start_routine;
	data->start_arg = arg;

	*thread = CreateThread(NULL, 0, win_thread_start, data, 0, NULL);
	if (*thread == NULL)
		return FUNC_FAILURE;
	return FUNC_SUCCESS;
}

int pthread_join(pthread_t thread, void **value_ptr)
{
	(void)value_ptr;
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	return FUNC_SUCCESS;
}

int pthread_detach(pthread_t thread)
{
	CloseHandle(thread);
	return FUNC_SUCCESS;
}

int pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr)
{
	(void)attr;

	if (mutex == NULL)
		return FUNC_FAILURE;

	InitializeCriticalSection(mutex);
	return FUNC_SUCCESS;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	if (mutex == NULL)
		return FUNC_FAILURE;
	DeleteCriticalSection(mutex);
	return FUNC_SUCCESS;
}

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
	if (mutex == NULL)
		return FUNC_FAILURE;
	EnterCriticalSection(mutex);
	return FUNC_SUCCESS;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	if (mutex == NULL)
		return FUNC_FAILURE;
	LeaveCriticalSection(mutex);
	return FUNC_SUCCESS;
}

#endif
