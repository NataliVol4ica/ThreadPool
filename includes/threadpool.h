#ifndef THREADPOOL_H
# define THREADPOOL_H

# include "structures.h"

t_thread_pool	*create_thread_pool(size_t num_of_threads);
void			stop_thread_pool(t_thread_pool	*pool);
void			add_task(t_thread_pool *pool, void *(*func)(void*), void *param);

void			*counter_func(void *param);

void			*thread_function(void *arg);
void			wait_cond(t_vars *var);
void			change_mutex_var(t_vars *var, int val);
void			t_var_init(t_vars *var);

/*
** ERRORS
*/

void			malloc_error(void);
void			thread_error(void);
void			fork_error(void);

#endif
