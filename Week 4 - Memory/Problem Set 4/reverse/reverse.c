#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage ./reverse input.wav output.wav");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file for reading
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("The file isn't a valid WAV");
        return 3;
    }

    // Open output file for writing
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 4;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int blockSize = get_block_size(header);

    // Write reversed audio to file

    BYTE buffer[blockSize];
    // Move the file pointer to the end of the audio data
    fseek(inptr, 0, SEEK_END);

    // Calculate the total number of audio blocks in the file
    long totalBlocks = (ftell(inptr) - sizeof(WAVHEADER)) / blockSize;

    // Iterate through each audio block in reverse order
    while (totalBlocks > 0)
    {
        // Calculate the offset to the beginning of the current audio block
        long blockOffset = sizeof(WAVHEADER) + (totalBlocks - 1) * blockSize;

        // Move the file pointer to the beginning of the current audio block
        fseek(inptr, blockOffset, SEEK_SET);

        // Read the audio block into the array
        fread(buffer, sizeof(BYTE), blockSize, inptr);

        // Write the audio block to the output file
        fwrite(buffer, sizeof(BYTE), blockSize, outptr);

        // Move to the previous audio block for the next iteration
        totalBlocks--;
    }

    // Close files
    fclose(inptr);
    fclose(outptr);

    return 0;
}

int check_format(WAVHEADER header)
{
    // Compare file header format with WAV signature
    char *signature = "WAVE";
    for (int charIndex = 0; charIndex < 4; charIndex++)
    {
        if (header.format[charIndex] != signature[charIndex])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // Return an integer representing the block size of the wiven WAV file, in bytes.
    // We calculate the size of each block with the following calculation: number of channels multiplied by bytes per sample.
    return header.numChannels * (header.bitsPerSample / 8);
}
