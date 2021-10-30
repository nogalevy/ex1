
// --------include section------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>
#include <time.h> //for clock()

const int SIZE = 50000;

// -------prototype section-----------------------
FILE* open_file(char* argv,  char *mode);
void close_file(FILE **fp);
void check_argv(int argc );
void calc_sort_times(char *filename);
void bubblesort(int arr[], FILE *fp);
void quicksort(int arr[], file *fp);
void parent_calc(FILE *fp);

//---------main section---------------------------

int main(int argc, char *argv[])
{
	clock_t time_req = clock();
	
	check_argv(argc);
	srand(atoi(argv[2])); //needed atoi?
	calc_sort_times(argv[1]);
	
	time_req = (double)(clock() - time_req)/CLOCKS_PER_SEC;
	printf("%d\n", time_req);

	return EXIT_SUCCESS;
}

//------------------------------------------------

//function opens file and checks that process was completed successfully
FILE * open_file(char* filename,  char *mode) //2 stars for filename??
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

void calc_sort_times(char *filename) 
{
	int i,j,k;
	pid_t pid;
	int child_id
	FILE *fp = open_file(filename, "r+"); //r or r+? and should we send &filename?

	for(i = 0; i < 50; i++)
	{
		static int arr[SIZE];

		for(j = 0; j < SIZE; j++)
			arr[j] = rand();

		for(k = 0; k < 2; k++)
		{
			pid = fork();

			if(pid < 0)
			{
				perror("Cannot fork()");
				exit (EXIT_FAILURE);
			}

			if(pid == 0)
			{
				if(k == 0)
					bubblesort(arr, &fp);
				else
					quicksort(arr, &fp);

				exit(EXIT_SUCCESS);
			}
		}
		for(k = 0; k < 2; k++)
			child_id = wait(&pid);  //another way?

	}
	parent_calc(fp);
	close_file(&fp);
	 //unlink?????????
	unlink(filename);
}
//------------------------------------------------

void bubblesort(int arr[], FILE *fp)
{
	//Check inital time
	//sort
	//check finishing time
	//add to file: 1. "b" for bubble sort 2. time it took to sort and new line?

	clock_t time_req = clock();

	//sort

	time_req = (double)(clock() - time_req)/CLOCKS_PER_SEC;
	fprintf(fp, "%c %lf\n", "b", time_req);
}

void quicksort(int arr[], file *fp)
{
	//check inital time
	//sort
	//check finishing time
	//add to file 1. "q" for quick sort 2. time it took to sort and new line?

	clock_t time_req = clock()

	//sort

	time_req = (double)(clock() - time_req)/CLOCKS_PER_SEC;
	fprintf(fp, "%c %lf\n", "q", time_req);
}

void parent_calc(FILE *fp)
{
	//puts pointer to start of file
	//define variables: sum_bsort, sum_qsort, min_bsort, min_qsort, max_bsort, max_qsort;
	//start loop to read characters and numbers
	//after b, read number, compare to max/min, add to sum;
	//after q, read number, compare to max/min, add to sum;
	//when out of loop print to output "average time for bsort", "average time for qsort", "min time for bsort", "min time for qsort", "max for bsort", "max for qsort" new line

	double sum_bsort, sum_qsort, min_bsort, min_qsort, max_bsort, max_qsort, curr; //what are starting values of min??
	char type;

	sum_bsort = sum_qsort = max_bsort = max_qsort = 0;

	fseek(fp, 0, SEEK_SET);

	fscanf(fp, "%c", type);

	while(!feof(fp))
	{
		fscanf(fp, "%lf" curr);

		if(strcmp(type, "b") == 0)
		{
			if(curr < min_bsort)
				min_bsort = curr;
			if(curr > max_bsort)
				max_bsort = curr;
			sum_bsort += curr; 
		}
		else
		{
			if(curr < min_bsort)
				min_bsort = curr;
			if(curr > max_bsort)
				max_bsort = curr;
			sum_bsort += curr; 	
		}

		fscanf(fp, "%c", type);
	}

	printf("%lf %lf %lf %lf %lf %lf", sum_bsort, sum_qsort, min_bsort, min_qsort, max_bsort, max_qsort);
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

//------------------------------------------------

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
