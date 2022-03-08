#include <stdio.h>
#include <string.h>
#include <stdint.h>

int64_t* max;

int64_t maxpoints(int* seq, int num)
{
    if (max[num] != -1)
        return max[num];

    if (num == 0)
    {
        max[num] = 0;
        return 0;
    }

    if (num == 1)
    {
        max[num] = seq[1];
        return max[num];
    }

    max[num] = maxpoints(seq, num - 1) > (maxpoints(seq, num - 2) + (int64_t)num * seq[num]) ? maxpoints(seq, num - 1) : maxpoints(seq, num - 2) + (int64_t)num * seq[num];
    return max[num];
}

int main()
{
    max = new int64_t[100001];
    memset(max, -1, sizeof(int64_t) * 100001);

    int* seq = new int[100001];
    memset(seq, 0, sizeof(int) * 100001);

    int n;
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%i", &a);
        seq[a]++;
    }

    for (int i = 0; i < 100001; i++)
    {
        maxpoints(seq, i);
    }

    printf("%lli\n", maxpoints(seq, 100000));
}
