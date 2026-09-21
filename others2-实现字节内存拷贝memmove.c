#include <stdio.h>

void *memmove(void *dest, const void *src, size_t n)
{
    if (n == 0 || dest == NULL || src == NULL)
    {
        return dest;
    }
    // 将指针转换为无符号字符指针，以便按字节进行操作
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (d <= s || d >= s + n) // 没有重叠，直接拷贝
    {
        for (size_t i = 0; i < n; i++)
        {
            d[i] = s[i];
        }
    }
    else // 有重叠，倒序拷贝
    {
        for (size_t i = n; i > 0; i--)
        {
            d[i - 1] = s[i - 1];
        }
    }

    return dest;
}

int main()
{
    char str1[20] = "Hello, World!";
    char str2[20];

    memmove(str2, str1, 13);
    printf("str2: %s\n", str2);

    return 0;
}