#include <stdio.h>
#include <ctype.h>

char* numtocol(int n)
{

}

int main()
{
    int n;
    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        int n, c, rowcol = 0;
        char str[100];
        scanf("%s", str);

        if (str[0] == 'R' && isdigit(str[1]))
        {
            for (int i = 2; i < 100; i++)
            {
                if (!str[i])
                {
                    n = i;
                    break;
                }

                if (str[i] == 'C')
                {
                    rowcol = 1;
                    c = i;
                }
            }
        }

        if (rowcol)
        {
            int row, col;
            str[c] = 0;
            row = strtol(&str[1], NULL, 10);
            col = strtol(&str[c + 1], NULL, 10);
        }
        else
        {

        }
    }
}
