//echo

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>

const int MAX_LEN = 100;

void check_argv(int argc);
void print_string(char *string);

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	check_argv(argc);
	print_string(arcv[1]);

	return EXIT_SUCCESS;
}

void check_argv(int argc )
{
	if(argc != 2)
	{
		printf("ERROR");
		exit(EXIT_FAILURE);
	}
}

void print_string(char *string)
{
	printf("s", string);
}