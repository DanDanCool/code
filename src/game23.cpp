#include <stdio.h>

int main()
{
    int n, m;
    scanf("%i%i", &n, &m);

    int f = m / n;
    if (m % n != 0)
    {
        printf("%i\n", -1);
        return 0;
    }

    int i = 0, j = 0, tmp = f;

    while (tmp % 3 == 0)
    {
        tmp = tmp / 3;
        i++;
    }

    while (tmp % 2 == 0)
    {
        tmp = tmp / 2;
        j++;
    }

    tmp = 1;
    for (int k = 0; k < i; k++)
        tmp = tmp * 3;

    for (int k = 0; k < j; k++)
        tmp = tmp * 2;

    if (tmp == f)
        printf("%i\n", i + j);
    else
        printf("%i\n", -1);
}
