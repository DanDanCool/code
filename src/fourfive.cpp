#include <stdio.h>

int res[40];

int main()
{
    int n;
    scanf("%i", &n);

    int rem = n % 20;
    n = n - rem;
    rem = rem ? rem : 20;

    int i = 4;
    res[4] = 1;
    res[5] = 1;

    while (true)
    {
        if (res[i])
        {
            res[i + 4] = 1;
            res[i + 5] = 1;
        }

        if (i >= rem)
            break;

        i++;
    }

    int ans = 0;

    if (res[rem])
    {
        ans = 1 + (n / 20);
    }

    printf("%i\n", ans);
}
