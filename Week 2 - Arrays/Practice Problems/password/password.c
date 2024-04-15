// As we all know by now, it’s important to use passwords that are not easy to guess! Many web apps now require passwords that
// require not only alphabetical characters, but also number and symbols.

// In this lab, the user is prompted for a password, which will then be validated using a function check that you will complete. If
// the password contains at least one upper case letter, one lower case letter, a number, and a symbol (meaning a printable
// character that’s not a letter or number, such as ‘!’, ‘$’ and ‘#’), the function should return true. If not it should return
// false.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool hasUppercase = false, hasLowercase = false, hasNumber = false, hasSymbol = false;

    for (int currentChar = 0, length = strlen(password); currentChar < length; currentChar++)
    {
        if (isupper(password[currentChar]))
        {
            hasUppercase = true;
        }
        else if (islower(password[currentChar]))
        {
            hasLowercase = true;
        }
        else if (isdigit(password[currentChar]))
        {
            hasNumber = true;
        }
        else if (ispunct(password[currentChar]))
        {
            hasSymbol = true;
        }
    }

    return hasUppercase && hasLowercase && hasNumber && hasSymbol;
}
