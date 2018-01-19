
#include "threadpool.h"
#include <stdio.h>

void	*thread_function(void *arg)
{
	t_thread_pool *pool;

	pool = (t_thread_pool*)arg;
	change_mutex_var(&pool->num_of_threads, 1);
	pthread_exit(NULL);
}

void	wait_cond(t_vars *var)
{
	pthread_cond_wait(&(*var).cond, &(*var).mutex);
}

void	change_mutex_var(t_vars *var, int val)
{
	pthread_mutex_lock(&(*var).mutex);
	(*var).val += val;
//	printf("Val got %zu\n", var->val);
	pthread_cond_signal(&(*var).cond);
	pthread_mutex_unlock(&(*var).mutex);
}

void	t_var_init(t_vars *var)
{
	(*var).val = 0;
	pthread_mutex_init(&(*var).mutex, NULL);
	pthread_cond_init(&(*var).cond, NULL);
}
