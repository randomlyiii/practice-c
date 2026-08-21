#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode dummy = {0, NULL};
    struct ListNode *tail = &dummy;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry != 0)
    {
        int sum = carry;

        if (l1 != NULL)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL)
        {
            sum += l2->val;
            l2 = l2->next;
        }

        tail->next = malloc(sizeof(struct ListNode));
        if (tail->next == NULL)
        {
            return NULL;
        }
        tail = tail->next;
        tail->val = sum % 10;
        tail->next = NULL;
        carry = sum / 10;
    }

    return dummy.next;
}

struct ListNode *createList(const int *values, int size)
{
    struct ListNode dummy = {0, NULL};
    struct ListNode *tail = &dummy;

    for (int i = 0; i < size; i++)
    {
        tail->next = malloc(sizeof(struct ListNode));
        if (tail->next == NULL)
        {
            return NULL;
        }
        tail = tail->next;
        tail->val = values[i];
        tail->next = NULL;
    }

    return dummy.next;
}

void freeList(struct ListNode *head)
{
    while (head != NULL)
    {
        struct ListNode *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    const int values1[] = {2, 4, 3};
    const int values2[] = {5, 6, 4};
    struct ListNode *l1 = createList(values1, 3);
    struct ListNode *l2 = createList(values2, 3);
    struct ListNode *result = addTwoNumbers(l1, l2);

    for (struct ListNode *node = result; node != NULL; node = node->next)
    {
        printf("%d", node->val);
        if (node->next != NULL)
        {
            printf(" -> ");
        }
    }
    printf("\n");

    freeList(l1);
    freeList(l2);
    freeList(result);
    return 0;
}