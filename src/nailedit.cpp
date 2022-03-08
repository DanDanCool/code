#include <stdio.h>

int lengths[2001];
int dense[2000];

int boardlengths[4001];

struct FenceSet
{
    int* Sparse;
    int* Dense;
    int* Lengths;
    int Index;

    int* SparseExtra;
    int* DenseExtra;
    int IndexExtra;

    FenceSet(int* s, int* d, int* l)
        : Sparse(s)
        , Dense(d)
        , Lengths(l)
        , Index(0)
    {
    }

    void Add(int l)
    {
        if (Sparse[l])
        {
            Sparse[l]++;
            for (int i = 0; i < Index; i++)
            {
                if (Sparse[Dense[i]] == Sparse[l])
                    Lengths[Dense[i] + l]++;
            }

            return;
        }

        for (int i = 0; i < Index; i++)
        {
            Lengths[Dense[i] + l]++;
        }

        Sparse[l] = 1;
        Dense[Index] = l;
        Index++;
    }
};

int main()
{
    int n;
    scanf("%i", &n);

    FenceSet set(lengths, dense, boardlengths);

    scanf("%i", &dense[0]);
    lengths[dense[0]] = 1;
    set.Index = 1;

    for (int i = 0; i < (n - 1); i++)
    {
        int l;
        scanf("%i", &l);
        set.Add(l);
    }

    int best = 0, count = 0;

    for (int i = 0; i < 4001; i++)
    {
        if (boardlengths[i] == best)
            count++;

        if (boardlengths[i] > best)
        {
            best = boardlengths[i];
            count = 1;
        }
    }

    printf("%i %i\n", best, count);
}
