/* Calculate the number of rotations when given a rotated array
 * Rotated arrays are sorted arrays that have been rotated to the right
 *
 * Testing to see various algorithms and how they perform
 * Inspired by CS50's How to Prepare for Tech Interviews: 
 * https://youtu.be/ii9NLvcAfpE
 * 
 * Brenda Anderson 26 Sep 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

// For the function pointer
typedef int(*rotation_fn) (int, int*);

// Prototypes
double calculate(const struct rusage *b, const struct rusage *a);
double test_algorithm(rotation_fn fn, int size, int *nums);
void build_rotated_array(int size, int *nums, int rotates);
int num_rotations_loop(int len, int *nums);
int num_rotations_min(int len, int *nums);
int num_rotations_log(int len, int *nums);
void print_arr(int len, int *nums);

// Running Variables
#define SIZE 200
#define STEPS 20
#define REPEATS 1000000


int main(void)
{
    int nums[SIZE];
    printf("Rots\tLog\tMin\tLoop\n");
    for (int j = 0; j < SIZE; j += SIZE / STEPS)
    {
        build_rotated_array(SIZE, nums, j);
        printf("%i\t", j);
        printf("%.2lf\t", test_algorithm(num_rotations_log, SIZE, nums));
        printf("%.2lf\t", test_algorithm(num_rotations_min, SIZE, nums));
        printf("%.2lf\t", test_algorithm(num_rotations_loop, SIZE, nums));
        printf("\n");
    }
}

// calls the function
double test_algorithm(rotation_fn fn, int size, int *nums)
{
    struct rusage before, after;  
    getrusage(RUSAGE_SELF, &before);
    for (int i = 0; i < REPEATS; i++)
        fn(size, nums);
    getrusage(RUSAGE_SELF, &after);
    // Calculate time 
    return calculate(&before, &after);
}

// fills the array with rotated numbers
void build_rotated_array(int size, int *nums, int rotates)
{
    for (int i = 0; i < rotates; i++)
        nums[i] = i + size - rotates;
    for (int i = rotates; i < size; i++)
        nums[i] = i - rotates;
}

// uses a linear search to find the rotation
int num_rotations_loop(int len, int *nums)
{
    if (nums[0] < nums[len-1]) 
        return 0;
    for (int i = 1; i < len; i++)
        if (nums[i] < nums[i - 1])
            return i;
    return 0;
}

// finds the minimum by iterating over every element
int num_rotations_min(int len, int *nums)
{
    int min = nums[0], index = 0;
    for (int i = 1; i < len; i++)
        if (nums[i] < min)
        {
             min = nums[i];
             index = i;
        }
    return index;
}

// finds the minimum by binary search
int num_rotations_log(int len, int *nums)
{
    int start = 0;
    int end = len - 1;
    while (end > start)
    {
        int mid = (end + start) / 2;
        if (nums[end] < nums[mid])
            start = mid + 1;
        else
            end = mid;
    }
    return start;
}


// Thanks CS50 Speller
// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
        return 0.0;
    else
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
}

// prints an array 
void print_arr(int len, int *nums)
{
    for (int i = 0; i < len; i++)
        printf("%i ", nums[i]);
    printf("\n");
}
