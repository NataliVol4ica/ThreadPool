
#include <unistd.h>
#include <stdlib.h>

void	malloc_error(void)
{
	write(1, "Malloc fail. Exiting program\n", 29);
	exit (1);
}

void	thread_error(void)
{
	write(1, "Thread creation fail. Exiting program\n", 38);
	exit (1);
}

void	fork_error(void)
{
	write(1, "Fork creation fail. Exiting program\n", 38);
	exit (1);
}
