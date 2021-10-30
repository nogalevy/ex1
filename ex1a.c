// --------include section------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>
#include <time.h> //for clock()

// ----------- const section ---------------------
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
	int i, j, k, child_id;
	pid_t pid;
	FILE *fp = open_file(filename, "r+"); //r or r+? and should we send &filename?

	//run 50 times
	for(i = 0; i < 50; i++)
	{
		static int arr[SIZE]; // not sure

		//insert data to array - can move to function
		for(j = 0; j < SIZE; j++)
			arr[j] = rand();

		//create two child proccess
		for(k = 0; k < 2; k++)
		{
			pid = fork();

			if(pid < 0) // handle error in fork()
			{
				perror("Cannot fork()");
				exit (EXIT_FAILURE);
			}

			if(pid == 0) //if child
			{
				if(k == 0)
					bubblesort(arr, &fp);
				else
					quicksort(arr, &fp);

				exit(EXIT_SUCCESS);
			}
		}
		//parent wait to both children
		for(k = 0; k < 2; k++)
			child_id = wait(&pid);  //another way?
	}

	parent_calc(fp);
	close_file(&fp);
	unlink(filename); //unlink?????????
}

//------------------------------------------------

void handle_bubble_sort(int arr[], FILE *fp)
{
	//Check inital time
	//sort
	//check finishing time
	//add to file: 1. "b" for bubble sort 2. time it took to sort and new line?
	int step, i;
	clock_t time_req = clock();

	//bubble sort from - https://www.programiz.com/dsa/bubble-sort
	bubble_sort(arr);
	time_req = (double)(clock() - time_req)/CLOCKS_PER_SEC;
	fprintf(fp, "%c %lf\n", "b", time_req);
}

void handle_quick_sort(int arr[], file *fp)
{
	//check inital time
	//sort
	//check finishing time
	//add to file 1. "q" for quick sort 2. time it took to sort and new line?
	int i, j, pivot, temp;
	clock_t time_req = clock()

	//quick sort
	quick_sort(arr, first,int last);
	time_req = (double)(clock() - time_req)/CLOCKS_PER_SEC;
	fprintf(fp, "%c %lf\n", "q", time_req);
}

//------------------------------------------------

void bubble_sort(int arr[])
{
	// loop to access each array element
	for (step = 0; step < SIZE - 1; ++step) {
		// loop to compare array elements
		for (i = 0; i < SIZE - step - 1; ++i) {
			// compare two adjacent elements
			// change > to < to sort in descending order
			if (arr[i] > arr[i + 1]) {
				// swapping occurs if elements
				// are not in the intended order
				int temp = array[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
}

//------------------------------------------------

void quick_sort(int arr[], int first_i, int last_i)
{
    if(first_i < last_i)
    {
        int q;
        q = partition(arr, first_i, last_i);
        quicksort(arr, first_i, q-1);
        quicksort(arr, q+1, last_i);
    }
}

//------------------------------------------------

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];  // selecting last element as pivot
    int i = (low - 1);  // index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If the current element is smaller than or equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

//------------------------------------------------

void parent_calc(FILE *fp)
{
	//- puts pointer to start of file
	//- define variables: sum_bsort, sum_qsort, min_bsort, min_qsort, max_bsort, max_qsort;
	//- start loop to read characters and numbers
	//- after b, read number, compare to max/min, add to sum;
	//- after q, read number, compare to max/min, add to sum;
	//- when out of loop print to output "average time for bsort",
	//	"average time for qsort", "min time for bsort", "min time for qsort", "max for bsort",
	// 	"max for qsort" new line

	double sum_bsort, sum_qsort, min_bsort, min_qsort, max_bsort, max_qsort, curr; //what are starting values of min??
	char type;

	sum_bsort = sum_qsort = max_bsort = max_qsort = 0; //reset all (min_bsort and min_qsort ?)

	fseek(fp, 0, SEEK_SET); //moves file pointer position to the beginning of the file
	fscanf(fp, "%c", type); //read char from file into 'type' variable

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
	//add calc avarage
	printf("%lf %lf %lf %lf %lf %lf", sum_bsort, sum_qsort, min_bsort, min_qsort, max_bsort, max_qsort);
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

//------------------------------------------------

// to swap two numbers
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
