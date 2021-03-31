/* 2021-03-30: SHAUN08 ->

Problem: Write a program to swap nodes in a Linked List without swapping data
Note: Swapping of data not allowed, only change pointers for the swap

Example 1:
Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8, X = 3, Y = 5
Output: 1 -> 2 -> 5 -> 4 -> 3 -> 6 -> 7 -> 8

Example 2:
Input:  1 -> 2 -> 5 -> 4 -> 3 -> 6 -> 7 -> 8, X = 1, Y = 2
Output:  2 -> 1 -> 5 -> 4 -> 3 -> 6 -> 7 -> 8

Example 3:
Input:  2 -> 1 -> 5 -> 4 -> 3 -> 6 -> 7 -> 8, X = 7, Y = 8
Output:  2 -> 1 -> 5 -> 4 -> 3 -> 6 -> 8 -> 7

Example 3:
Input: 2 -> 1 -> 5 -> 4 -> 3 -> 6 -> 8 -> 7, X = 4, Y = 2
Output:  4 -> 1 -> 5 -> 2 -> 3 -> 6 -> 8 -> 7
*/

#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

void insertAtHead(Node** head, int data)
{
    Node* new_node = new Node(data);
    new_node->next = *head;
    *head = new_node;
}

void deleteList(Node** head)
{
    Node* temp = nullptr;
    Node* curr = *head;

    while(curr)
    {
        temp = curr;
        curr = curr->next;
        delete temp;
    }

    *head = nullptr;
}

void printList(Node** head)
{
    Node* temp = *head;

    cout << "List: ";
    while(temp)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl << endl;
}

void swapNodes(int x , int y, Node** head)
{
    if(*head == nullptr)
    {
        cout << "ERROR: Empty List passed" << endl << endl;
        return;
    }

    if(x == y)
    {
        cout << "ERROR: Both data values passed are same = " << x << ", no swaps done" << endl << endl;
        return;
    }

    bool x_found = false, y_found = false;
    Node *x_p = *head, *y_p = *head, *temp = *head;
    Node *x_prev_p = nullptr, *y_prev_p = nullptr;

    // Search for nodes with x and y value
    // NOTE: This will just look for the first instance of the node with these data values
    while(temp && (!x_found || !y_found))
    {
        if(!x_found && temp->data == x)
            x_found = true;
        
        if(!y_found && temp->data == y)
            y_found = true;
        
        if(!x_found)
        {
            x_prev_p = temp;
            x_p = temp->next;
        }

        if(!y_found)
        {
            y_prev_p = temp;
            y_p = temp->next;
        }

        temp = temp->next;
    }

    // Either one or both of nodes not found
    if(!x_found || !y_found)
    {
        if(!x_found && !y_found)
            cout << "ERROR: Both data nodes " << x << " and " << y << " not found" << endl << endl;
        else if(!x_found)
            cout << "ERROR: First data node " << x << " not found" << endl << endl;
        else // !y_found
            cout << "ERROR: Second data node " << y << " not found" << endl << endl;

        return;
    }

    // Swap the two nodes found while taking care of head, if it needs swapping
    if(x_prev_p)
        x_prev_p->next = y_p;
    else
        *head = y_p;
    
    if(y_prev_p)
        y_prev_p->next = x_p;
    else
        *head = x_p;
    
    temp = x_p->next;
    x_p->next = y_p->next;
    y_p->next = temp;
}

int main()
{
    Node* head = nullptr;
    insertAtHead(&head, 8);
    insertAtHead(&head, 7);
    insertAtHead(&head, 6);
    insertAtHead(&head, 5);
    insertAtHead(&head, 4);
    insertAtHead(&head, 3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);
    cout << "Original ";
    printList(&head);

    // Swap nodes that are internal to the list
    swapNodes(3, 5, &head);
    cout << "Swapped 3 and 5" << endl;
    cout << "New ";
    printList(&head);

    // Swap nodes where first node is a head node
    swapNodes(1, 2, &head);
    cout << "Swapped 1 and 2" << endl;
    cout << "New ";
    printList(&head);

    // Swap nodes that are adjacent
    swapNodes(7, 8, &head);
    cout << "Swapped 7 and 8" << endl;
    cout << "New ";
    printList(&head);

    // Swap nodes where second node is a head node
    swapNodes(4, 2, &head);
    cout << "Swapped 4 and 2" << endl;
    cout << "New ";
    printList(&head);

    swapNodes(7, 7, &head); // Both nodes have same value
    swapNodes(17, 8, &head); // First node not in list
    swapNodes(6, 10, &head); // Second node not in list
    swapNodes(66, 0, &head); // Both nodes not in list

    deleteList(&head);
    swapNodes(7, 7, &head); // Empty list passed

    return 0;
}