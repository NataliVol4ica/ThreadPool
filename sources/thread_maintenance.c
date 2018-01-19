
#include "threadpool.h"
#include <stdio.h>

void	*thread_function(void *arg)
{
	t_thread_pool *pool;

	pool = (t_thread_pool*)arg;
	pthread_mutex_lock(&pool->lock_num_of_threads);
	printf("Creating thread %zu\n", ++pool->num_of_threads);
	pthread_mutex_unlock(&pool->lock_num_of_threads);
	pthread_cond_signal(&pool->cond_num_of_threads);
	pthread_exit(NULL);
}
