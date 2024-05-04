#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    int a[26] = {};
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        int temp = (toupper(argv[1][i]) - 'A');
        if (temp < 0 || temp > 25)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        if (!a[temp])
        {
            a[temp] = 1;
        }
        else
        {
            printf("Key should consist Unique Alphabets only.\n");
            return 1;
        }
    }
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; s[i] != '\0'; i++)
    {
        if ((s[i] - 'A') >= 0 && (s[i] - 'A') <= 25)
        {
            printf("%c", toupper(argv[1][s[i] - 'A']));
        }
        else if ((s[i] - 'a') >= 0 && (s[i] - 'a') <= 25)
        {
            printf("%c", tolower(argv[1][s[i] - 'a']));
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
