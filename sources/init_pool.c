
#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>

#define MALL_ERROR(x) if (!(x)) malloc_error()
#define THR_ERROR(x) if ((x)) thread_error()

t_thread_pool	*create_thread_pool(size_t num_of_threads)
{
	t_thread_pool	*pool;
	size_t			i;
	int				rc;

	MALL_ERROR(pool = (t_thread_pool*)malloc(sizeof(t_thread_pool)));
	MALL_ERROR(pool->threads = (t_thread**)malloc(sizeof(t_thread*) * num_of_threads));
	pool->queue = NULL;
	pool->num_of_threads = num_of_threads;
	pool->num_of_active_threads = 0;
	i = -1;
	while (++i < num_of_threads)
	{
		MALL_ERROR(pool->threads[i] = (t_thread*)malloc(sizeof(t_thread)));
		THR_ERROR(rc = pthread_create(&pool->threads[i]->thread, NULL, thread_function, pool));
	}
	return (pool);
}

void			stop_thread_pool(t_thread_pool	*pool)
{
	size_t	i;

	i = -1;
	while (++i < pool->num_of_threads)
		free(pool->threads[i]);
	free(pool->threads);
	free(pool);
}
