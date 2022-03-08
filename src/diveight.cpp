#include <stdio.h>
#include <string.h>

const int MAXN = 105;

int n;
bool dp[MAXN][8];
int prev[MAXN][8];

int main()
{
    int n;
    char digits[101];
    scanf("%s", digits);
    n = strlen(digits);

    memset(prev, -1, sizeof(prev));

    dp[0][(digits[0] - '0') % 8] = true;

    for (int i = 1; i < n; i++)
    {
        dp[i][(digits[i] - '0') % 8] = true;

        for (int j = 0; j < 8; j++)
        {
            if (dp[i - 1][j])
            {
                dp[i][(j * 10 + digits[i] - '0') % 8] = true;
                prev[i][(j * 10 + digits[i] - '0') % 8] = j;

                dp[i][j] = true;
                prev[i][j] = j;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (dp[i][0])
        {
            char ans[101];
            int ians = 0;
            int curI = i, curJ = 0;

            while (true)
            {
                if (prev[curI][curJ] == -1 || prev[curI][curJ] != curJ)
                {
                    ans[ians] = s[curI];
                    ians++;
                }

                if (prev[curI][curJ] == -1)
                    break;

                curJ = prev[curI][curJ];
                curI--;
            }

            reverse(all(ans));
            printf("YES\n%s\n", ans);
        }
    }

    printf("NO\n");
}
