#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
void checksum(int num[], int len)
{
    int sum = 0;
    for (int i = 0; i <= len; i++)
    {
        if (i % 2 == 1)
        {
            sum += 2 * num[i] % 10;
            sum += 2 * num[i] / 10;
        }
        else
        {
            sum += num[i];
        }
    }
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        exit(0);
    }
}
int main(void)
{
    long n;
    int len = -1;
    int cn[20] = {0};
    do
    {
        n = get_long("Number: ");
    }
    while (n == LONG_MAX);
    for (int i = 0; n != 0; i++)
    {
        cn[i] = n % 10;
        n = n / 10;
        len++;
    }
    checksum(cn, len);
    if (cn[len] == 3 && (cn[len - 1] == 4 || cn[len - 1] == 7) && len == 14)
    {
        printf("AMEX\n");
    }
    else if (cn[len] == 5 && cn[len - 1] >= 1 && cn[len - 1] <= 5 && len == 15)
    {
        printf("MASTERCARD\n");
    }
    else if (cn[len] == 4 && (len == 12 || len == 15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
