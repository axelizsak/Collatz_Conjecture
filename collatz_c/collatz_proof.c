#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int     i;
	i = atoi(argv[1]);
	if (i < 1)
		return (0);
	while (i > 1)
	{
		if (i%2 == 0)
		{
			printf("%d ", i);
			i = i/2;
		}
		else if (i%2 != 0)
		{
			printf("%d ", i);
			i = 3 * i + 1;
		}
	}
	printf("%d\n", i);
}
