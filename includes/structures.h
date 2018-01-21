#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <pthread.h> 
# include <string.h>

typedef struct	s_thread
{
	pthread_t	thread;
	size_t		id;
}				t_thread;

typedef struct	s_task
{
	void			*(*func)(void*);
	void			*param;
	struct s_task	*next_task;
}				t_task;

typedef struct	s_vars
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	volatile size_t val;
}				t_vars;

typedef struct	s_thread_pool
{
	t_thread	*threads;
	t_task		*queue;
	t_vars		num_of_threads;
	t_vars		num_of_active_threads;
	t_vars		awake_thread;
	t_vars		quit_pool;
	t_vars		queue_access;
}				t_thread_pool;

#endif
