//echo

// -------include section-----------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>

// -------prototype section-----------------------
void check_argv(int argc);
void print_string(char *string);

// -------main section-----------------------
int main(int argc, char *argv[])
{
	check_argv(argc);
	print_string(argv[1]);

	return EXIT_SUCCESS;
}

//------------------------------------------------

void check_argv(int argc)
{
	if(argc != 2)
	{
		printf("ERROR");
		exit(EXIT_FAILURE);
	}
}

//------------------------------------------------

void print_string(char *string)
{
	printf("%s\n", string);
}
