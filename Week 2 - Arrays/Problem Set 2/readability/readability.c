#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float L = (float) countLetters(text) / (float) countWords(text) * 100;
    float S = (float) countSentences(text) / (float) countWords(text) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (index > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", index);
}

int countLetters(string text)
{
    int totalLetters = 0;
    for (int currentChar = 0, textLength = strlen(text); currentChar < textLength; currentChar++)
    {
        if (isalpha(text[currentChar]))
        {
            totalLetters++;
        }
    }
    return totalLetters;
}

int countWords(string text)
{
    int totalWords = 1;
    for (int currentChar = 0, textLength = strlen(text); currentChar < textLength; currentChar++)
    {
        if (isspace(text[currentChar]))
        {
            totalWords++;
        }
    }
    return totalWords;
}

int countSentences(string text)
{
    int totalSentences = 0;
    for (int currentChar = 0, textLength = strlen(text); currentChar < textLength; currentChar++)
    {
        if (text[currentChar] == 33 || text[currentChar] == 46 || text[currentChar] == 63)
        {
            totalSentences++;
        }
    }
    return totalSentences;
}
