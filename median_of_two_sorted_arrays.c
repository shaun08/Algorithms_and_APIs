/*
2021-04-09: SHAUN08 ->
Problem: Write a program to return the median value of two sorted arrays
NOTE- Array sizes range from 0 to 1000
*/

#include <stdio.h>

#define SIZE 6

void printArray(double arr[], int size)
{
    int i = 0;
    
    printf("Array:");
    while(i<size)
    {
        printf(" %3.2lf", arr[i]);
        i++;
    }
    printf("\n");
}

double getMedianOfSortedArray(double arr[], int size)
{
    int mid = size / 2;
    
    return (size % 2) ? (double)arr[mid] : ( (double)(arr[mid-1] + arr[mid]) / 2.0 );
}

double medianOfTwoSortedArrays(double arr1[], int size1, double arr2[], int size2)
{
    double result = 0.0;

    if((size1 == 0) && (size2 == 0))
        printf("ERROR: Both arrays are empty, returning 0.0\n");
    else if(size2 == 0)
        result =  getMedianOfSortedArray(arr1, size1);
    else if(size1 == 0)
        result = getMedianOfSortedArray(arr2, size2);
    else
    {
        int idx1 = 0, idx2 = 0, count = 0;
        double mid1 = 0.0, mid2 = 0.0;
        int total_size = size1 + size2;
        int arrays_mid = total_size/2;

        for(count=0; count <= arrays_mid; count++)
        {
            mid1 = mid2;

            if( (idx1 < size1) && (idx2 < size2) )
            {
                if(arr1[idx1] < arr2[idx2])
                    mid2 = arr1[idx1++];
                else
                    mid2 = arr2[idx2++];
            }
            else if(idx1 < size1)
                mid2 = arr1[idx1++];
            else
                mid2 = arr2[idx2++];
        }

        result = (total_size % 2) ? (double)mid2 : ( (double)(mid1 + mid2) / 2.0 );
    }

    return result;
}


int main()
{
    double arr[SIZE] = {1.0, 4.0, 7.0, 10.0, 13.0, 16.0};
    double arr2[SIZE] = {2.0, 5.0, 8.0, 11.0, 14.0, 17.0};
    double arr3[SIZE-1] = {3.0, 6.0, 9.0, 12.0, 15.0};
    
    printf("\nFirst ");
    printArray(arr, SIZE);
    printf("Second ");
    printArray(arr2, SIZE);
    printf("Third ");
    printArray(arr3, SIZE-1);

    // Test even and odd sized arrays
    printf("\nMedian of first and second array: %3.2lf\n\n", medianOfTwoSortedArrays(arr, SIZE, arr2, SIZE));
    printf("Median of first and third array:  %3.2lf\n\n", medianOfTwoSortedArrays(arr, SIZE, arr3, SIZE-1));
    printf("Median of second and third array: %3.2lf\n\n", medianOfTwoSortedArrays(arr2, SIZE, arr3, SIZE-1));

    // Test arrays with 0 elements
    printf("Median of empty and third array: %3.2lf\n\n", medianOfTwoSortedArrays(arr2, 0, arr3, SIZE-1));
    printf("Median of second and empty array: %3.2lf\n\n", medianOfTwoSortedArrays(arr2, SIZE, arr3, 0));
    printf("Median of both empty array: %3.2lf\n\n", medianOfTwoSortedArrays(arr2, 0, arr3, 0));
    
    return 0;
}