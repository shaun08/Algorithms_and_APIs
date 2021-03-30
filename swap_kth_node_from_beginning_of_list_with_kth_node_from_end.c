/* 2021-03-30: SHAUN08 ->

Problem: Write a program to swap kth node from beginning with kth node from end of a Linked List
Note: swapping of data not allowed, only change pointers for the swap

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8, K = 3
Output: 1 -> 2 -> 6 -> 4 -> 5 -> 3 -> 7 -> 8

Example 2:
Input:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8, K = 8
Output:  8 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 1
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node_tag
{
    int data;
    struct Node_tag* next;
} Node;

void insertAtHead(Node** head, int data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void deleteAtHead(Node** head)
{
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteList(Node** head)
{
    Node* temp = NULL;
    Node* curr = *head;

    while(curr)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    *head= NULL;
}

void printList(Node* head)
{
    Node* temp = head;

    printf("List: ");
    
    while(temp)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n\n");
}

int countNodesInList(Node** head)
{
    int count = 0;
    Node* temp = *head;

    while(temp)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void swapKthNodes(Node** head, int k)
{
    if(*head == NULL)
    {
        printf("ERROR: Empty list passed\n\n");
        return;
    }

    if(k < 1)
    {
        printf("ERROR: Invalid K value passed: %d\n\n",k);
        return;
    }

    int count = countNodesInList(head);
    
    if(count < k)
    {
        printf("ERROR: K value '%d' greater than number of elements in list '%d'\n\n", k, count);
        return;
    }

    if(2*k-1 == count)
    {
        printf("K value '%d' evaluates to middle element in list, no swap needed\n\n", k);
        return;
    }

    Node* k_beg = *head, *k_end = *head; // Kth nodes from beginning and end of list
    Node* k_beg_prev = NULL, *k_end_prev = NULL; // Previous nodes of the Kth nodes in line above
    Node* temp = NULL;
    int temp_count = 1;

    // Get the Kth node from beginning
    while(temp_count != k)
    {
        k_beg_prev = k_beg;
        k_beg = k_beg->next;
        temp_count++;
    }

    // Get the Kth node from end
    temp_count = 1;
    while(temp_count != (count - k + 1))
    {
        k_end_prev = k_end;
        k_end = k_end->next;
        temp_count++;
    }

    // Swap the Kth node from beginning with Kth node from end
    if(k_beg_prev)
        k_beg_prev->next = k_end;
    
    if(k_end_prev)
        k_end_prev->next = k_beg;
    
    temp = k_end->next;
    k_end->next = k_beg->next;
    k_beg->next = temp;

    // Set the head node if it was swapped
    if(k==1)
        *head = k_end;
        
    if(k == count)
        *head = k_beg;
}

int main()
{
    Node* head = NULL;
    insertAtHead(&head, 8);
    insertAtHead(&head, 7);
    insertAtHead(&head, 6);
    insertAtHead(&head, 5);
    insertAtHead(&head, 4);
    insertAtHead(&head, 3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);
    printf("Original ");
    printList(head);

    int k = 0;
    for(k=1; k<=8; k++)
    {
        swapKthNodes(&head, k);
        printf("Swapped Node %d from beginning and end of list\n", k);
        printList(head);
    }

    // Verify when K is middle elemnt from both ends of list
    deleteAtHead(&head);
    swapKthNodes(&head, 4);

    // Verify when K is less than 1
    swapKthNodes(&head, 0);

    // Verify when K is greater than count of list
    swapKthNodes(&head, 10);

    // Verify when NULL list is passed
    deleteList(&head);
    swapKthNodes(&head, 4);
    
    return 0;
}