/* 2021-04-03: SHAUN08 ->

Problem: Write a program to rotate a singly linked list clockwise or counter-clockwise by an interger value "k"
Note: k can be greater than number of elements (n) in the List, in this case we rotate list (k%n) times

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8, Clockwise = true, K = 3
Output: 6 -> 7 -> 8 -> 1 -> 2 -> 3 -> 4 -> 5

Example 2:
Input:  6 -> 7 -> 8 -> 1 -> 2 -> 3 -> 4 -> 5, Clockwise = false, K = 11
Output:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8
*/

#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

void insertAtHead(Node** head, int data)
{
    Node* new_node = new Node(data);
    new_node->next = *head;
    *head = new_node;
}

void printList(Node* head)
{
    cout << "List: ";
    
    while(head)
    {
        cout << head->data << " -> ";
        head = head->next;
    }

    cout << "NULL" << endl << endl;
}

void rotateListClockwise(Node** head, int k)
{
    Node *temp = *head, *new_tail = *head;
    int count = 0;

    while(temp->next)
    {
        if(count < k)
            count++;
        else
            new_tail = new_tail->next;
        
        temp = temp->next;
    }

    temp->next = *head;
    *head = new_tail->next;
    new_tail->next = nullptr;
}

void rotateListCounterClockwise(Node** head, int k)
{
    Node *temp = *head, *new_tail = nullptr;
    int count = 0;
    bool new_tail_found = false;

    while(temp->next)
    {
        if(count < k)
            count++;
        
        if( (count == k) && !new_tail_found )
        {
            new_tail = temp;
            new_tail_found = true;
        }

        temp = temp->next;
    }

    temp->next = *head;
    *head = new_tail->next;
    new_tail->next = nullptr;
}

void rotateList(Node** head, int k, bool clockwise)
{
    if(*head == nullptr)
    {
        cout << "ERROR: Head to list passed is NULL" << endl;
        return;
    }

    Node* temp = *head;

    if(temp->next == nullptr)
    {
        cout << "WARNING: List has only one element, no rotation needed" << endl;
        return;
    }

    int node_count = 1;
    
    // Get the number of nodes in list
    while(temp->next)
    {
        temp = temp->next;
        node_count++;
    }

    if( (k%node_count) == 0)
    {
        cout << "WARNING: Number of elements " << node_count << " in List is multiple of k " << k;
        cout << ", no rotation needed" << endl;
        return;
    }

    k = k%node_count;

    if(clockwise)
        rotateListClockwise(head, k);
    else
        rotateListCounterClockwise(head, k);
}

int main()
{
    Node* head = new Node(8);
    insertAtHead(&head, 7);
    insertAtHead(&head, 6);
    insertAtHead(&head, 5);
    insertAtHead(&head, 4);
    insertAtHead(&head, 3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);
    cout << "Original ";
    printList(head);

    cout << "Rotate List Clockwise with K=3" << endl << "New ";
    rotateList(&head, 3, true);
    printList(head);

    cout << "Rotated List Counter-clockwise with K=11" << endl;
    rotateList(&head, 11, false);
    cout <<  "New ";
    printList(head);

    return 0;
}