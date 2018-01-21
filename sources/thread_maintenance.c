
#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>

void	*thread_function(void *arg)
{
	t_thread_pool	*pool;
	t_task			*temp;
	size_t			id;

	pool = (t_thread_pool*)arg;
	pthread_mutex_lock(&pool->num_of_threads.mutex);
	pool->num_of_threads.val += 1;
	id = pool->num_of_threads.val;
	printf("Thread %zu has been created\n", id);
	pthread_cond_signal(&pool->num_of_threads.cond);
	pthread_mutex_unlock(&pool->num_of_threads.mutex);
	while (1)
	{
		if (pool->queue)
		{
			change_mutex_var(&pool->num_of_active_threads, 1);
			temp = pool->queue;
			pool->queue = pool->queue->next_task;
			pthread_mutex_unlock(&pool->queue_access.mutex);
			temp->func(temp->param);
			free(temp);
			change_mutex_var(&pool->num_of_active_threads, -1);
			continue ;
		}
		pthread_mutex_lock(&pool->quit_pool.mutex);
		if (pool->quit_pool.val == 1)
		{
			printf("Thread %zu is quitting\n", id);
			pthread_mutex_unlock(&pool->quit_pool.mutex);
			break;
		}
		pthread_mutex_unlock(&pool->quit_pool.mutex);
		pthread_mutex_lock(&pool->queue_access.mutex);
		if (pool->queue == NULL)	//if there is no task in queue
		{
			printf("Thread %zu going to sleep\n", id);
			pthread_mutex_unlock(&pool->queue_access.mutex);
			wait_cond(&pool->awake_thread);
			printf("Thread %zu has awaken\n", id);
		}
	}
	pthread_exit(NULL);
}

void	wait_cond(t_vars *var)
{
	pthread_mutex_lock(&(*var).mutex);
	pthread_cond_wait(&(*var).cond, &(*var).mutex);
	pthread_mutex_unlock(&(*var).mutex);
}

void	change_mutex_var(t_vars *var, int val)
{
	pthread_mutex_lock(&(*var).mutex);
	(*var).val += val;
	pthread_cond_signal(&(*var).cond);
	pthread_mutex_unlock(&(*var).mutex);
}

void	t_var_init(t_vars *var)
{
	(*var).val = 0;
	pthread_mutex_init(&(*var).mutex, NULL);
	pthread_cond_init(&(*var).cond, NULL);
}
