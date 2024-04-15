// There are many situations where you’ll find it helpful to have a function that finds the maximum (and minimum) value in an array.
//  Since there is no built-in max function in C, you’ll create one in this practice problem. You can then use it in upcoming
//  problem sets where it may be helpful!

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    int largestNumber = array[0];
    for (int currentNumberIndex = 0; currentNumberIndex < n; currentNumberIndex++)
    {
        if (array[currentNumberIndex] > largestNumber)
        {
            largestNumber = array[currentNumberIndex];
        }
    }
    return largestNumber;
}
