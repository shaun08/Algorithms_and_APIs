/* 2021-04-07: SHAUN08 ->

Problem:
Write a program to reverse a sublist within a linked list while making use of generic reverse list technique (iterative / recursive)
The code below uses both recursive as well as iterative linked list reversal approaches to reverse sublists for practise

NOTE-
1 - The start and end points of the sublist are passed as indices m and n where (m > n) or (n > m)
2 - The first/head/root node of the list is considered to be index 0

Example 1-
List: 1->2->3->4->5->6, m = 2, n = 4
New List: 1->2->5->4->3->6

Example 2-
List: 1->2->5->4->3->6, m = 4, n = 0
New List: 3->4->5->2->1->6

Example 3-
List: 3->4->5->2->1->6, m = 3, n = 5
New List: 3->4->5->6->1->2
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

node* reverseListRecursive(node* head)
{
	if(!head)
		return nullptr;

	if(!head->next)
	{
		return head;
	}
	
	node* curr = head;
	head = reverseListRecursive(head->next);
	curr->next->next = curr;
	curr->next = nullptr;

	return head;
}

node* reverseSublistInLinkedList(node *head, int m, int n)
{
    // List passed is Empty
    if(!head)
    {
        cout << "ERROR: Empty list passed" << endl;
        return head;
    }

    // Throw an error if the indices passed are invalid or equal
    if( (m == n) || (m < 0) || (n < 0) )
    {
        if( (m < 0) && (n < 0) )
        {
            cout << "ERROR: Invalid indices passed for sublist, start = (" << m;
            cout << "), end = (" << n << ")" << endl;
        }
        else if(m < 0)
            cout << "ERROR: Invalid start index passed for sublist, (" << m << ")" << endl;
        else if(n < 0)
            cout << "ERROR: Invalid end index passed for sublist, (" << n << ")" << endl;
        else if(m == n)
        {
            cout << "WARNING: Both start and end indices for the sublist are the same (";
            cout << n << "), no reversals done in the list" << endl;
        }

        return head;
    }
    
    // Count nodes in the given list
    node* temp = head;
    int count = 0;

    while(temp)
    {
        count++;
        temp = temp->next;
    }
    
    // Throw an error if either or both of the indices passed are greater than the number of nodes in the list
    if( (m >= count) || (n >= count) )
    {
        if( (m >= count) && (n >= count) )
        {
            cout << "ERROR: Indices passed for sublist are greater than the nodes in the list";
            cout << ", start = (" << m << "), end = (" << n << ")" << endl;
        }
        else if(m >= count)
            cout << "ERROR: Start index passed for sublist is greater than the nodes in the list, (" << m << ")" << endl;
        else
            cout << "ERROR: End index passed for sublist is greater than the nodes in the list, (" << n << ")" << endl;

        return head;
    }

    // Swap m and n if (n < m) so that m is the start and n is the end of the sublist to be reversed
    if(n < m)
    {
        m ^= n;
        n ^= m;
        m ^= n;
    }

    // Find start and end nodes of the sublist to be reversed
    node* start = head, *start_prev = nullptr;
    node* end = head, *end_next = nullptr;
    bool start_found = false, end_found = false;
    count = 0;
    temp = head;

    while(!start_found || !end_found)
    {
        if(!start_found)
        {
            if(m == 0) // Head is part of sublist
            {
                start = temp;
                start_found = true;
            }
            else if(count+1 == m)
            {
                start_prev = temp;
                start = temp->next;
                start_found = true;
            }
        }
        
        if(!end_found && (count == n))
        {
            end = temp;
            end_next = temp->next;
            end_found = true;
        }
        
        count++;
        temp = temp->next;
    }

    // Set the sublist as its own list, so the generic reverse list functions can be used
    end->next = nullptr;

    // Connect the node before start of sublist to the reversed sublist
    if(start_prev)
        start_prev->next = reverseListRecursive(start);
    else // start is head
        head = reverseListIterative(start);
    
    // Connect the end of sublist to the rest of the list passed
    // NOTE - This will work even if the end of sublist is the last node in the list
    start->next = end_next;

    return head;
}

int main()
{
    node* head = nullptr;
    head = insertAtHead(head, 6);
    head = insertAtHead(head, 5);
    head = insertAtHead(head, 4);
    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);
    cout << endl << "Original ";
    printList(head);

    // Test 1
    cout << endl << "--> Reverse sublist with indices 2 and 4" << endl;
    head = reverseSublistInLinkedList(head, 2, 4);
    printList(head);
    
    // Test 2
    cout << endl << "--> Reverse sublist with indices 4 and 0" << endl;
    head = reverseSublistInLinkedList(head, 4, 0);
    printList(head);
    
    // Test 3
    cout << endl << "--> Reverse sublist with indices 3 and 5" << endl;
    head = reverseSublistInLinkedList(head, 3, 5);
    printList(head);

    // Test 4
    cout << endl << "--> Reverse sublist with same start and end index 5" << endl;
    head = reverseSublistInLinkedList(head, 5, 5);
    
    // Test 5
    cout << endl << "--> Reverse sublist with one invalid index -3 and 5" << endl;
    head = reverseSublistInLinkedList(head, -3, 5);

    // Test 6
    cout << endl << "--> Reverse sublist with invalid indices 100 and 200" << endl;
    head = reverseSublistInLinkedList(head, 100, 200);
    
    // Test 7
    cout << endl << "--> Reverse sublist in an empty (null) list" << endl;
    head = reverseSublistInLinkedList(nullptr, -3, 5);

    cout << endl;
    return 0;
}