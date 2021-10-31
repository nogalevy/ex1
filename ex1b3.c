//ps or ps -a

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void check_and_print(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	check_and_print(argc, argv);
	return EXIT_SUCCESS;
}

//------------------------------------------------

void check_and_print(int argc, char *argv[])
{
	switch(argc)
	{
		case 1:
			printf("Current pid: %d\n", getpid());
			return;
		case 2:
			printf("Parent pid: %s Current pid %d\n", getppid(), getpid());
			return;
		default:
			printf("Program failed\n");
			return;
	}
}
