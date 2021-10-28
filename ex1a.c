/*
	File: ex0a.c
Reading Data from Input file into 2D Array and Locating Maximum Line
=====================================================================
Written by: Tali Kalev, ID:208629691, Login: talikal
		and	Noga Levy, ID:315260927, Login: levyno

This program receives the name of an input and output file into the argument
vector. The program opens both files and reads data from the input file into a
2D dynamic array. The program then locates the "Max Line" in the 2D array and
prints the index of that line into the output file. The max line is represented
by the line in which the value in column j is larger than or equal to the
value in the same column j of all the other rows. If no max line is found, the
program prints the value -1 into the output file.

Complie: gcc -Wall ex0a.c -o ex0a
Run: ex0a

Input: An array where the first digit in each line represents the number
	   of digits in that line.
	   Example:
	   2 5 15
	   3 12 17 0
	   1 9
	   5 11 16 -2 38 79

Output: The index of the row that meets the requirements of "Max Line".
		Example:
		1

*/


// --------include section------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int SIZE = 50000;

// -------prototype section-----------------------
FILE* open_file(char* argv,  char *mode);
void print_file(FILE *ofp, int row_ind);
void close_file(FILE **fp);
void check_argv(int argc );

//---------main section---------------------------
int main(int argc, char *argv[])
{
	FILE *fp = NULL; // input file pointer

	check_argv(argc);
	srand(argv[2]);
	fp = open_file(argv[1], "r");
	create_parent(argv[1]);

	print_file(fp, row_ind); // print result in output file

	free_array(&data);
	close_file(&ifp);
	close_file(&ofp);

	return EXIT_SUCCESS;
}

//------------------------------------------------

//function opens file and checks that process was completed successfully
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

//-------------------------------------------------

void create_parent(char *filename)
{
	int i,j,k, kid[2];
	for(i = 0; i < 50; i++)
	{
		static int arr[SIZE];

		for(j = 0; j < SIZE; j++)
			arr[j] = rand();

		for(k = 0; k < 2; k++)
		{
			kid[k] = fork();

			if(kid[k] == 0)
				//do something

		}

	}
}
//------------------------------------------------

//function receives index of max row and prints into output file
void print_file(FILE *ofp, int row_ind)
{
	fprintf(ofp, "%d", row_ind);
}

//------------------------------------------------

/* BS = 
for (c = 0 ; c < n - 1; c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (array[d] > array[d+1])  For decreasing order use '<' instead of '>' 
      {
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
      }
    }
  }


void quicksort(int number[25],int first,int last){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);

   }
}








*/






//------------------------------------------------

//function closes file
void close_file(FILE **fp)
{
    int res = fclose(*fp);

	//checks if action failed
	if(res !=0)
		printf("Error!\n");
}

//------------------------------------------------\



//function checks that both input file and output file names are
//given in argument vector
void check_argv(int argc )
{
	if(argc != 3)
	{
		printf("ERROR");
		exit(EXIT_FAILURE);
	}
}
