#include <stdio.h>
#include <stdlib.h>

int compare(const void* p1, const void* p2)
{
    int a = *(int*)p1;
    int b = *(int*)p2;

    return a - b;
}

int main()
{
    int n, l;
    int lanterns[1000];
    scanf("%i%i", &n, &l);

    for (int i = 0; i < n; i++)
    {
        scanf("%i", &lanterns[i]);
    }

    qsort(lanterns, n, sizeof(int), compare);

    int max = 0;
    for (int i = 0; i < (n - 1); i++)
    {
        int d = lanterns[i + 1] - lanterns[i];
        max = max > d ? max : d;
    }

    int end1 = lanterns[0] * 2;
    int end2 = (l - lanterns[n - 1]) * 2;
    max = max > end1 ? max : end1;
    max = max > end2 ? max : end2;

    float distance = max / 2.0f;

    printf("%f\n", distance);
}
