/* 2021-06-04: SHAUN08 ->

Problem: Find an element in an sorted and rotated array
Note: The array passed is always valid with no duplicates

Example1: Find 5, 2, 3, 4, 8 in array {4, 5, 6, 7, 1, 2, 3}
Solution: 5->true, 2->true, 3->true, 4->true, 8->false

Example2: Find 6, 9, 4, 7, 18 in array {7, 8, 9, 1, 2, 3, 4, 5, 6}
Solution: 6->true, 9->true, 4->true, 7->true, 18->false

*/

#include <stdbool.h>
#include <stdio.h>

#define BOOL_TO_STR(x) ( (x) ? "true" : "false" )

#define ARR1_SIZE 7
#define ARR2_SIZE 9

void printArray(int *arr, int size)
{
    int i = 0;
    
    printf("Array:");

    while(i<size)
    {
        printf(" %d", arr[i]);
        i++;
    }

    printf("\n");
}

bool findElemInSortedRotatedArr(int *arr, int arr_size, int element)
{
    int low = 0;
    int high = arr_size-1;
    int mid = 0;

    while(low <= high)
    {
        mid = low + (high-low)/2;

        if( (arr[mid] == element) || (arr[low] == element) || (arr[high] == element) )
            return true;
        
        else if(arr[low] > arr[mid]) // Left of mid is sorted and rotated array
        {
            if( (arr[mid] < element) && (arr[high] > element) ) // Search right of mid
                low = mid+1;
            else // Search left of mid
                high = mid-1;
        }
        
        else // Left of mid is sorted array
        {
            if( (arr[mid] > element) && (arr[low] < element) ) // Search left of mid
                high = mid-1;
            else // Search right of mid
                low = mid+1;
        }
    }

    return false;
}

int main()
{
    // Array 1
    int arr1[ARR1_SIZE] = {4, 5, 6, 7, 1, 2, 3};
    printf( "\nFirst " );
    printArray(arr1, ARR1_SIZE);
    printf( "Find 5 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr1, ARR1_SIZE, 5) ) );
    printf( "Find 2 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr1, ARR1_SIZE, 2) ) );
    printf( "Find 3 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr1, ARR1_SIZE, 2) ) );
    printf( "Find 4 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr1, ARR1_SIZE, 2) ) );
    printf( "Find 8 in array - %s\n\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr1, ARR1_SIZE, 8) ) );

    // Array 2
    int arr2[ARR2_SIZE] = {7, 8, 9, 1, 2, 3, 4, 5, 6};
    printf("\nSecond ");
    printArray(arr2, ARR2_SIZE);
    printf( "Find 6 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr2, ARR2_SIZE, 6) ) );
    printf( "Find 9 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr2, ARR2_SIZE, 9) ) );
    printf( "Find 4 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr2, ARR2_SIZE, 4) ) );
    printf( "Find 7 in array - %s\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr2, ARR2_SIZE, 7) ) );
    printf( "Find 18 in array - %s\n\n", BOOL_TO_STR( findElemInSortedRotatedArr(arr2, ARR2_SIZE, 18) ) );

    return 0;
}