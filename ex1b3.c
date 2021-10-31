//ps or ps -a

// -------include section-----------------------
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// ------- prototype section-----------------------
void check_and_print(int argc, char *argv[]);

// ------- main section-----------------------
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
		case 1: //ps
			printf("Current pid: %d\n", getpid());
			return;
		case 2: //ps -a
			printf("Parent pid: %d Current pid %d\n", getppid(), getpid());
			return;
		default:
			printf("Program failed\n");
			return;
	}
}
