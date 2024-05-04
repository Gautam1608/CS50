#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int n = 0;
    while (n <= 0 || n >= 9)
    {
        n = get_int("Height: ");
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
