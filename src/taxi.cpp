#include <stdio.h>

int main()
{
    int n = 0, a = 0, b = 0, c = 0, d = 0;
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        int e;
        scanf("%i", &e);

        switch(e)
        {
            case 4: a++; break;
            case 3: b++; break;
            case 2: c++; break;
            case 1: d++; break;
        }
    }

    // groups of fours
    int t = a;

    // groups of 3s and 1s
    int m = b > d ? d : b;
    t += m;
    b -= m;
    d -= m;

    // groups of 2
    t += c / 2;
    c = c % 2;

    t += b;
    t += c;

    if (c)
        d -= 2;

    d = d < 0 ? 0 : d;

    t += d / 4;
    d = d % 4;

    if (d)
        t++;

    printf("%i\n", t);
}
