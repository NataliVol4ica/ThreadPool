
#include "threadpool.h"
#include <stdio.h>

void	*thread_function(void *arg)
{
	t_thread_pool	*pool;
	size_t			id;

	pool = (t_thread_pool*)arg;
	pthread_mutex_lock(&pool->num_of_threads.mutex);
	pool->num_of_threads.val += 1;
	id = pool->num_of_threads.val;
	pthread_cond_signal(&pool->num_of_threads.cond);
	pthread_mutex_unlock(&pool->num_of_threads.mutex);
	while (1)
	{
		wait_cond(&pool->awake_thread);
		pthread_mutex_lock(&pool->quit_pool.mutex);
		if (pool->quit_pool.val == 1)
		{
			pthread_mutex_unlock(&pool->quit_pool.mutex);
			break;
		}
		pthread_mutex_unlock(&pool->quit_pool.mutex);
		change_mutex_var(&pool->num_of_active_threads, 1);
		//run getting task from list here
		change_mutex_var(&pool->num_of_active_threads, -1);
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
