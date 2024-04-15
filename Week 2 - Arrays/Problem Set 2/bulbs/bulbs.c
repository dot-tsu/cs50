// Design and implement a program, bulbs, that converts text into instructions for the strip of bulbs on CS50’s stage as follows:

// Implement your program in a file called bulbs.c.
// Your program must first ask the user for a message using get_string.
// Your program must then convert the given string into a series of 8-bit binary numbers, one for each character of the string.
// You can use the provided print_bulb function to print a series of 0s and 1s as a series of yellow and black emoji, which
// represent on and off light bulbs. Each “byte” of 8 symbols should be printed on its own line when outputted; there should be a \n
// after the last “byte” of 8 symbols as well.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void printBulb(int bit);
void convertIntoBinary(char character);
bool binaryChar[BITS_IN_BYTE];

int main(void)
{
    // TODO
    string message = get_string("Message: ");
    for (int currentChar = 0, messageLength = strlen(message); currentChar < messageLength; currentChar++)
    {
        convertIntoBinary(message[currentChar]);
        for (int currentBit = 0; currentBit < BITS_IN_BYTE; currentBit++)
        {
            printBulb(binaryChar[currentBit]);
        }
        printf("\n");
    }
}

void printBulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

void convertIntoBinary(char character)
{
    for (int currentBit = BITS_IN_BYTE - 1; currentBit > 0; currentBit--)
    {
        binaryChar[currentBit] = character % 2;
        character /= 2;
    }
}
