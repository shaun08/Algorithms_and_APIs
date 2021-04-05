/* 2021-04-04: SHAUN08 -> Problem: Write a program to merge two sorted arrays in O(1) space */

#include <iostream>

void printArray(int a[], int size)
{
    for(int i=0; i<size; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}

// Time complexity - O(m*n)
// Space complexity - O(1)
void mergeSortedArrays(int a[], int m, int b[], int n)
{
    if(m < 1 && n < 1)
        return;
    
    for(int j=n-1; j>=0; j--)
    {
        int last=a[m-1];
        int i=m-2;

        for(i=m-2; ( (i>=0) && (a[i] > b[j]) ); i--)
            a[i+1] = a[i];
        
        if( (i != m-2) || (last > b[j]) )
        {
            a[i+1] = b[j];
            b[j] = last;
        }
    }
}

// Time complexity - O( (m+n)*log(m+n) )
// Space complexity - O(1)
void mergeSortedArraysGap(int a[], int m, int b[], int n)
{
    if( m<1 && n<1 )
        return;

    int total_size = m+n, i = 0, j = 0;
    int gap = (total_size > 1) ? ( (total_size/2) + (total_size%2) ) : 0;

    while( gap > 0 )
    {
        for( i=0; i+gap < m; i++ )
        {
            if( a[i] > a[i+gap] )
                std::swap(a[i], a[i+gap]);
        }

        for( j = (gap>m) ? (gap-j) : 0; i < m && j < n; i++,j++ )
        {
            if( a[i] > b[j] )
                std::swap(a[i], b[j]);
        }

        if( j < n )
        {
            for( j=0; j+gap < n; j++ )
            {
                if( b[j] > b[j+gap] )
                    std::swap(b[j], b[j+gap]);
            }
        }

        gap = (gap > 1) ? ( (gap/2) + (gap%2)) : 0;
    }
}

void runTest()
{
    // Odd sized arrays
    int arr[4] = {2,3,5,9};
    int arr2[3] = {0,4,8};

    std::cout << "Arrays:" << std::endl;
    printArray(arr, 4);
    printArray(arr2, 3);

    mergeSortedArrays(arr, 4, arr2, 3);
    
    std::cout << "Arrays post merging:" << std::endl;
    printArray(arr, 4);
    printArray(arr2, 3);

    // Even sized arrays
    std::cout << std::endl << "New arrays" << std::endl;
    int arr3[4] = {0,2,5,9};
    int arr4[4] = {3,5,8,10};

    printArray(arr3, 4);
    printArray(arr4, 4);

    mergeSortedArrays(arr3, 4, arr4, 3);
    
    std::cout << "Arrays post merging:" << std::endl;
    printArray(arr3, 4);
    printArray(arr4, 4);
}

void runTestGap()
{
    // Odd sized arrays
    int arr[4] = {2,3,5,9};
    int arr2[3] = {0,4,8};

    std::cout << "Arrays:" << std::endl;
    printArray(arr, 4);
    printArray(arr2, 3);

    mergeSortedArraysGap(arr, 4, arr2, 3);

    std::cout << "Arrays post merging:" << std::endl;
    printArray(arr, 4);
    printArray(arr2, 3);

    // Even sized arrays
    std::cout << std::endl << "New arrays" << std::endl;
    int arr3[4] = {0,2,5,9};
    int arr4[4] = {3,5,8,10};

    printArray(arr3, 4);
    printArray(arr4, 4);

    mergeSortedArraysGap(arr3, 4, arr4, 4);

    std::cout << "Arrays post merging:" << std::endl;
    printArray(arr3, 4);
    printArray(arr4, 4);
}

int main()
{
    std::cout << "*** TEST O(m*n) technique ***" << std::endl;
    runTest();
    std::cout << std::endl;

    std::cout << "*** TEST O((m+n)*log(m+n)) technique ***" << std::endl;
    runTestGap();
    std::cout << std::endl;

    return 0;
}