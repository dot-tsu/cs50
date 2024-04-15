// Complete the implementation of scrabble.c, such that it determines the winner of a short scrabble-like game, where two players
// each enter their word, and the higher scoring player wins.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    printf(score1 > score2 ? "Player 1 wins!\n" : (score2 > score1 ? "Player 2 wins!\n" : "Tie!\n"));
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int totalPoints = 0;

    for (int currentChar = 0, wordLength = strlen(word); currentChar < wordLength; currentChar++)
    {
        if (!ispunct(word[currentChar]))
        {
            totalPoints += POINTS[toupper(word[currentChar]) - 65];
        }
    }
    return totalPoints;
}
