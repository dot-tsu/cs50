// Prime numbers are defined as whole numbers greater than 1, whose only factors are 1 and itself. So 3 is prime because its only
// factors are 1 and 3, while 4 is composite and not prime, because it is the product of 2 × 2. In this lab you will write an
// algorithm to generate all prime numbers in a range specified by the user.

Hints
#include <cs50.h>
#include <stdio.h>

    bool
    prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // By definition, 1 is not a prime number.
    if (number == 1)
    {
        return false;
    }

    // Check if the remainder of every number from 2 up to the number itself is 0, if not, returns false because that number isnt
    // prime.
    for (int i = 2; i < number; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }

    // Returns true when the remainder of every number from 2 up to the number itself is 0.
    return true;
}
