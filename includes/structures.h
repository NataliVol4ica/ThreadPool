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

typedef struct	s_queue
{
	t_task	*first_task;
	size_t	num_of_tasks;
}				t_queue;

typedef struct	s_thread_pool
{
	t_thread		*threads;
	t_queue			*queue;
	pthread_mutex_t	lock_num_of_threads;
	pthread_cond_t	cond_num_of_threads;
	volatile size_t	num_of_threads;
	pthread_mutex_t	lock_num_of_active_threads;
	volatile size_t	num_of_active_threads;
}				t_thread_pool;

#endif
