
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
	t_var_init(&(pool->num_of_threads));
	t_var_init(&(pool->num_of_active_threads));
	t_var_init(&(pool->awake_thread));
	t_var_init(&(pool->quit_pool));
	t_var_init(&(pool->queue_access));
	i = -1;
	while (++i < num_of_threads)
		THR_ERROR(rc = pthread_create(&pool->threads[i].thread, NULL, thread_function, pool));//starting all the threads
	pthread_mutex_lock(&pool->num_of_threads.mutex);
	while(pool->num_of_threads.val < num_of_threads)
		pthread_cond_wait(&pool->num_of_threads.cond, &pool->num_of_threads.mutex);//waiting for all threads to be created
	pthread_mutex_unlock(&pool->num_of_threads.mutex);
	printf("Pool has been created\n");
	return (pool);
}

void			add_task(t_thread_pool *pool, void *(*func)(void*), void *param)
{
	t_task	*new;
	t_task	*queue;

	new = (t_task*)malloc(sizeof(t_task));
	new->func = func;
	new->param = param;
	new->next_task = NULL;
	//adding new task to queue
	pthread_mutex_lock(&pool->queue_access.mutex);
	if (!pool->queue)
		pool->queue = new;
	else
	{
		queue = pool->queue;
		while (queue->next_task)
			queue = queue->next_task;
		queue->next_task = new;
	}
	printf("Adding queue task\n");
	pthread_cond_signal(&pool->awake_thread.cond);
	pthread_mutex_unlock(&pool->queue_access.mutex);
	//do something. 
}

void			stop_thread_pool(t_thread_pool	*pool)
{
	size_t	i;

	pthread_mutex_lock(&pool->quit_pool.mutex);
	pool->quit_pool.val = 1;
	pthread_cond_broadcast(&pool->awake_thread.cond);
	pthread_mutex_unlock(&pool->quit_pool.mutex);
	i = -1;
	while (++i < pool->num_of_threads.val)
		pthread_join(pool->threads[i].thread, NULL);
	free(pool->threads);
	free(pool);
	printf("Pool has finished its existing\n");
}
