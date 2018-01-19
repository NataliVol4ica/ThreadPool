
#include "threadpool.h"
#include <stdio.h>

void	*thread_function(void *arg)
{
	printf("Creating thread\n");
	pthread_exit(NULL);
}
