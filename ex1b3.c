//ps or ps -a

/*
Files: exb3.c 
Shell Commands Running from File
=====================================================================
Written by: Tali Kalev, ID:208629691, Login: talikal
		and	Noga Levy, ID:315260927, Login: levyno

ex1b3.c
ps command handler
print the proccess id-
This program can either receive no arguments via the argument vector or one.
If the program recieves none then it will print the process ID of the current
process. If the program receives an argument (other than the name of the file)
then it will print the process ID of the current and parent process.

Compile:  gcc -Wall ex1b3.c -o ps
		 

*/

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
