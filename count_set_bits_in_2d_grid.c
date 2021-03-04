/*
2021-03-04: SHAUN08 --> Count the number of set bits between 2 points in a 2-D grid with following conditions
                        1- include the boundaries of the 2 points
                        2- points passed are valid grid points
                        3- second point is always bigger or on same boundary as the first (to the right and below from the first point)
                        4- the grid can have only 1s or 0s
                        5- the grid can have mxn elements where 0<m,n<=10000

Example Grid:
  j-------
i 1 0 0 0 
| 1 1 0 0 
| 1 1 1 0 
| 1 1 1 1 
| 1 1 1 1 

--> points are dentoed as {i,j} where 0<=i<5, 0<=j<4
--> number of ones between {0,0} and {3,3}: 10
--> number of ones between {0,1} and {4,2}: 7
--> number of ones between {2,1} and {3,2}: 4
--> number of ones between {0,2} and {1,3}: 0
--> number of ones between {2,1} and {2,3}: 2
--> number of ones between {2,2} and {4,2}: 3

HINT: Map count grid for the grid above as follows:
   j---------
i  1 1 1 1 
|  2 3 3 3 
|  3 5 6 6 
|  4 7 9 10 
|  5 9 12 14
*/

#include <stdio.h>

#define R 5
#define C 4

void printGrid(int grid[][C], int rows, int columns)
{
    int i=0, j=0;

    printf("Grid:\n");

    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void initGrid(int grid[][C], int rows, int columns)
{
    int i=0, j=0;

    for(i=0; i<R; i++)
    {
        for(j=0; j<C;j++)
        {
            if(j<=i)
                grid[i][j] = 1;
        }
    }
}

void initCountGrid(int grid[][C], int count_grid[][C], int rows, int columns)
{
    int i=0, j=0, count=0;

    // count set values in 1st row
    for(i=0; i<rows; i++)
    {
        count_grid[i][j] = grid[i][j] + count;
        count = count_grid[i][j];
    }

    // count set values in 1st column
    i=0;
    count = count_grid[0][0];
    for(j=1; j<columns; j++)
    {
        count_grid[i][j] = grid[i][j] + count;
        count = count_grid[i][j];
    }

    // cout set values for rest of the grid
    for(i=1; i<rows; i++)
    {
        for(j=1; j<columns; j++)
        {
            count_grid[i][j] = grid[i][j] + count_grid[i-1][j] + count_grid[i][j-1] - count_grid[i-1][j-1];
        }
    }
}

int getOnes(int x1, int y1, int x2, int y2, int count_grid[][C])
{
    int ret_val = 0;

    // First point is {0,0}
    if(x1 == 0 && y1 == 0)
        ret_val = count_grid[x2][y2];

    // First point is on left or top boundary
    else if(x1 == 0 || y1 == 0)
    {
        if(x1 == 0)
            ret_val = count_grid[x2][y2] - count_grid[x2][y1-1];

        if(y1 == 0)
            ret_val = count_grid[x2][y2] - count_grid[x1-1][y2];
    }

    // Points are not on grid boundary
    else if(x1>0 && y1>0 && x2>0 && y2>0)
        ret_val = count_grid[x2][y2] - count_grid[x2][y1-1] - count_grid[x1-1][y2] + count_grid[x1-1][y1-1];
    
    // Do nothing as we do not expect to hit this cases
    else
        ;

    return ret_val;
}

int main()
{
    int grid[R][C] = {0};
    int count_grid[R][C] = {0};

    initGrid(grid, R, C);
    printGrid(grid, R, C);

    initCountGrid(grid, count_grid, R, C);
    printf("Count ");
    printGrid(count_grid, R, C);

    int ones = getOnes(0,0,3,3,count_grid);
    printf("Ones found between {0,0} and {3,3}: %d\n", ones);

    ones = getOnes(0,1,4,2,count_grid);
    printf("Ones found between {0,1} and {4,2}: %d\n", ones);

    ones = getOnes(2,1,3,2,count_grid);
    printf("Ones found between {2,1} and {3,2}: %d\n", ones);

    ones = getOnes(0,2,1,3,count_grid);
    printf("Ones found between {0,2} and {1,3}: %d\n", ones);

    ones = getOnes(2,1,2,3,count_grid);
    printf("Ones found between {2,1} and {2,3}: %d\n", ones);

    ones = getOnes(2,2,4,2,count_grid);
    printf("Ones found between {2,2} and {4,2}: %d\n", ones);

    return 0;
}