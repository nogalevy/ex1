//echo
/*

Files: ex1b2.c
Shell Commands Running from File
=====================================================================
Written by: Tali Kalev, ID:208629691, Login: talikal
		and	Noga Levy, ID:315260927, Login: levyno

ex1b2.c
echo command handler
print string-
This program receives via the argument vector a string. The program
then prints this string on the screen.

Compile: gcc -Wall ex1b2.c -o echo
		

*/
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
