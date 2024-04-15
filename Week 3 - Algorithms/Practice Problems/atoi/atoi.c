// / Imagine that you travel back in time to the 1970’s, when the C programming language was first created.
// You are hired as a programmer to come up with a way to convert strings to ints.
// (You may have used a function just like this in Week 2, called atoi).
// You want to be thorough in your development process and plan to try several approaches before deciding on the most efficient.

// In this problem, you will start with a simple implementation of atoi that handles positive
// ints using loops.You want to rework this into an implementation that uses recursion.Recusive
// functions can be memory intensive and are not always the best solution,
// but there are some problems in which using recursion can provide a simpler and more elegant solution.

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // If first character is "null" return 0
    if (input[0] == '\0')
    {
        return 0;
    }
    // Find the index of the last character in the string
    int lastChar = strlen(input) - 1;

    // Convert the last character to it's numeric value
    int numericValueOfChar = input[lastChar] - '0';

    // Shorten the string by removing the last character
    input[lastChar] = '\0';

    // Recursively call atoi on the shortened string
    int result = convert(input);

    // Calculate the final result
    return (result * 10) + numericValueOfChar;
}
