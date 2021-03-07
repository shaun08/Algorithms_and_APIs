// 2021-03-07: SHAUN08 --> Circular queue library in C

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 5

static int front = -1;
static int back = -1;
static int* queue_ptr = NULL;
static int queue_size = 0;

void initQueue(int nr_of_elements);
void deleteQueue();
void enqueue(int value);
int dequeue();
bool isEmpty();
bool isFull();
void printQueue();

void initQueue(int nr_of_elements)
{
    if(queue_ptr != NULL)
    {
        printf("ERROR: Queue already initialized!\n");
        return;
    }

    queue_ptr = (int*)malloc(sizeof(int)*nr_of_elements);
    if(queue_ptr == NULL)
    {
        printf("ERROR: Malloc failed while creating queue of %d elements\n",nr_of_elements);
        return;
    }

    front = -1;
    back = -1;
    queue_size = nr_of_elements;
    printf("Created a queue of %d elements\n",nr_of_elements);
}

void deleteQueue()
{
    if(queue_ptr != NULL)
    {
        front = -1;
        back = -1;
        queue_size = 0;

        free(queue_ptr);
        queue_ptr = NULL;
    }

    printf("Queue deleted\n");
}

bool isFull()
{
    if(queue_ptr == NULL)
    {
        printf("ERROR: Queue not initialized!\n");
        return false;
    }

    if( ((back+1)%queue_size) == front)
        return true;
    return false;
}

bool isEmpty()
{
    if(queue_ptr == NULL)
    {
        printf("ERROR: Queue not initialized!\n");
        return false;
    }

    if( (front == back) && (back == -1) )
        return true;
    return false;
}

void printQueue()
{
    if(queue_ptr == NULL)
    {
        printf("ERROR: Queue not initialized!\n");
        return;
    }

    printf("Queue: ");
    
    if(isEmpty())
    {
        printf("Empty\n");
        return;
    }

    int temp = front;
    if(temp != back)
    {
        while(temp != back)
        {
            printf("%d ",queue_ptr[temp]);
            temp = (temp+1)%queue_size;
        }
    }
    printf("%d\n", queue_ptr[temp]);
}

void enqueue(int val)
{
    if(queue_ptr == NULL)
    {
        printf("ERROR: Queue not initialized!\n");
        return;
    }

    if(isFull())
    {
        printf("ERROR: Queue full, enqueuing %d failed!\n",val);
        return;
    }

    if(isEmpty())
        front = (front+1)%queue_size;

    back = (back+1)%queue_size;
    queue_ptr[back] = val;
    printf("Enqueued %d at index %d\n",val,back);
}

int dequeue()
{
    if(queue_ptr == NULL)
    {
        printf("ERROR: Queue not initialized!\n");
        return INT_MIN;
    }

    if(isEmpty())
    {
        printf("ERROR: Queue is empty, dequeue failed!\n");
        return INT_MIN;
    }

    int ret_val = queue_ptr[front];
    printf("Dequeued element %d from index %d\n",ret_val,front);

    if(front == back)
    {
        front = -1;
        back = -1;
    }
    else
        front = (front+1)%queue_size;
    
    return ret_val;
}

int main()
{
    // Error Cases before queue init
    printf("IsEmpty(): %d\n",isEmpty());
    printf("IsFull(): %d\n",isFull());
    enqueue(-5);
    dequeue();
    initQueue(QUEUE_SIZE);
    printf("\n");
    
    // Printing queue
    initQueue(QUEUE_SIZE);
    printQueue();
    printf("IsEmpty(): %d\n",isEmpty());
    printf("IsFull(): %d\n\n",isFull());

    // Test1 with enquque(s)
    enqueue(2);
    enqueue(4);
    enqueue(6);
    enqueue(8);
    printf("IsEmpty(): %d\n",isEmpty());
    enqueue(10);
    enqueue(12);
    printf("IsFull(): %d\n",isFull());
    printQueue();
    printf("\n");

    // Test2 with dequeue(s)
    dequeue();
    dequeue();
    printQueue();
    printf("\n");

    // Test3 with more enqueue(s)
    enqueue(-1);
    printf("IsFull(): %d\n",isFull());
    enqueue(-3);
    printf("IsFull(): %d\n",isFull());
    printQueue();
    printf("\n");

    // Test4 with both enqueue(s)/dequeue(s)
    enqueue(-5);
    dequeue();
    dequeue();
    enqueue(-7);
    enqueue(-9);
    printQueue();
    printf("IsFull(): %d\n\n",isFull());

    // Test5 dequeue(s) error case
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    printf("IsEmpty(): %d\n",isEmpty());
    printQueue();
    deleteQueue();
    deleteQueue();

    return 0;
}
