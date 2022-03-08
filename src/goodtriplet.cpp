#include <stdio.h>
#include <unordered_set>
#include <tuple>

using namespace std;

#define MAXN 1000001
int sparse[MAXN];
int dense[MAXN];

int N, C;
int halfc;

int isgood(int a, int b, int c)
{
    if (a == b || a == c || b == c)
        return 0;

    if (halfc)
    {
        if ((a + halfc) % C == b || (a + halfc) % C == c || (b + halfc) % C == c)
            return 0;
    }

    return 1;
}

int main()
{
    unordered_set<tuple<int, int, int>> myset();
    myset.reserve(100000);

    scanf("%i%i", &N, &C);

    halfc = C % 2 ? 0 : C / 2;

    int index = 0;

    for (int i = 0; i < N; i++)
    {
        int a;
        scanf("%i", &a);

        if (!sparse[a])
        {
            sparse[a] = 1;
            dense[index] = a;
            index++;
        }
    }

    int good = 0;

    for (int i = 0; i < index; i++)
    {
        for (int j = 0; j < index; j++)
        {
            for (int k = 0; k < index; k++)
            {
                int a = i;
                int b = j;
                int c = k;

                if (b < a)

                good += isgood(i, j, k);
            }
        }
    }

    printf("%i\n", good);
}
