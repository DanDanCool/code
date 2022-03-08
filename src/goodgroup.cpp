#include <stdio.h>
#include <stdint.h>

#define MAXN 187091
uint32_t samegroup[MAXN];
uint32_t diffgroup[MAXN];

uint32_t hash(const char* key)
{
    uint32_t hash = 0x811c9dc5;

    while (*key)
    {
        hash = (hash ^ *key) * 0x01000193;
        key++;
    }

    return hash % MAXN;
}

int main()
{
    int x;
    scanf("%i", &x);

    for (int i = 0; i < x; i++)
    {
        char str[100];
        scanf("%s", str);

        uint32_t key = hash(str);

        scanf("%s", str);

        uint32_t val = hash(str);

        samegroup[key] = val;
        samegroup[val] = key;
    }

    int y;
    scanf("%i", &y);

    for (int i = 0; i < y; i++)
    {
        char str[100];
        scanf("%s", str);

        uint32_t key = hash(str);

        scanf("%s", str);

        uint32_t val = hash(str);

        diffgroup[key] = val;
        diffgroup[val] = key;
    }

    int g, count = 0;
    scanf("%i", &g);

    for (int i = 0; i < g; i++)
    {
        uint32_t a, b, c;

        char str[100];
        scanf("%s", str);
        a = hash(str);

        scanf("%s", str);
        b = hash(str);

        scanf("%s", str);
        c = hash(str);

        if (samegroup[a] && (samegroup[a] != b && samegroup[a] != c))
        {
            samegroup[samegroup[a]] = 0;
            samegroup[a] = 0;
            count++;
        }

        if (samegroup[b] && (samegroup[b] != a && samegroup[b] != c))
        {
            samegroup[samegroup[b]] = 0;
            samegroup[b] = 0;
            count++;
        }

        if (samegroup[c] && (samegroup[c] != b && samegroup[c] != a))
        {
            samegroup[samegroup[c]] = 0;
            samegroup[c] = 0;
            count++;
        }

        if (diffgroup[a] && (diffgroup[a] == b || diffgroup[a] == c))
        {
            diffgroup[diffgroup[a]] = 0;
            diffgroup[a] = 0;
            count++;
        }

        if (diffgroup[b] && (diffgroup[b] == a || diffgroup[b] == c))
        {
            diffgroup[diffgroup[b]] = 0;
            diffgroup[b] = 0;
            count++;
        }

        if (diffgroup[c] && (diffgroup[c] == b || diffgroup[c] == a))
        {
            diffgroup[diffgroup[c]] = 0;
            diffgroup[c] = 0;
            count++;
        }
    }

    printf("%i\n", count);
}
