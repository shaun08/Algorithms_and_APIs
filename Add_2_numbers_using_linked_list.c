// 2021-03-09: SHAUN08 --> Add two numbers represented by Singly Linked List
//                         EXAMPLE: 6->1->7 + 2->9->5 = 9->1->2
//                         NOTE: This code is run on 64-bit machine

#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node_tag
{
    uint8_t digit;
    struct node_tag* next;
} Node;

void insertAtHead(Node** head, uint8_t digit)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->digit = digit;
    new_node->next = *head;
    *head = new_node;
}

void insertAtTail(Node** head, uint8_t digit)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->digit = digit;
    new_node->next = NULL;

    if(*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        Node* temp = *head;

        while(temp->next)
            temp = temp->next;

        temp->next = new_node;
    }
}

Node* reverseList(Node* head)
{
    if(head == NULL)
        return head;
    
    if(head->next == NULL)
        return head;
    
    Node* prev = NULL;
    Node* next = NULL;
    Node* curr = head;

    while(curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

void printList(Node* list)
{
    printf("List: ");

    while(list)
    {
        printf("%d->",list->digit);
        list = list->next;
    }

    printf("NULL\n");
}

Node* createList(uint64_t num)
{
    Node* list = NULL;

    while(num)
    {
        insertAtHead(&list, (uint8_t)(num%10));
        num = num/10;
    }

    return list;
}

uint64_t getNumber(Node* list)
{
    uint64_t num = 0;
    uint64_t prev_num = 0;

    while(list)
    {
        prev_num = num;
        num = ((uint64_t)num * 10) + (uint64_t)list->digit;
        
        //Check for UINT64 overflow
        if(num < prev_num)
        {
            printf("ERROR: Number in list is greater than UINT64_MAX, truncating number to UINT64_MAX here\n");
            return UINT64_MAX;
        }

        list = list->next;
    }

    return num;
}

Node* addTwoNumbers(Node* head1, Node* head2)
{
    Node* sum_list = NULL;

    if(head1 == NULL && head2 == NULL)
        ; // Do Nothing
    else if(head1 == NULL)
    {
        while(head2)
        {
            insertAtTail(&sum_list, head2->digit);
            head2 = head2->next;
        }
    }
    else if(head2 == NULL)
    {
        while(head1)
        {
            insertAtTail(&sum_list, head1->digit);
            head1 = head1->next;
        }
    }
    else
    {
        uint8_t sum = 0;
        uint8_t carry = 0;
        Node* tail1 = head1;
        Node* tail2 = head2;

        if(head1->next != NULL)    
            tail1 = reverseList(head1);
        
        if(head2->next != NULL)
            tail2 = reverseList(head2);

        while(tail1 && tail2)
        {
            sum = tail1->digit + tail2->digit + carry;

            carry = sum/10;
            sum  %= 10;

            insertAtHead(&sum_list, sum);

            tail1 = tail1->next;
            tail2 = tail2->next;
        }

        while(tail1)
        {
            sum = tail1->digit + carry;

            carry = sum/10;
            sum  %= 10;

            insertAtHead(&sum_list, sum);

            tail1 = tail1->next;
        }

        while(tail2)
        {
            sum = tail2->digit + carry;

            carry = sum/10;
            sum  %= 10;

            insertAtHead(&sum_list, sum);

            tail2 = tail2->next;
        }

        if(carry)
        {
            insertAtHead(&sum_list, carry);
        }
    }

    return sum_list;
}

void runTest(uint64_t a, uint64_t b)
{
    Node* a_list = createList(a);
    printf("A: %llu, ",a);
    printList(a_list);

    Node* b_list = createList(b);
    printf("B: %llu, ",b);
    printList(b_list);

    Node* sum_list = addTwoNumbers(a_list, b_list);
    uint64_t sum = getNumber(sum_list);
    printf("Sum: %llu, ",sum);
    printList(sum_list);
    printf("\n");
}

int main()
{
    // Add two numbers
    uint64_t a = 617;
    uint64_t b = 295;
    runTest(a,b); // Expected sum = 912

    // Add two large numbers
    a = 6175655;
    b = 2954654651;
    runTest(a,b); // Expected sum = 2960830306

    // Add two 0's
    a = 0;
    b = 0;
    runTest(a,b); // Expected sum = 0

    // Add when 1st number is 0
    a = 42354625;
    runTest(a,b); // Expected sum = 42354625

    // Add when 2nd number is 0
    a = 0;
    b = 165461;
    runTest(a,b); // Expected sum = 165461

    // Add when sum overflow occurs on 64-bit unsigned int
    // NOTE: - In this case sum is expected to not match sum_list
    //       - Sum will be truncated to UINT64_MAX while the sum_list will have the correct value
    a = UINT64_MAX;
    b = 1;
    runTest(a,b); // Expected sum = UINT64_MAX (18446744073709551615) with ERROR string

    return 0;
}