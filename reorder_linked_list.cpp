/* 2021-04-07: SHAUN08 ->

Problem: Write a program to reorder a given Linked List like in the examples below.
NOTE - This should be done using O(1) space and in O(n) time

Example 1-
List: 1->2->3->4->5->6
New List: 1->6->2->5->3->4

Example 2-
List: 1->2->3->4->5->6->7
New List: 1->7->2->6->3->5->4
*/

#include <iostream>
using namespace std;

struct node
{
    int data;
    node* next;

    node(int data) : data(data), next(nullptr) {}
};

node* insertAtHead(node* head, int new_data)
{
    node* new_node = new node(new_data);
    new_node->next = head;
    return new_node;
}

void printList(node* head)
{
    cout << "List: ";
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

node* reverseListIterative(node* head)
{
    node* prev = nullptr;
    node* next = nullptr;
    node* curr = head;

    while(curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

node* reorderList(node* head)
{
    if(!head)
    {
        cout << "ERROR: Empty list passed" << endl;
        return head;
    }

    if(!head->next)
    {
        cout << "WARNING: List has only one element, no reordering done" << endl;
        return head;
    }

    if(!head->next->next)
    {
        cout << "WARNING: List has only two elements, no reordering done" << endl;
        return head;
    }

    // Get the middle node of the list
    node *slow = head, *fast = head;

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Break the list into two seperate lists with head1 and head2 as heads of the two lists respectively
    node* head1 = head;
    node* head2 = slow->next;
    slow->next = NULL;

    // Reverse the second list
    head2 = reverseListIterative(head2);
    
    // Create dummy node as head
    head = new node(0);
    node* temp = head;
    
    // Merge the two lists by linking it to dummy node to complete reordering
    while(head1 || head2)
    {
        if(head1)
        {
            temp->next = head1;
            head1 = head1->next;
            temp = temp->next;
        }

        if(head2)
        {
            temp->next = head2;
            head2 = head2->next;
            temp = temp->next;
        }
    }

    // Get the actual head to be returned and delete dummy head
    temp = head;
    head = head->next;
    delete temp;

    return head;
}

int main()
{
    // Test list with even number of nodes
    node* head = nullptr;
    head = insertAtHead(head, 6);
    head = insertAtHead(head, 5);
    head = insertAtHead(head, 4);
    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);
    cout << endl << "First ";
    printList(head);
    cout << "--> Reordering list above" << endl;
    head = reorderList(head);
    printList(head);
    
    // Test list with odd number of nodes
    node* head2 = nullptr;
    head2 = insertAtHead(head2, 5);
    head2 = insertAtHead(head2, 4);
    head2 = insertAtHead(head2, 3);
    head2 = insertAtHead(head2, 2);
    head2 = insertAtHead(head2, 1);
    cout << endl << "Second ";
    printList(head2);
    cout << "--> Reordering list above" << endl;
    head2 = reorderList(head2);
    printList(head2);

    // Test empty list
    node* head3 = nullptr;
    cout << endl << "Third ";
    printList(head3);
    cout << "--> Reordering list above" << endl;
    head3 = reorderList(head3);

    // Test list with one element
    node* head4 = nullptr;
    head4 = insertAtHead(head4, 1);
    cout << endl << "Fourth ";
    printList(head4);
    cout << "--> Reordering list above" << endl;
    head4 = reorderList(head4);
    printList(head4);

    // Test list with two elements
    node* head5 = nullptr;
    head5 = insertAtHead(head5, 2);
    head5 = insertAtHead(head5, 1);
    cout << endl << "Fifth ";
    printList(head5);
    cout << "--> Reordering list above" << endl;
    head5 = reorderList(head5);
    printList(head5);

    cout << endl;
    return 0;
}