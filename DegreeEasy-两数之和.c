#include <stdio.h>
#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int *answer = malloc(2 * sizeof(int));
    if (answer == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < numsSize - 1; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                answer[0] = i;
                answer[1] = j;
                *returnSize = 2;
                return answer;
            }
        }
    }

    free(answer);
    *returnSize = 0;
    return NULL;
}

int main(void)
{
    int nums[] = {2, 7, 11, 15};
    int returnSize = 0;
    int *answer = twoSum(nums, 4, 9, &returnSize);

    if (answer != NULL)
    {
        printf("[%d, %d]\n", answer[0], answer[1]);
        free(answer);
    }

    return 0;
}