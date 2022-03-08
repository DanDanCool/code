#include <stdio.h>

int main()
{
    char digits[100];
    int m, s, it = 0;
    scanf("%i%i", &m, &s);

    double d = m;
    double left = s;
    double avg = left / d;
    double pref = 0.0;

    if (avg > 9.0 || avg <= 0.0)
    {
        if (s == 0 && m == 1)
            printf("0 0");
        else
            printf("-1 -1");

        return 0;
    }

    int firstnotzero = -1;
    while (it < m)
    {
        if (d > 1.0)
        {
            while ((left - pref) / (d - 1.0) > 9.0)
                pref += 1.0;
        }
        else
        {
            pref = left;
        }

        if (pref > 0.0 && firstnotzero == -1)
            firstnotzero = it;

        digits[it] = '0' + (char)pref;
        left -= pref;
        d -= 1.0;
        it++;
    }

    digits[m] = 0;
    if (digits[0] == '0')
    {
        digits[0] = '1';
        digits[firstnotzero] = digits[firstnotzero] - 1;

        printf("%s ", digits);

        digits[0] = '0';
        digits[firstnotzero] = digits[firstnotzero] + 1;
    }
    else
    {
        printf("%s ", digits);
    }

    for (int i = m - 1; i >= 0; i--)
    {
        printf("%c", digits[i]);
    }
}
