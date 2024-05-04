#include <cs50.h>
#include <math.h>
#include <stdio.h>
int main(void)
{
    string p = get_string("Text: ");
    int letters = 0, words = 1, sentences = 0;
    for (int i = 0; p[i] != '\0'; i++)
    {
        if ((p[i] >= 'A' && p[i] <= 'Z') || (p[i] >= 'a' && p[i] <= 'z'))
        {
            letters++;
        }
        else if (p[i] == ' ')
        {
            words++;
        }
        else if (p[i] == '.' || p[i] == '!' || p[i] == '?')
        {
            sentences++;
        }
    }
    float index = 0.0588 * (((float) letters / words) * 100) - 0.296 * (((float) sentences / words) * 100) - 15.8;
    int grade = round(index);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}
