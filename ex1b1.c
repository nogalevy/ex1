//history

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>

const int MAX_LEN = 100;

void check_argv(int argc);
FILE * open_file(char* filename,  char *mode);
void read_print_file(FILE *fp);
void close_file(FILE **fp);

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	check_argv(argc);
	open_file(argv[1], "r+");
	read_print_file(fp);
	close_file(&fp);

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

FILE * open_file(char* filename,  char *mode)
{
	FILE *fp = fopen(filename, mode);

	//if unsuccessful stops program
	if (fp == NULL)
	{
		printf("Error! cannot open %s  ", filename);
		exit (EXIT_FAILURE);
	}
    return fp;
}

void read_print_file(FILE *fp)
{
	char line[MAX_LEN];
	
	while(fgets(line, sizeof(line), fp) != NULL)
		printf("%s\n",line);
}

//function closes file
void close_file(FILE **fp)
{
    int res = fclose(*fp);

	//checks if action failed
	if(res !=0)
		printf("Error!\n");
}