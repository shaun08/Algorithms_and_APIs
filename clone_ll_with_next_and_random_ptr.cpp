/* 2021-03-11: SHAUN08 ->

Problem: Write a program to clone a linked list with next and random pointer
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

#include <iostream>
#include <unordered_map>

class Node
{
public:
    int data {0};
    Node* next {nullptr};
    Node* random {nullptr};

    Node(int data = 0) : data(data), next(nullptr), random(nullptr) {}
};

class LinkedList
{
public:
    Node* m_head {nullptr};
    Node* m_tail {nullptr};

    LinkedList(Node* head = nullptr) : m_head(head)
    {
        if(head)
        {
            while(head->next)
                head = head->next;
        }

        m_tail = head;
    }

    ~LinkedList()
    {
        while(m_head)
        {
            Node* temp = m_head;
            m_head = m_head->next;
            delete temp;
        }

        m_head = nullptr;
        m_tail = nullptr;
    }

    void insertAtTail(int data)
    {
        if(m_tail)
        {
            m_tail->next = new Node(data);
            m_tail = m_tail->next;
        }
        else
        {
            m_tail = new Node(data);
            m_head = m_tail;
        }
    }

    void printList()
    {
        std::cout << "List:" << std::endl;

        Node* temp = m_head;
        while(temp)
        {
            std::cout << "Data: " << temp->data;

            if(temp->random)
                std::cout << ", Random data: " << temp->random->data << std::endl;
            else
                std::cout << ", Random data: NULL" << std::endl;
            
            temp = temp->next;
        }

        std::cout << "End of list" << std::endl;
    }

    // Method to clone the current linked list and return pointer to new list
    LinkedList* clone()
    {
        Node* orig_curr = m_head;
        Node* new_curr = nullptr;

        std::unordered_map<Node*, Node*> hash_map;

        // Set up the new list and add current as well as new list's nodes as key-value pair in hash map
        while(orig_curr)
        {
            new_curr = new Node(orig_curr->data);
            hash_map[orig_curr] = new_curr;
            orig_curr = orig_curr->next;
        }

        // Use the hash map to complete linking of new linked list
        orig_curr = m_head;
        while(orig_curr)
        {
            new_curr = hash_map[orig_curr];
            new_curr->next = hash_map[orig_curr->next];
            new_curr->random = hash_map[orig_curr->random];
            orig_curr = orig_curr->next;
        }

        return new LinkedList(m_head ? hash_map[m_head] : nullptr);
    }
};

int main()
{
    // Set up data in linked list (refer example at top)
    LinkedList ll;
    ll.insertAtTail(1);
    ll.insertAtTail(2);
    ll.insertAtTail(3);
    ll.insertAtTail(4);
    ll.insertAtTail(5);
    
    // Set up the random pointers in this list (refer example at top)
    ll.m_head->random = ll.m_tail;
    ll.m_head->next->random = ll.m_head->next;
    ll.m_head->next->next->next->random = ll.m_head;
    ll.m_head->next->next->next->next->random = ll.m_head;

    std::cout << std::endl << "Original ";
    ll.printList();

    // Create a clone list in O(n) time and space complexity
    LinkedList *ll_clone_p = ll.clone();
    std::cout << std::endl << "Clone ";
    ll_clone_p->printList();
    delete ll_clone_p;
    ll_clone_p = nullptr;

    // Create a clone of empty linked list
    LinkedList ll_2;
    std::cout << std::endl << "Empty Original ";
    ll_2.printList();
    ll_clone_p = ll_2.clone();
    std::cout << std::endl << "Empty Clone ";
    ll_clone_p->printList();
    delete ll_clone_p;
    ll_clone_p = nullptr;
    
    std::cout << std::endl;
    
    return 0;
}