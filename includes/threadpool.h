#ifndef THREADPOOL_H
# define THREADPOOL_H

# include "structures.h"

t_thread_pool	*create_thread_pool(size_t num_of_threads);

void		*thread_function(void *arg);

/*
** ERRORS
*/

void			malloc_error(void);
void			thread_error(void);

#endif
