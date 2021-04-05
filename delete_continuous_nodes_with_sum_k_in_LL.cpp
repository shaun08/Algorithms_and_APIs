/* 2021-04-03: SHAUN08 ->

Problem: Write a program to delete continuous nodes in a Linked List with sum K
Note:
1 - K is greater than 0
2 - A single node with value K is also considered a continuous node with sum K

Example 1:
Linked List: 1 -> 2 -> -3 -> 3 -> 1, K = 3 
Output: -3 -> 1 

Example 2:
Linked List: 1 -> 1 -> -3 -> -3 -> -2, K = 5 
Output: 1 -> 1 -> -3 -> -3 -> -2
*/

#include <iostream>
#include <unordered_map>

using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

void insertAtHead(Node ** head, int data)
{
    auto new_node = new Node(data);
    new_node->next = *head;
    *head = new_node;
}

void printList(Node* head)
{
    cout << "List: ";

    while(head)
    {
        cout << "(" << head->data << ") -> ";
        head = head->next;
    }

    cout << "NULL" << endl;
}

void deleteContinuousNodes(Node** head, int k)
{
    if(*head == nullptr)
        return;
    
    unordered_map<int, Node*> sum_map;
    int sum = 0;
    Node* curr = *head;

    Node* root = new Node(0);
    root->next = *head;
    sum_map[0] = root;

    while(curr)
    {
        sum += curr->data;

        if(sum_map.find(sum - k) != sum_map.end())
        {
            Node* prev = sum_map[sum-k];
            Node* start = prev->next;
            Node* end = curr->next;
            int aux = sum;
            sum = sum-k;

            while(start != end)
            {
                Node* temp = start;
                aux += start->data;
                sum_map.erase(aux);
                start = start->next;
                delete temp;
            }

            prev->next = start;
            curr = start;
        }
        else
        {
            if(sum_map.find(sum) == sum_map.end())
                sum_map[sum] = curr;
        
            curr = curr->next;
        }
    }

    *head = root->next;
}

int main()
{
    // List 1
    Node* head = new Node(1);
    insertAtHead(&head, 3);
    insertAtHead(&head, -3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);
    cout << endl << "First ";
    printList(head);

    cout << "Deleting continous nodes with K=3 in the list above" << endl;
    deleteContinuousNodes(&head, 3);
    cout << "New ";
    printList(head);
    cout << endl;

    // List 2
    Node* head2 = new Node(2);
    insertAtHead(&head2, -3);
    insertAtHead(&head2, -3);
    insertAtHead(&head2, 1);
    insertAtHead(&head2, 1);
    cout << "Second ";
    printList(head2);

    cout << "Deleting continous nodes with K=5 in the list above" << endl;
    deleteContinuousNodes(&head2, 5);
    cout << "New ";
    printList(head2);
    cout << endl;

    return 0;
}