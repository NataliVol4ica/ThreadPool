
#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define MALL_ERROR(x) if (!(x)) malloc_error()
#define THR_ERROR(x) if ((x)) thread_error()
#define FORK_ERROR(x) if (x == -1) fork_error()

t_thread_pool	*create_thread_pool(size_t num_of_threads)
{
	t_thread_pool	*pool;
	size_t			i;
	int				rc;

	MALL_ERROR(pool = (t_thread_pool*)malloc(sizeof(t_thread_pool)));
	MALL_ERROR(pool->threads = (t_thread*)malloc(sizeof(t_thread) * num_of_threads));
	pool->queue = NULL;
	pool->num_of_threads.val = 0;
	pool->num_of_active_threads.val = 0;
	t_var_init(&(pool->num_of_threads));
	t_var_init(&(pool->num_of_active_threads));
	i = -1;
	while (++i < num_of_threads)
		THR_ERROR(rc = pthread_create(&pool->threads[i].thread, NULL, thread_function, pool));
	pthread_mutex_lock(&pool->num_of_threads.mutex);
	while(pool->num_of_threads.val < num_of_threads)
		wait_cond(&pool->num_of_threads);
	pthread_mutex_unlock(&pool->num_of_threads.mutex);
	return (pool);
}

void			stop_thread_pool(t_thread_pool	*pool)
{
	free(pool->threads);
	free(pool);
}
