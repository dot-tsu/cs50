// Design and implement a program, caesar, that encrypts messages using Caesar’s cipher.
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool onlyDigits(string text);

int main(int argc, string argv[])
{
    if (argc != 2 || !onlyDigits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int secretKey = atoi(argv[1]);

    string plainText = get_string("plaintext: "), cipherText = plainText;

    for (int currentChar = 0, textLength = strlen(plainText); currentChar < textLength; currentChar++)
    {
        if (isalpha(plainText[currentChar]))
        {
            char base = isupper(plainText[currentChar]) ? 'A' : 'a';
            cipherText[currentChar] = ((plainText[currentChar] - base + secretKey) % 26) + base;
        }
    }
    printf("ciphertext: %s\n", cipherText);
}

bool onlyDigits(string text)
{
    for (int currentChar = 0, length = strlen(text); currentChar < length; currentChar++)
    {
        if (!isdigit(text[currentChar]))
            return false;
    }
    return true;
}
