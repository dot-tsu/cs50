// The main function initializes the cities array, calls the sort_cities function and prints out the array in sorted order. You
// will use an O(n2) sorting algorithm of your choice (possibly bubble sort, selection sort, or insertion sort) to sort the array
// by temperature, in descending order.

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string name;
    int temp;
} avg_temp;

avg_temp cities[NUM_CITIES];
avg_temp temporaryCityHolder[1];

void sort_cities_bubble(void);
void sort_cities_selection(void);
void sort_cities_insection(void);

int main(void)
{
    cities[0].name = "Austin";
    cities[0].temp = 97;

    cities[1].name = "Boston";
    cities[1].temp = 82;

    cities[2].name = "Chicago";
    cities[2].temp = 85;

    cities[3].name = "Denver";
    cities[3].temp = 90;

    cities[4].name = "Las Vegas";
    cities[4].temp = 105;

    cities[5].name = "Los Angeles";
    cities[5].temp = 82;

    cities[6].name = "Miami";
    cities[6].temp = 97;

    cities[7].name = "New York";
    cities[7].temp = 85;

    cities[8].name = "Phoenix";
    cities[8].temp = 107;

    cities[9].name = "San Francisco";
    cities[9].temp = 66;

    sort_cities_selection();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", cities[i].name, cities[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order

// Bubble sort
void sort_cities_bubble(void)
{
    // Set swap counter to a non-zero value
    int swapCounter = -1;

    // Repeat until the swap counter is 0
    do
    {
        // Reset swap counter to 0
        swapCounter = 0;

        // Look at each adjacent pair
        for (int currentCity = 0; currentCity < NUM_CITIES - 1; currentCity++)
        {
            // if two adjacent elements are not in order, swap them and add one to the swap counter
            if (cities[currentCity].temp < cities[currentCity + 1].temp)
            {
                temporaryCityHolder[0] = cities[currentCity];
                cities[currentCity] = cities[currentCity + 1];
                cities[currentCity + 1] = temporaryCityHolder[0];
                swapCounter++;
            }
        }
    }
    while (swapCounter != 0);
}

// Selection sort
void sort_cities_selection(void)
{
    // Repeat until no unsorted elements remain
    for (int currentCity = 0; currentCity < NUM_CITIES - 1; currentCity++)
    {
        int maxTemperature = cities[currentCity].temp, maxTemperatureIndex;
        // Search the unsorted part of the data to find the smallest value
        for (int unsortedCity = currentCity; unsortedCity < NUM_CITIES; unsortedCity++)
        {
            if (cities[unsortedCity].temp > maxTemperature)
            {
                maxTemperature = cities[unsortedCity].temp;
                maxTemperatureIndex = unsortedCity;
            }
        }
        // Swap the smallest found value with the first element of the unsorted part
        if (maxTemperature != cities[currentCity].temp)
        {
            temporaryCityHolder[0] = cities[currentCity];
            cities[currentCity] = cities[maxTemperatureIndex];
            cities[maxTemperatureIndex] = temporaryCityHolder[0];
        }
    }
}

// Insertion sort
void sort_cities_insertion(void)
{
    int currentCity = 1;
    while (currentCity < NUM_CITIES)
    {
        // Store the current city in a temporary variable
        temporaryCityHolder = cities[currentCity];
        int previousCityIndex = currentCity - 1;

        // Shift elements of the sorted part to make room for the current city
        while (previousCityIndex >= 0 && cities[previousCityIndex].temp < temporaryCityHolder.temp)
        {
            cities[previousCityIndex + 1] = cities[previousCityIndex];
            previousCityIndex = previousCityIndex - 1;
        }

        // Place the current city in its correct position within the sorted part
        cities[previousCityIndex + 1] = temporaryCityHolder;

        currentCity = currentCity + 1;
    }
}
