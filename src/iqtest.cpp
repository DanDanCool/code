#include <stdio.h>

int main()
{
    int n, nodd = 0, neven = 0;
    int odd[100];
    int even[100];

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        int d;
        scanf("%d", &d);

        switch (d % 2)
        {
            case 0:
                {
                    odd[nodd] = i;
                    nodd++;
                    break;
                }

            case 1:
                {
                    even[neven] = i;
                    neven++;
                    break;
                }
        }
    }

    int res;

    if (nodd == 1)
        res = odd[0] + 1;
    else
        res = even[0] + 1;

    printf("%i\n", res);
}
