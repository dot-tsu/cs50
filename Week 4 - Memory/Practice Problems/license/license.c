#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char *buffer = malloc(7); // In the heap so I can use strcpy on it
    if (buffer == NULL)
    {
        printf("Not enough memory available.");
        return 2;
    }

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("No such file found.");
        return 3;
    }

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Allocate memory for each plate number
        plates[idx] = malloc(8);
        if (plates[idx] == NULL)
        {
            printf("Not enough memory available for plate %d.", idx);
            return 4;
        }

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }

    // Print plates
    for (int i = 0; i < idx; i++)
    {
        printf("%s\n", plates[i]);
        // Free allocated memory for each plate number
        free(plates[i]);
    }

    // Free buffer
    free(buffer);

    // Close the file
    fclose(infile);

    return 0;
}
