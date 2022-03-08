#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct tree
{
    int pos;
    int height;
};

enum TREE_FLAGS
{
    TREE_USED = 1 << 0,
    TREE_LEFT = 1 << 1,
    TREE_RIGHT = 1 << 2
};

int* max;
uint8_t* flags;

int maxtrees(tree* trees, int num)
{
    if (max[num] != -1)
        return max[num];

    if (num == 0)
    {
        max[num] = 0;
        return 0;
    }

    if (num == 1)
    {
        max[num] = 1;
        flags[num - 1] = TREE_USED | TREE_LEFT;
        return 1;
    }

    int shoulduse = 0;

    tree& t = trees[num - 1];
    int minrange = t.pos - t.height;
    int maxrange = t.pos + t.height;

    tree& prev = trees[num - 2];

    int prevrange = (flags[num - 2] & TREE_LEFT || !flags[num - 2]) ? prev.pos : prev.pos + prev.height;
    if (minrange > prevrange)
    {
        shoulduse = 1;
        flags[num - 1] = TREE_USED | TREE_LEFT;
    }
    else
    {
        tree& next = trees[num];
        if (maxrange < next.pos)
        {
            shoulduse = 1;
            flags[num - 1] = TREE_USED | TREE_RIGHT;
        }
    }

    max[num] = maxtrees(trees, num - 1) + shoulduse;
    return max[num];
}

int main()
{
    max = new int[100001];
    memset(max, -1, sizeof(int) * 100001);

    flags = new uint8_t[100000];
    memset(flags, 0, sizeof(uint8_t) * 100000);

    tree* trees = new tree[100001];

    int n;
    scanf("%i", &n);

    tree& last = trees[n];
    last.pos = INT32_MAX;
    last.height = INT32_MAX;

    for (int i = 0; i < n; i++)
    {
        tree* t = &trees[i];
        scanf("%i%i", &t->pos, &t->height);
    }

    for (int i = 0; i < n; i++)
    {
        maxtrees(trees, i);
    }

    printf("%i\n", maxtrees(trees, n));
}
