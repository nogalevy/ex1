//history
/*

Files: ex1b1.c 
Shell Commands Running from File
=====================================================================
Written by: Tali Kalev, ID:208629691, Login: talikal
		and	Noga Levy, ID:315260927, Login: levyno

ex1b1.c
history command handler
prints the history of the commands -
This program receives via the argument vector the name of a file.
The program then reads line by line the information in the file and
prints it on the screen.


Compile: gcc -Wall ex1b1.c -o history

*/

// -------include section-----------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>

// -------prototype section-----------------------
void check_argv(int argc);
FILE * open_file(char* filename,  char *mode);
void read_print_file(FILE *fp);
void close_file(FILE **fp);

//---------main section---------------------------
int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	check_argv(argc);
	fp = open_file(argv[1], "r+");

	read_print_file(fp);
	close_file(&fp);

	return EXIT_SUCCESS;
}

//------------------------------------------------

void check_argv(int argc )
{
	if(argc != 2)
	{
		printf("ERROR");
		exit(EXIT_FAILURE);
	}
}

//------------------------------------------------

FILE * open_file(char* filename,  char *mode)
{
	FILE *fp = fopen(filename, mode);

	if (fp == NULL)
	{
		printf("Error! cannot open %s  ", filename);
		exit (EXIT_FAILURE);
	}
    return fp;
}

//------------------------------------------------

void read_print_file(FILE *fp)
{
	size_t size = 0;
	char* line = NULL;

	getline(&line, &size, fp);

	while(!feof(fp))
	{
		printf("%s",line);
		getline(&line, &size, fp);
	}
}

//------------------------------------------------

//function closes file
void close_file(FILE **fp)
{
    int res = fclose(*fp);

	//checks if action failed
	if(res !=0)
		printf("Error!\n");
}
