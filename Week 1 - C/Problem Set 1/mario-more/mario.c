#include <cs50.h>
#include <stdio.h>

void makePyramid(int pyramidHeight);
void printHashes(int floor);

int main(void)
{
    // Ask the user for the height input.
    int pyramidHeight;
    do
    {
        pyramidHeight = get_int("How tall do you want the pyramids to be? (from 1 to 8): ");
    }
    while (pyramidHeight < 1 || pyramidHeight > 8);

    makePyramid(pyramidHeight);
}

void makePyramid(int pyramidHeight)
{
    for (int pyramidFloor = 1; pyramidFloor <= pyramidHeight; pyramidFloor++)
    {
        // Print leading spaces
        for (int leadingSpaces = pyramidHeight; leadingSpaces > pyramidFloor; leadingSpaces--)
        {
            printf(" ");
        }

        // Print left-side blocks
        printHashes(pyramidFloor);

        // Print the gap between blocks
        printf("  ");

        // Print right-side blocks
        printHashes(pyramidFloor);

        // Go to the next floor
        printf("\n");
    }
}

void printHashes(int floor)
{
    for (int blocks = 1; blocks <= floor; blocks++)
    {
        printf("#");
    }
}
