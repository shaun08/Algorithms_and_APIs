/* 2021-04-03: SHAUN08 ->

Problem: Write a program to find the maximum sum of subarrays within an array and also print the subarray
Note:
1 - The subarrays should be contiguous
2 - Subarray can also be the actual array itself
3 - Values in the array can range from INT_MIN to INT_MAX
*/

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define ARR_SIZE 16

void printArray(int* arr, int size)
{
    if(arr == NULL)
        printf("ERROR: ARRAY passed is NULL\n\n");

    if(size <=0)
        printf("ERROR: Invalid size (%d) passed for array\n\n", size);

    printf("Array:");
    int i=0;    
    for(i=0; i<size; i++)
        if(arr[i] == INT_MIN)
            printf(" INT_MIN");
        else if(arr[i] == INT_MAX)
            printf(" INT_MAX");
        else
            printf(" %2d", arr[i]);
    printf("\n");
}

int getSumWithIntOverflowCheck(int a, int b)
{
    int sum = a+b;

    // Positive overflow
    if((a > 0) && (b > 0) && (sum < 0))
        return INT_MAX;
    
    // Negative overflow
    if((a < 0) && (b < 0) && (sum >= 0)) // NOTE: Checking for sum>=0 here as some compilers limit sum to 0
        return INT_MIN;
    
    return sum;
}

bool maxSumSubArray(int *arr, int size, int* max_sum, int* start_idx, int* end_idx)
{
    bool max_found = false;
    
    if(arr == NULL)
    {
        printf("ERROR: ARRAY passed is NULL\n\n");
        return max_found;
    }

    if(size <= 0)
    {
        printf("ERROR: Invalid size (%d) passed for array\n\n", size);
        return max_found;
    }
    
    int start = 0, end = 0, sub_idx = 0, i=0;
    int max_so_far = INT_MIN, current_max = INT_MIN;

    for(i=0; i<size; i++)
    {
        int temp_sum = getSumWithIntOverflowCheck(current_max, arr[i]);

        if(arr[i] > temp_sum)
        {
            current_max = arr[i];
            sub_idx = i;
        }
        else
            current_max = temp_sum;

        if(current_max >= max_so_far)
        {
            max_so_far = current_max;
            start = sub_idx;
            end = i;
        }
    }

    if(max_so_far > INT_MIN)
    {
        *max_sum = max_so_far;
        *start_idx = start;
        *end_idx = end;
        max_found = true;
    }

    return max_found;
}

void runTest(int* arr, int size, int expected_sum)
{
    printArray(arr, size);

    int start_idx = -1;
    int end_idx = -1;
    int max_sum = 0;
    
    bool max_found = maxSumSubArray(arr, size, &max_sum, &start_idx, &end_idx);

    if(!max_found)
        printf("No subarray found with sum greater than INT_MIN\n\n");
    else
    {
        assert(max_sum = expected_sum);
        printf("Maximum sum of subarrays in the list above: ");
        (max_sum == INT_MAX) ? printf("INT_MAX\n") : printf("%d\n", max_sum);
        printf("Sub");
        printArray(&arr[start_idx], end_idx-start_idx+1);
        printf("\n");
    }
}

int main()
{
    // TEST 1
    int arr[ARR_SIZE] = {4, -3, -2, 2, 3, 1, -2, -3, 4, 2, -6, -3, -1, 3, 1, 2};
    int expected_sum1 = 7;
    printf("\nFirst ");
    runTest(arr, ARR_SIZE, expected_sum1);

    // TEST 2
    int arr2[ARR_SIZE/2] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int expected_sum2 = 7;
    printf("Second ");
    runTest(arr2, ARR_SIZE/2, expected_sum2);

    // TEST 3
    int arr3[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 12, 13, 14, 0};
    int expected_sum3 = 95;
    printf("Third ");
    runTest(arr3, ARR_SIZE, expected_sum3);

    // TEST 4
    int arr4[ARR_SIZE/2] = {0, -1, -2, 3, INT_MAX, 5, INT_MAX, -7};
    int expected_sum4 = INT_MAX;
    printf("Fourth ");
    runTest(arr4, ARR_SIZE/2, expected_sum4);

    // TEST 5
    int arr5[ARR_SIZE/4] = {INT_MIN, INT_MIN, INT_MIN, INT_MIN};
    printf("Fifth ");
    runTest(arr5, ARR_SIZE/4, expected_sum4);
    
    // TEST 6
    printf("Null Array passed\n");
    int max_sum=0, start_idx=-1, end_idx=-1;
    bool max_found6 = maxSumSubArray(NULL, ARR_SIZE, &max_sum, &start_idx, &end_idx);
    assert(max_found6 == false);

    // TEST 7
    printf("Passing array size less than 1\n");
    bool max_found7 = maxSumSubArray(arr3, -2, &max_sum, &start_idx, &end_idx);
    assert(max_found7 == false);

    return 0;
}