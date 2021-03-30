/* 2021-03-30: SHAUN08 ->

Problem: Write a program to clone a linked list with next and random pointer in O(1) extra space
Note: the random pointer is guaranteed to be one of the nodes in the list or NULL

Example:
Original List
1 - 2 - 3 - 4 - 5 - NULL
|   |   |   |   |
5   2  NULL 1   1

New List
1' - 2' - 3' - 4' - 5' - NULL
|    |    |    |    |
5'   2'  NULL  1'   1'
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node_tag
{
    int data;
    struct Node_tag* next;
    struct Node_tag* random;
} Node;

void insertAtTail(Node** head, int data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->random = NULL;

    Node* temp = *head;

    if(temp == NULL)
        *head = new_node;
    else
    {
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = new_node;
    }
}

void printList(Node** head)
{
    Node* temp = *head;
    
    printf("List: \n");
    
    while(temp)
    {
        printf("Data: %d, Random data: ", temp->data);
        
        if(temp->random)
            printf("%d\n", temp->random->data);
        else
            printf("NULL\n");
        
        temp = temp->next;
    }
    
    printf("End of list\n\n");
}

Node* cloneList(Node** head)
{
    if(*head == NULL)
        return NULL;
    
    Node *clone_head = NULL, *temp = *head, *temp_clone = NULL, *new_node = NULL;
    
    // Add elements of new list in the current list
    while(temp)
    {
        new_node = (Node*)malloc(sizeof(Node));
        new_node->data = temp->data;
        new_node->next = temp->next;
        new_node->random = NULL;
        temp->next = new_node;
        temp = temp->next->next;
    }

    printf("Intermediate ");
    printList(head);

    // Build the random pointers using original lists linking
    temp = *head;
    temp_clone = temp->next;

    while(temp)
    {
        if(temp->random)
            temp_clone->random = temp->random->next;
        
        temp = temp->next->next;

        if(temp)
            temp_clone = temp_clone->next->next;
    }

    // Split the two lists and return new list
    temp = *head;
    clone_head = temp->next;
    temp_clone = temp->next;

    while(temp && temp_clone)
    {
        temp->next = temp_clone->next;

        if(temp_clone->next)
            temp_clone->next = temp_clone->next->next;
        
        temp = temp->next;
        temp_clone = temp_clone->next;
    }

    return clone_head;
}

void freeList(Node** head)
{
    Node* temp = NULL;
    Node* curr = *head;

    while(curr)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    *head = NULL;
}

int main()
{
    Node* head = NULL;
    insertAtTail(&head, 1);
    insertAtTail(&head, 2);
    insertAtTail(&head, 3);
    insertAtTail(&head, 4);
    insertAtTail(&head, 5);
    
    // Set up the random pointers in this list (refer example at top)
    head->random = head->next->next->next->next;
    head->next->random = head->next;
    head->next->next->next->random = head;
    head->next->next->next->next->random = head;

    printf("Original ");
    printList(&head);
    
    // Create a clone of the linked list in O(1) space complexity
    Node* clone_head = cloneList(&head);
    printf("Original ");
    printList(&head);
    printf("Clone ");
    printList(&clone_head);

    // Free the 2 lists
    freeList(&head);
    freeList(&clone_head);

    // Create a clone of an empty linked list
    clone_head = cloneList(&head);
    printf("Original ");
    printList(&head);
    printf("Clone ");
    printList(&clone_head);
    
    return 0;
}