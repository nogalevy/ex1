//shell

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

const int MAX_LEN = 100;

void check_argv(int argc);
FILE * open_file(char* filename,  char *mode);
void write_commands(FILE **fp, char* filename);
void close_file(FILE **fp);


int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	open_file(argv[1], "r+");
	check_argv(argc);
	write_commands(&fp, argv[1]);
	close_file(&fp);
	unlink(argv[1]);

	return EXIT_SUCCESS;
}

void check_argv(int argc)
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


void write_commands(FILE **fp, char* filename)
{
	char line[MAX_LEN];
	pid_t pid;

	scanf("%s", line);

	while(!(strcmp(line, "history") == 0 ||
					strncmp(line, "echo", 4) == 0 ||
					strncmp(line,"ps", 2) == 0 ||
					strcmp(line, "exit") == 0))
	{
		perror("bad command\n");
		scanf("%s", line);
	}


	while(strcmp(line, "exit") != 0)
	{
		fprintf(fp, "%s\n", line);
		pid = fork();

		if(pid < 0)
		{
			perror("Cannot fork()");
			exit (EXIT_FAILURE);
		}

		if(pid == 0)
		{
			if(strncmp(line, "history", 7) == 0)//history
			{
				if(execlp("./history", "history", filename, NULL) != 0)
				{
					perror("execlp() failed");
					exit(EXIT_FAILURE);
				}
			}
			if(strncmp(line, "echo", 4) == 0)
			{
				//send only part of line.. how?

				if(execlp("./echo", "echo", line , NULL) != 0)
				{
					perror("execlp() failed");
					exit(EXIT_FAILURE);
				}
			}
			if(strncmp(line,"ps", 2) == 0)
			{
				if(strcmp(line, "ps") == 0)
				{
					if(execlp("./ps", "ps",NULL) != 0)
					{
						perror("execlp() failed");
						exit(EXIT_FAILURE);
					}

				}
				else
				{
					if(execlp("./ps", "ps", line ,NULL) != 0)
					{
						perror("execlp() failed");
						exit(EXIT_FAILURE);
					}
				}
			}
		}
		scanf("%s", line);
	}
}


//function closes file
void close_file(FILE **fp)
{
    int res = fclose(*fp);
	//checks if action failed
	if(res !=0)
		printf("Error!\n");
}
