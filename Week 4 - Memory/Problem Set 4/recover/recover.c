#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
bool checkHeader(BYTE buffer[]);
int BlockSize = 512;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open memory card file
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    int jpegNumber = 0;
    char filename[8];
    FILE *outptr = NULL;

    // Repeat until the end of the card:
    BYTE buffer[BlockSize];
    while (fread(buffer, 1, BlockSize, inptr) == BlockSize)
    {
        // If start of a new JPEG
        if (checkHeader(buffer))
        {
            // Close the previous file before opening a new one
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Open a new file
            sprintf(filename, "%03i.jpg", jpegNumber);
            jpegNumber++;

            outptr = fopen(filename, "wb");

            if (outptr == NULL)
            {
                printf("Could not open file");
                fclose(inptr);
                return 3;
            }

            // Start writing to the new file
            fwrite(buffer, 1, BlockSize, outptr);
        }
        // If already found JPEG, keep writing to the current file
        else if (jpegNumber > 0)
        {
            fwrite(buffer, 1, BlockSize, outptr);
        }
    }

    // Close any remaining files
    fclose(inptr);

    // Close the last JPEG file if it was open
    if (outptr != NULL)
    {
        fclose(outptr);
    }

    return 0;
}

bool checkHeader(BYTE buffer[])
{
    // Compare first 3 bytes with JPEG signature
    BYTE signature[] = {0xff, 0xd8, 0xff};
    for (int byteIndex = 0; byteIndex < 3; byteIndex++)
    {
        if (buffer[byteIndex] != signature[byteIndex])
        {
            return false;
        }
    }
    // Check last byte using bitwise arithmetic
    if ((buffer[3] & 0xf0) != 0xe0)
    {
        return false;
    }

    return true;
}
