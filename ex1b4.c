/*

Files: ex1b1.c ex1b2.c exb3.c exb4.c
Shell Commands Running from File
=====================================================================
Written by: Tali Kalev, ID:208629691, Login: talikal
		and	Noga Levy, ID:315260927, Login: levyno

ex1b4.c
This program receives a series of commands from the user. The program
reads these commands and writes them into a file that it receives via
the argument vector. If the user types "history", "echo", or "ps" then
the program runs the matching executable file. The program finishes when
the user inputs "exit" as a command. 

ex1b1.c
history command handler
prints the history of the commands -
This program receives via the argument vector the name of a file.
The program then reads line by line the information in the file and
prints it on the screen.

ex1b2.c
echo command handler
print string-
This program receives via the argument vector a string. The program
then prints this string on the screen.

ex1b3.c
ps command handler
print the proccess id-
This program can either receive no arguments via the argument vector or one.
If the program recieves none then it will print the process ID of the current
process. If the program receives an argument (other than the name of the file)
then it will print the process ID of the current and parent process.


Compile: gcc -Wall ex1b1.c -o history
		 gcc -Wall ex1b2.c -o echo
		 gcc -Wall ex1b3.c -o ps
		 gcc -Wall ex1b4.c -o shell

Run: ./shell <filename>

Input: When running the file: ./shell <filename>
		and then a list of commands.	
		Example: echo hello
				 exit


Output: The string after echo is printed.
		Example: hello
*/

// -------include section-----------------------
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

// -------include section-----------------------
const int MAX_LEN = 100;

const char C_HISTORY[] = "history"; //command history
const char C_PS[] = "ps"; //command ps
const char C_ECHO[] = "echo"; //command echo
const char C_EXIT[] = "exit"; //command exit

// -------prototype section-----------------------
void check_argv(int argc);
FILE * open_file(char* filename,  char *mode);
void write_commands(FILE **fp, char* filename);
void close_file(FILE **fp);
void error_exec();
bool is_valid_input(char *line);

// -------main section-----------------------
int main(int argc, char *argv[])
{
	FILE *fp;
	fp = open_file(argv[1], "w+");

	check_argv(argc);
	write_commands(&fp, argv[1]);
	close_file(&fp);
	unlink(argv[1]);

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


//------------------------------------------------

void write_commands(FILE **fp, char* filename)
{
	char line[MAX_LEN];
	pid_t pid;

	fgets(line, MAX_LEN, stdin);
	line[strlen(line) - 1] = '\0';

	while(!is_valid_input(line))
	{
		perror("bad command\n");

		fgets(line, MAX_LEN, stdin);
		line[strlen(line) - 1] = '\0';
	}
	char path[] = "./";

	while(strcmp(line, C_EXIT) != 0)
	{
		pid = fork();

		if(pid < 0)
		{
			perror("Cannot fork()");
			exit (EXIT_FAILURE);
		}

		if(pid == 0)
		{
			if(strncmp(line, C_HISTORY, 7) == 0)//history
			{
				if(execlp(strcat(path, C_HISTORY), C_HISTORY, filename, NULL) != 0)	error_exec();
			}

			else if(strncmp(line, C_ECHO, 4) == 0) //echo
			{
				//remove the 'echo' part and save the rest of the string
				char *new_line = line;
				while (*new_line != 0 && *(new_line++) != ' ') {}

				if(execlp(strcat(path, C_ECHO), C_ECHO, new_line , NULL) != 0)	error_exec();
			}

			else if(strncmp(line, C_PS, 2) == 0) //ps or ps -a
			{
				if (strlen(line) == 2 ) //ps
				{
					if(execlp(strcat(path, C_PS), C_PS, NULL) != 0)	error_exec();
				}
				else //ps -a
				{
					if(execlp(strcat(path, C_PS), C_PS, line ,NULL) != 0) error_exec();
				}
			}
			exit(EXIT_SUCCESS);
		}

		wait(NULL);
		fprintf(*fp, "%s\n", line); // when finishrd print line in file
		fflush(*fp);

		fgets(line, MAX_LEN, stdin); //gets new line from user
		line[strlen(line) - 1] = '\0'; // delete \n from line
	}
}

//-----------------------------------------

void error_exec()
{
	perror("execlp() failed");
	exit(EXIT_FAILURE);
}

//-----------------------------------------

//function closes file
void close_file(FILE **fp)
{
    int res = fclose(*fp);

	//checks if action failed
	if(res !=0)
		printf("Error!\n");
}

//-----------------------------------------

bool is_valid_input(char *line)
{
	return (strcmp(line, C_HISTORY) == 0 ||
					strncmp(line, C_ECHO, 4) == 0 ||
					strncmp(line, C_PS, 2) == 0 ||
					strcmp(line, C_EXIT) == 0);
}
