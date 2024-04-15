// For this problem, you’ll write a program that implements a substitution cipher
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

    // Function to validate the substitution key
    bool
    validKey(int numberOfArguments, string key);

// Function to encipher a character using the substitution key
char encipher(char character, string key);

int main(int argc, string argv[])
{
    // Check if the substitution key is valid; exit if not
    if (!validKey(argc, argv[1]))
        return 1;

    // Convert the substitution key to uppercase for consistency
    string key = argv[1];
    for (int currentChar = 0, keyLength = strlen(argv[1]); currentChar < keyLength; currentChar++)
    {
        key[currentChar] = toupper(argv[1][currentChar]);
    }

    // Get the plaintext input from the user
    string plainText = get_string("plaintext: "), cipherText = plainText;

    // Encipher the plaintext to create the ciphertext
    for (int currentChar = 0, textLength = strlen(plainText); currentChar < textLength; currentChar++)
    {
        cipherText[currentChar] = encipher(plainText[currentChar], key);
    }

    // Display the ciphertext to the user
    printf("ciphertext: %s\n", cipherText);
}

bool validKey(int numberOfArguments, string key)
{
    // Check if the correct number of command-line arguments are provided
    if (numberOfArguments != 2)
    {
        printf("Usage: ./substitution key\n");
        return false;
    }

    // Check if the key has exactly 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int currentChar = 0, keyLength = strlen(key); currentChar < keyLength; currentChar++)
    {
        // Check if a character is not alphabetic
        if (!isalpha(key[currentChar]))
        {
            printf("Key must be alphabetic\n");
            return false;
        }

        // Check for duplicate characters in the key
        for (int comparisonChar = currentChar + 1; comparisonChar < keyLength; comparisonChar++)
        {
            if (toupper(key[currentChar]) == toupper(key[comparisonChar]))
            {
                printf("The letters in the key cannot be duplicated\n");
                return false;
            }
        }
    }

    return true;
}

char encipher(char character, string key)
{
    // Check if the character is alphabetic
    if (isalpha(character))
    {
        // Determine the base character ('a' or 'A') for case conversion
        char base = islower(character) ? 'a' : 'A';

        // Calculate the offset of the character in the alphabet
        int offset = character - base;

        // Check if the offset is within the valid range (0 to 25)
        if (offset >= 0 && offset < 26)
        {
            // Retrieve the corresponding character from the substitution key
            char cipherChar = key[offset];

            // Preserve the case of the original character
            return (islower(character) ? tolower(cipherChar) : cipherChar);
        }
    }

    // If the character is not alphabetic, return it unchanged
    return character;
}
