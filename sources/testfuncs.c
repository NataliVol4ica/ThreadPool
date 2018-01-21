
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	*counter_func(void *param)
{
	size_t	from;
	size_t	i;

	from = *(size_t*)(param);
	printf("Got %zu\n", from);
	i = -1;
	while (++i < 100)
	{
		from++;
	}
	printf("Counted %zu\n", from);
	return (NULL);
}
