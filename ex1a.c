
// --------include section------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //?
#include <sys/types.h>
//#include <time.h> //for clock()
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

// ----------- const section ---------------------

const int SIZE = 50000;
const int NUM_OF_LOOPS = 50;

// -------prototype section-----------------------

FILE* open_file(char* argv,  char *mode);
void close_file(FILE **fp);
void check_argv(int argc );
void calc_sort_times(char *filename);
void bubble_sort(int arr[]);
void quick_sort(int arr[], int first_i, int last_i);
void parent_calc(FILE *fp);
void randomize_array(int arr[]);
void handle_child(int child_num, int arr[], FILE **fp);
void handle_bubble_sort(int arr[], FILE ***fp);
void handle_quick_sort(int arr[], FILE ***fp);
int partition (int arr[], int low, int high);
void swap(int* a, int* b);

//---------main section---------------------------

int main(int argc, char *argv[])
{
	struct timeval t0, t1;
	gettimeofday(&t0, NULL); //calculating start time
	
	check_argv(argc);
	srand(atoi(argv[2])); 
	calc_sort_times(argv[1]); 

	gettimeofday(&t1, NULL); //calculating end time
	//printing time parent took to run
	printf("%f\n",(double)(t1.tv_usec - t0.tv_usec)/1000000 +
									(double)(t1.tv_sec - t0.tv_sec));

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
		printf("Error! cannot open %s  \n", filename);
		exit (EXIT_FAILURE);
	}
    return fp;
}

//-------------------------------------------------

//function receives filename and calculates sort time
//of bubble and quick sort via children
void calc_sort_times(char *filename)
{
	int i, j;
	pid_t pid;
	int arr[SIZE];
	FILE *fp = open_file(filename, "w+");

	for(i = 0; i < NUM_OF_LOOPS; i++)
	{
		randomize_array(arr); //putting random numbers in array

		//create two child proccess
		for(j = 0; j < 2; j++)
		{
			pid = fork();

			if(pid < 0) // handle error in fork()
			{
				perror("Cannot fork()");
				exit (EXIT_FAILURE);
			}

			if(pid == 0) //if child
				handle_child(j, arr, &fp);
		}
		//parent wait for both children
		for(j = 0; j < 2; j++)
			wait(NULL);
	}

	parent_calc(fp); //parent prints data from file
	close_file(&fp);
	unlink(filename); //deleting file
}

//------------------------------------------------

//function receives child number, randomized array and opened file
//appropriate child sorts accordingly
void handle_child(int child_num, int arr[], FILE **fp)
{
	if(child_num == 0)
		handle_bubble_sort(arr, &fp);
	else
		handle_quick_sort(arr, &fp);

	exit(EXIT_SUCCESS); //child ends process
}

//------------------------------------------------

//function recieves array and enters randomized numbers into it
void randomize_array(int arr[])
{
	int index;
	
	for(index = 0; index < SIZE; index++)
		arr[index] = (rand() % 1000); 
}

//------------------------------------------------

//function receives array and file, sorts array and puts calculated
//run time into file
void handle_bubble_sort(int arr[], FILE ***fp)
{
	struct timeval t0, t1;
	
	gettimeofday(&t0, NULL);
	bubble_sort(arr);
	gettimeofday(&t1, NULL);
	fprintf(**fp, "%s %f\n", "b", (double)(t1.tv_usec - t0.tv_usec)/1000000 +
									(double)(t1.tv_sec - t0.tv_sec));
}

//------------------------------------------------

//function receives array and file, sorts array and puts calculated
//run time into file
void handle_quick_sort(int arr[], FILE ***fp)
{
	int first = 0, last = SIZE -1;
	struct timeval t0, t1;
	
	gettimeofday(&t0, NULL);
	quick_sort(arr, first, last);
	gettimeofday(&t1, NULL);
	fprintf(**fp, "%s %f\n", "q", (double)(t1.tv_usec - t0.tv_usec)/1000000 +
									(double)(t1.tv_sec - t0.tv_sec));
}
//------------------------------------------------

//function receives array and sorts it using the bubble sort algorithm
void bubble_sort(int arr[])
{
	int step, i, temp;
	// loop to access each array element
	for (step = 0; step < SIZE - 1; ++step) {
		// loop to compare array elements
		for (i = 0; i < SIZE - step - 1; ++i) {
			// compare two adjacent elements
			// change > to < to sort in descending order
			if (arr[i] > arr[i + 1]) {
				// swapping occurs if elements
				// are not in the intended order
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
}

//------------------------------------------------

//function receives array, starting and ending point and sorts the array
//using the quick sort algorithm
void quick_sort(int arr[], int first_i, int last_i)
{
    if(first_i < last_i)
    {
        int q;
        q = partition(arr, first_i, last_i);
        quick_sort(arr, first_i, q-1);
        quick_sort(arr, q+1, last_i);
    }
}

//------------------------------------------------

//function receives array and partitions accordingly
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

//function receives file filled with run time data and prints
//out average, min and max of all run time data 
void parent_calc(FILE *fp)
{
	double sum_bsort, sum_qsort, min_bsort, min_qsort, 
				max_bsort, max_qsort, curr; 
	char type;

	//setting initial values
	sum_bsort = sum_qsort = max_bsort = max_qsort = 0;
	min_qsort = min_bsort = 100;

	//returning to start of file
	rewind(fp);
	fscanf(fp, "%c", &type); //read char from file into 'type' variable

	while(!feof(fp))
	{
		//read data about specific sorting algorithm
		fscanf(fp, "%lf", &curr);

		if(type == 'b') //if bubble sort
		{
			//compares numbers and adds to sum
			if(curr < min_bsort)
				min_bsort = curr;
			if(curr > max_bsort)
				max_bsort = curr;
			sum_bsort += curr;
		}
		else	//if quick sort
		{
			//compares numbers and adds to sum
			if(curr < min_qsort)
				min_qsort = curr;
			if(curr > max_qsort)
				max_qsort = curr;
			sum_qsort += curr;
		}

		//read next sort type
		fscanf(fp, "%c", &type); 
	}
	//dividing sums to get average
	sum_bsort /= NUM_OF_LOOPS;
	sum_qsort /= NUM_OF_LOOPS;
	
	//prints onto screen values calculated
	printf("%lf %lf %lf %lf %lf %lf\n", sum_bsort, sum_qsort, min_bsort, 
													min_qsort, max_bsort, max_qsort);
	
}


//------------------------------------------------

//function closes file
void close_file(FILE **fp)
{
  int res = fclose(*fp);
	//checks if action failed
	if(res !=0)
		printf("Error! Failed to close file.\n");
}

//------------------------------------------------

//function checks that both input file and output file names are
//given in argument vector
void check_argv(int argc )
{
	if(argc != 3)
	{
		printf("Error! Incorrect number of arguments.\n");
		exit(EXIT_FAILURE);
	}
}

//------------------------------------------------

//function swaps two numbers
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
