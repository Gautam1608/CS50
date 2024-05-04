#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int scrabble(char *player)
{
    int arr[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;
    for (int i = 0; player[i] != '\0'; i++)
    {
        if (player[i] >= 65 && player[i] <= 90)
        {
            score += arr[player[i] - 'A'];
        }
        else if (player[i] >= 97 && player[i] <= 122)
        {
            score += arr[player[i] - 'a'];
        }
    }
    return score;
}
int main(void)
{

    char player1[100];
    char player2[100];
    printf("Player 1: ");
    scanf("%s", player1);
    printf("Player 2: ");
    scanf("%s", player2);
    int score1 = scrabble(player1);
    int score2 = scrabble(player2);
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
