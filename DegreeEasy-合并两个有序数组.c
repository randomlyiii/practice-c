#include <stdio.h>

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
    int p1 = m - 1;    // nums1有效元素末尾
    int p2 = n - 1;    // nums2末尾
    int p = m + n - 1; // nums1总数组末尾

    // 两个数组都没遍历完
    while (p1 >= 0 && p2 >= 0)
    {
        if (nums1[p1] > nums2[p2])
        {
            nums1[p] = nums1[p1];
            p1--;
        }
        else
        {

            nums1[p] = nums2[p2];
            p2--;
        }
        p--;
    }
    // 如果nums2还有剩余元素，全部拷贝到nums1前面
    while (p2 >= 0)
    {
        nums1[p] = nums2[p2];
        p--;
        p2--;
    }
}

int main(void)
{
    // 示例测试用例
    int nums1[] = {1, 2, 3, 0, 0, 0};
    int m = 3;
    int nums2[] = {2, 5, 6};
    int n = 3;
    int size1 = sizeof(nums1) / sizeof(int);
    int size2 = sizeof(nums2) / sizeof(int);

    merge(nums1, size1, m, nums2, size2, n);

    // 打印结果
    for (int i = 0; i < m + n; i++)
    {
        printf("%d ", nums1[i]);
    }
    printf("\n");
    return 0;
}
