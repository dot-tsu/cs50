// If you’ve been on the internet, you might have seen “leetspeak” (or “l33tsp36k” for our purposes!), which involves the
// substitution of symbols for alphabetical characters, where those symbols somewhat resemble their alphabetical counterparts. In
// this lab, you’ll write a program to replace certain vowels with digits!

// Up until now, you’ve frequently written programs for which you’ve been provided distribution code.
// You’ll notice when downloading the “distro” for this problem, you start with nothing more than a couple of commonly used
// libraries and an empty main function. In this problem, you will convert a word, which you will input at the command line, to a
// corresponding word with numbers replacing vowels.

#include <cs50.h>
#include <stdio.h>

string replace(string word);

int main(int argc, string argv[])
{

    if (argc < 1 || argc > 2)
    {
        printf("Wrong number of parameters, use only one word! ");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
}

string replace(string word)
{
    int length = 0;

    while (word[length] != '\0')
    {
        length++;
    }

    for (int currentChar = 0; currentChar < length; currentChar++)
    {
        switch (word[currentChar])
        {
            case 'a':
                word[currentChar] = '6';
                break;
            case 'e':
                word[currentChar] = '3';
                break;
            case 'i':
                word[currentChar] = '1';
                break;
            case 'o':
                word[currentChar] = '0';
                break;
        }
    }
    return word;
}
