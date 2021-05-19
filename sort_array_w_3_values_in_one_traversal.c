/* 2021-05-19: SHAUN08 ->

Problem:  Sort an array containing only 2s, 5s and 10s in a single pass/traversal (Dutch National Flag algorithm)
Example: arr = [2, 2, 2, 5, 2, 5, 10, 2, 10] -> [2, 2, 2, 2, 2, 5, 5, 10, 10]

Hint: Use 3 pointers - low, mid, high
[2, 2, 2, 2, 5, 5, 5... 10, 10, 10 , 10]
 low        mid                     high   
*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arr_size 9
#define val1 2
#define val2 5
#define val3 10

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

void swap(int* a, int* b)
{
    if(a != b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

// Approach 1 - lots of logic
bool sortArray(int *arr, int size)
{
    if(!arr)
        return false;
    
    if(!size)
        return false;
    
    int low = 0, high = size-1, mid = -1;
    
    while((low < high) && (mid <= high))
    {
        if(arr[low] == val1)
            low++;
        else if(mid == -1)
            mid = low;
        
        while( (high >=0) && (arr[high] == val3) )
            high--;
        
        if((mid != -1) && (mid <= high))
        {
            if( (arr[mid] == val1) && (low < mid) )
            {
                swap(&arr[low], &arr[mid]);
                low++;
            }
            
            if( arr[mid] == val3 )
            {
                swap(&arr[high], &arr[mid]);
                high--;
                
                if(arr[mid] == val1)
                {
                    swap(&arr[low], &arr[mid]);
                    low++;
                }
            }
            
            mid++;
        }
    }

    return true;
}

// Approach 2 - cleaner code
bool sortArray2(int arr[], int size)
{
    if(size <= 1)
        return false;
    
    int low = 0, mid = 0, high = size-1;

    while(mid <= high)
    {
        if(arr[mid] == val1)
        {
            swap(&arr[low++], &arr[mid++]);
        }
        else if(arr[mid] == val3)
        {
            swap(&arr[high--], &arr[mid]);
        }
        else
            mid++;
    }

    return true;
}

int main()
{
    int arr[arr_size] = {2, 2, 2, 5, 2, 5, 10, 2, 10};
    printf("First ");
    printArray(arr, arr_size);

    //bool status1 = sortArray(arr, arr_size);
    bool status1 = sortArray2(arr, arr_size);
    printf("Sorted ");
    printArray(arr, arr_size);

    int arr2[arr_size-4] = {10, 2, 5, 10, 10};
    printf("\nSecond ");
    printArray(arr2, arr_size-4);

    //bool status2 = sortArray(arr2, arr_size-4);
    bool status2 = sortArray2(arr2, arr_size-4);
    printf("Sorted ");
    printArray(arr2, arr_size-4);

    int arr3[3] = {10, 10, 5};
    printf("\nThird ");
    printArray(arr3, 3);

    //bool status3 = sortArray(arr3, 3);
    bool status3 = sortArray2(arr3, 3);
    printf("Sorted ");
    printArray(arr3, 3);

    int arr4[arr_size-4] = {2, 2, 2, 2, 2};
    printf("\nFourth ");
    printArray(arr4, arr_size-4);

    //bool status4 = sortArray(arr4, arr_size-4);
    bool status4 = sortArray2(arr4, arr_size-4);
    printf("Sorted ");
    printArray(arr4, arr_size-4);

    int arr5[arr_size-4] = {5, 5, 5, 5, 5};
    printf("\nFifth ");
    printArray(arr5, arr_size-4);

    //bool status5 = sortArray(arr5, arr_size-4);
    bool status5 = sortArray2(arr5, arr_size-4);
    printf("Sorted ");
    printArray(arr5, arr_size-4);

    return 0;
}