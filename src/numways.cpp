#include <stdio.h>
#include <math.h>
#include <stdint.h>

int a[1000010];
uint64_t cnt[1000010];

int main()
{
    int n;
    scanf("%i", &n);

    int64_t s = 0;
    for(int i = 0; i < n; ++i)
    {
        scanf("%i", &a[i]);
        s += a[i];
    }

    if (s % 3)
    {
        printf("0\n");
    }
    else
    {
        s = s / 3;
        int64_t ss = 0;
        for(int i = n - 1; i >= 0; --i)
        {
            ss += a[i];
            if (ss == s)
                cnt[i] = 1;
        }

        for(int i = n - 2; i >= 0; --i)
            cnt[i] += cnt[i + 1];

        int64_t ans = 0;
        ss = 0;

        for(int i = 0; i + 2 < n; ++i)
        {
            ss += a[i];
            if (ss == s)
                ans += cnt[i + 2];
        }

        printf("%lli\n", ans);
    }

    return 0;
}
