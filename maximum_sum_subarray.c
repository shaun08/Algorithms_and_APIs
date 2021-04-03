/* 2021-04-03: SHAUN08 ->

Problem: Write a program to find the maximum sum of subarrays within an array and also print the subarray
Note:
1 - The subarrays should be contiguous
2 - Subarray can also be the actual array itself
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

    printf("Array: ");
    int i=0;    
    for(i=0; i<size; i++)
        printf(" %2d", arr[i]);
    printf("\n");
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
        if(arr[i] > current_max + arr[i])
        {
            current_max = arr[i];
            sub_idx = i;
        }
        else
            current_max += arr[i];

        if(current_max > max_so_far)
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

int main()
{
    // TEST 1
    int arr[ARR_SIZE] = {4, -3, -2, 2, 3, 1, -2, -3, 4, 2, -6, -3, -1, 3, 1, 2};
    printf("\nFirst ");
    printArray(arr, ARR_SIZE);

    int start_idx = -1;
    int end_idx = -1;
    int max_sum = 0;
    
    bool max_found = maxSumSubArray(arr, ARR_SIZE, &max_sum, &start_idx, &end_idx);

    if(!max_found)
        printf("No subarray with sum greater than 0\n\n");
    else
    {
        printf("Maximum sum of subarrays in the list above: %d\n", max_sum);
        printf("Sub");
        printArray(&arr[start_idx], end_idx-start_idx+1);
        printf("\n");
    }

    // TEST 2
    int arr2[ARR_SIZE/2] = {-2, -3, 4, -1, -2, 1, 5, -3};
    printf("Second ");
    printArray(arr2, ARR_SIZE/2);

    int start_idx2 = -1;
    int end_idx2 = -1;
    int max_sum2 = 0;
    
    bool max_found2 = maxSumSubArray(arr2, ARR_SIZE/2, &max_sum2, &start_idx2, &end_idx2);

    if(!max_found2)
        printf("No subarray with sum greater than 0\n\n");
    else
    {
        printf("Maximum sum of subarrays in the list above: %d\n", max_sum2);
        printf("Sub");
        printArray(&arr2[start_idx2], end_idx2-start_idx2+1);
        printf("\n");
    }

    // TEST 3
    int arr3[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    printf("Third ");
    printArray(arr3, ARR_SIZE);

    int start_idx3 = -1;
    int end_idx3 = -1;
    int max_sum3 = 0;
    
    bool max_found3 = maxSumSubArray(arr3, ARR_SIZE, &max_sum3, &start_idx3, &end_idx3);

    if(!max_found3)
        printf("No subarray with sum greater than 0\n\n");
    else
    {
        printf("Maximum sum of subarrays in the list above: %d\n", max_sum3);
        printf("Sub");
        printArray(&arr3[start_idx3], end_idx3-start_idx3+1);
        printf("\n");
    }

    // TEST 4
    printf("Null Array passed\n");
    bool max_found4 = maxSumSubArray(NULL, ARR_SIZE, &max_sum3, &start_idx3, &end_idx3);
    assert(max_found4 == false);

    // TEST 5
    printf("Passing array size less than 1\n");
    bool max_found5 = maxSumSubArray(arr3, -2, &max_sum3, &start_idx3, &end_idx3);
    assert(max_found5 == false);

    return 0;
}