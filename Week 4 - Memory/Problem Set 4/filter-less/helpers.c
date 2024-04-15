#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            RGBTRIPLE pixel = image[x][y];
            // Calculate the average pixel value.
            // I will use bankers rounding instead of round() from math.h
            int roundedAverage = (int) (((float) (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0) + 0.5);
            // Set each color value to the average value.
            image[x][y].rgbtRed = roundedAverage;
            image[x][y].rgbtGreen = roundedAverage;
            image[x][y].rgbtBlue = roundedAverage;
        }
    }
    return;
}
// Function to ensure that a value is an integer between 0 and 255, inclusive.
int clampToByteRange(int value)
{
    if (value > 255)
    {
        value = 255;
    }
    else if (value < 0)
    {
        value = 0;
    }
    return value;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            RGBTRIPLE pixel = image[x][y];
            // Calculate each new color value using the Sepia formula.
            int originalRed = pixel.rgbtRed, originalGreen = pixel.rgbtGreen, originalBlue = pixel.rgbtBlue;

            int sepiaRed = (int) (((float) (.393 * originalRed + .769 * originalGreen + .189 * originalBlue)) + 0.5);
            int sepiaGreen = (int) (((float) (.349 * originalRed + .686 * originalGreen + .168 * originalBlue)) + 0.5);
            int sepiaBlue = (int) (((float) (.272 * originalRed + .534 * originalGreen + .131 * originalBlue)) + 0.5);

            // Ensure that the result is an integer between 0 and 255, inclusive.
            sepiaRed = clampToByteRange(sepiaRed);
            sepiaGreen = clampToByteRange(sepiaGreen);
            sepiaBlue = clampToByteRange(sepiaBlue);

            // Set each color value to the sepia value.
            image[x][y].rgbtRed = sepiaRed;
            image[x][y].rgbtGreen = sepiaGreen;
            image[x][y].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary pixel RGB holder
    RGBTRIPLE temporaryHolder = {0x0000, 0x0000, 0x0000};

    // For each row
    for (int x = 0; x < height; x++)
    {
        // Swap pixel on horizontal opposite sides.
        for (int y = 0; y < width / 2; y++)
        {
            temporaryHolder = image[x][y];
            image[x][y] = image[x][width - y - 1];
            image[x][width - y - 1] = temporaryHolder;
        }
    }

    return;
}

// Function to apply a blur effect to the image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary image to store the blurred values
    RGBTRIPLE tempImage[height][width];

    // Define a 3x3 kernel for weighted average
    int kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    // Iterate over each pixel in the image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, weightSum = 0;

            // Iterate over the kernel
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newX = x + i;
                    int newY = y + j;

                    // Check if the neighboring pixel is within bounds
                    if (newX >= 0 && newX < height && newY >= 0 && newY < width)
                    {
                        int weight = kernel[i + 1][j + 1];
                        weightSum += weight;
                        sumRed += image[newX][newY].rgbtRed * weight;
                        sumGreen += image[newX][newY].rgbtGreen * weight;
                        sumBlue += image[newX][newY].rgbtBlue * weight;
                    }
                }
            }

            // Calculate the average values using banker's rounding
            tempImage[x][y].rgbtRed = clampToByteRange((int)(((float)sumRed / weightSum) + 0.5));
            tempImage[x][y].rgbtGreen = clampToByteRange((int)(((float)sumGreen / weightSum) + 0.5));
            tempImage[x][y].rgbtBlue = clampToByteRange((int)(((float)sumBlue / weightSum) + 0.5));
        }
    }

    // Copy the values from the temporary image back to the original image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = tempImage[x][y];
        }
    }

    return;
}
