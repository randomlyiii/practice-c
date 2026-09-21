#include <stdio.h>
#define TOG_BIT(x, n) ((x) ^ (1 << (n))) // 实现位翻转

int i; // 全局变量，静态存储，默认初始值 = 0

int main()
{
    i--;
    if (i > sizeof(int))
    {
        printf(">\n");
    }
    else
    {
        printf("<\n");
    }
    printf("sizeof(int) = %zu\n", sizeof(int));

    unsigned int a = 100;
    int b = -1;
    if (b < a) // 你以为true，实际false！b变成超大无符号数
    {
        printf("b < a\n");
    }
    else if (b > a)
    {
        printf("b > a\n");
    }
    else
    {
        printf("b == a\n");
    }
    printf("unsignedInt : b = %u, a = %u\n", b, a);

    printf("TOG_BIT(7, 1) = %u\n", TOG_BIT(7, 2)); // 7 = 0111, TOG_BIT(7, 2) = 0011 = 3
    return 0;
}
