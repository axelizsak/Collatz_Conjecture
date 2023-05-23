#include <stdlib.h>
#include <stdio.h>

// Function to convert an integer to binary
void	int2bin(int n, int *bin)
{
	for (int i = 31; i >= 0; i--)
	{
		bin[i] = n % 2;
		n /= 2;
	}
}

// Function to convert a binary number to an integer
int	bin2int(int *bin)
{
	int	decimal = 0;
	int	multiplier = 1;
	for (int i = 31; i >= 0; i--)
	{
		decimal += bin[i] * multiplier;
		multiplier *= 2;
	}
	return decimal;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("\033[0;31mwrong arg\033[0m\n");
		return (0);
	}
	
	int	i = 1;
	int	*n = (int *)malloc((argc - 1) * sizeof(int)); // Allocate memory for n array
	int	**bin = (int **)malloc((argc - 1) * sizeof(int *)); // Allocate memory for bin array of pointers
	
	// Loop through command-line arguments and convert them to integers and binary arrays
	while  (i < argc)
	{
		n[i - 1] = atoi(argv[i]);
		bin[i - 1] = (int *)malloc(32 * sizeof(int)); // Allocate memory for binary array
		int2bin(n[i - 1], bin[i - 1]);
		i++;
	}
	
	// Check Criteria 1 : Do we have a binary representation of the first term of the collatz trace?
	int test1 = bin2int(bin[0]) - n[0];
	if (test1 == 0)
		printf("\033[0;32mCriteria 1 : ok\033[0m\n");
	else
		printf("\033[0;31mCriteria 1 : Error\033[0m\n");
	
	// Check Criteria 2 : Is the last term a binary representation of 1?
	int test2 = bin2int(bin[argc - 2]) - 1;
	if (test2 == 0)
		printf("\033[0;32mCriteria 2 : ok\033[0m\n");
	else
		printf("\033[0;31mCriteria 2 : Error\033[0m\n");
	
	// Check Criteria 3 : Does the trace contain only bits? (a number is equal to its square if and only if it is 0 or 1).
	int	k = 1;
	for (int i = 0; i < argc - 1; i++)
	{
		int squared_diff = 0;
		for (int j = 0; j < 32; j++)
		{
			squared_diff += bin[i][j] * bin[i][j] - bin[i][j];
		}
		if (squared_diff != 0)
		{
			printf("\033[0;31mCriteria 3 : Error -> %ls not binary.\033[0m\n", bin[i]);
			k--;
		}
	}
	if (k == 1)
		printf("\033[0;32mCriteria 3 : ok\033[0m\n");
	
	// Check Criteria 4 : Is the collatz rule verified between each number?
	int	z = 1;
	for (int i = 0; i < argc - 2; i++)
	{
		int bin1 = bin2int(bin[i]);
		int bin2 = bin2int(bin[i+1]);
		int result = 0;
		if (bin1 % 2 == 0)
			result = (bin1 - 2 * bin2);
		else
			result = (3 * bin1 + 1) - bin2;
		if (result != 0)
		{
			printf("\033[0;31mCritère 4 : Error -> %d %d.\033[0m\n", n[i], n[i+1]);
			z--;
		}
	}
	if (z == 1)
		printf("\033[0;32mCritère 4 : ok\033[0m\n");
	
	printf("\n");
	if (test1 == 0 && test2 == 0 && k == 1 && z == 1)
		printf("This is a Collatz sequence\n");
	else
		printf("This is not a Collatz sequence\n");
	printf("\n");

	// Free allocated memory
	for (i = 0; i < argc - 1; i++)
		free(bin[i]);
	free(bin);
	free(n);
	return 0;
}
