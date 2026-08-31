#include <stdio.h>
#include <stdlib.h>

// 链表节点定义
typedef struct Link
{
    int data;
    struct Link *next;
} Link;

Link *insertElem(Link *p, int elem, int add)
{
    Link *newNode = (Link *)malloc(sizeof(Link));
    if (newNode == NULL)
        return p;
    newNode->data = elem;
    newNode->next = NULL;

    if (add == 1)
    {
        newNode->next = p;
        return newNode;
    }

    Link *cur = p;
    int i = 1;
    while (cur != NULL && i < add - 1)
    {
        cur = cur->next;
        i++;
    }
    if (cur == NULL)
    {
        free(newNode);
        return p;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return p;
}

int findElem(Link *p, int add)
{
    Link *cur = p;
    int i = 1;
    while (cur != NULL && i < add)
    {
        cur = cur->next;
        i++;
    }
    if (cur == NULL)
        return -1;
    return cur->data;
}

Link *deleteElem(Link *p, int add)
{
    if (p == NULL)
        return NULL;
    Link *del = NULL;
    if (add == 1)
    {
        del = p;
        p = p->next;
        free(del);
        return p;
    }

    Link *cur = p;
    int i = 1;
    while (cur != NULL && i < add - 1)
    {
        cur = cur->next;
        i++;
    }
    if (cur == NULL || cur->next == NULL)
        return p;

    del = cur->next;
    cur->next = del->next;
    free(del);
    return p;
}

// 打印整个链表，辅助看结果
void printList(Link *p)
{
    Link *cur = p;
    printf("list: ");
    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// 测试主函数
int main(void)
{
    Link *head = NULL; // 空链表

    // 在1号位置插入10
    head = insertElem(head, 10, 1);
    printList(head);

    // 在2号位置插入20
    head = insertElem(head, 20, 2);
    printList(head);

    // 在2号位置插入15
    head = insertElem(head, 15, 2);
    printList(head);

    // 查询第2个元素
    int val = findElem(head, 2);
    printf("pos2 value = %d\n", val);

    // 删除第3个位置
    head = deleteElem(head, 3);
    printList(head);

    // 删除头节点
    head = deleteElem(head, 1);
    printList(head);

    return 0;
}
