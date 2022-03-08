#include <stdio.h>
#include <stdlib.h>

int compare(const void* p1, const void* p2)
{
    int a = *(int*)p1;
    int b = *(int*)p2;

    return a - b;
}

int find(int* prices, int num, int key)
{
    int beg = 0;
    int end = num - 1;
    int mid = (end + beg) / 2;

    while (true)
    {
        if (key < prices[mid])
            end = mid > 0 ? mid - 1 : 0;

        if (key > prices[mid])
            beg = mid < num ? mid + 1 : num;

        mid = (end + beg) / 2;

        if (key == prices[mid] || beg >= end)
            break;
    }

    while (mid < (num - 1) && key >= prices[mid + 1])
        mid++;

    while (mid >= 0 && key < prices[mid])
        mid--;

    return mid + 1;
}

int main()
{
    int n, q;
    int* prices = new int[100000];

    scanf("%i", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%i", &prices[i]);
    }

    qsort((void*)prices, n, sizeof(int), compare);

    scanf("%i", &q);
    for (int i = 0; i < q; i++)
    {
        int c;
        scanf("%i", &c);

        printf("%i\n", find(prices, n, c));
    }
}
