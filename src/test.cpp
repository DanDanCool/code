#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int success;
    int trials = 10000000;
    for (int i = 0; i < trials; i++)
    {
        int aces = 4;
        int num = 52;
        for (int j = 0; j < 5; j++)
        {
            int random = rand() % num;
            aces -= random < aces;
            num--;
        }

        success += aces == 2;
    }

    float p = success / (float)trials;
    printf("%f\n", p);
}
