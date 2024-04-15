#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startPopulationSize, targetPopulationSize, currentLlamas;
    int yearsRequired = 0;
    // Prompt for start size
    do
    {
        startPopulationSize = get_int("Please enter the starting population size: ");
    }
    while (startPopulationSize < 9);
    // Prompt for end size
    do
    {
        targetPopulationSize = get_int("Please enter the target population size: ");
    }
    while (targetPopulationSize < startPopulationSize);
    // Calculate number of years until we reach threshold
    currentLlamas = startPopulationSize;

    while (currentLlamas < targetPopulationSize)
    {
        currentLlamas += (currentLlamas / 3) - (currentLlamas / 4);
        yearsRequired++;
    }
    // Print number of years
    printf("Years: %i\n", yearsRequired);
}
