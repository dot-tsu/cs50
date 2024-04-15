#include <cs50.h>
#include <stdio.h>

bool calculateChecksum(long creditCardNumber);
string creditCardType(long creditCardNumber);

int main(void)
{
    // Prompt for input.
    long creditCardNumber = get_long("What's your credit card number? ");

    // Print the credit card type.
    printf("%s\n", creditCardType(creditCardNumber));
}

bool calculateChecksum(long creditCardNumber)
{
    int lastDigit, sumOfProductDigits = 0;
    bool odd = false;

    // Scroll through digits
    while (creditCardNumber != 0)
    {
        lastDigit = creditCardNumber % 10;
        creditCardNumber /= 10;

        // Multiply every other digit by 2, starting with the number’s second-to-last digit.
        if (odd)
        {
            lastDigit *= 2;
            if (lastDigit > 9)
            {
                lastDigit -= 9;
            }
        }
        odd = !odd;

        // Sum up all digits
        sumOfProductDigits += lastDigit;
    }

    // If its divisible by 10 means that the card is valid.
    return sumOfProductDigits % 10 == 0;
}

string creditCardType(long creditCardNumber)
{
    int length = 0, firstDigits = 0;
    long tempNumber = creditCardNumber;

    // Check if the card is valid
    if (!calculateChecksum(creditCardNumber))
    {
        return "INVALID";
    };

    // Calculate length of the number.
    while (tempNumber != 0)
    {
        tempNumber /= 10;
        length++;
    }

    tempNumber = creditCardNumber;

    // Calculate first digits.
    while (tempNumber >= 100)
    {
        tempNumber /= 10;
    }

    firstDigits = tempNumber % 100;

    // Return the type of card based on first digits and length.
    if ((length == 13 || length == 16) && firstDigits / 10 == 4)
    {
        return "VISA";
    }
    if (length == 16 && (firstDigits == 51 || firstDigits == 52 || firstDigits == 53 || firstDigits == 54 || firstDigits == 55))
    {
        return "MASTERCARD";
    }
    if (length == 15 && (firstDigits == 34 || firstDigits == 37))
    {
        return "AMEX";
    }
    return "INVALID";
}
