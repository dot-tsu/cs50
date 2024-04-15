#include "helpers.h"
#include <stdio.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Set colors in HEX
    RGBTRIPLE black = {0x00, 0x00, 0x00};
    RGBTRIPLE customColor = {0xff, 0xff, 0x00}; // For some reason its BGR not RGB.

    // Change all black pixels to a color of your choosing
    for (int heightIndex = 0; heightIndex < height; heightIndex++)
    {
        for (int widthIndex = 0; widthIndex < width; widthIndex++)
        {
            // If the pixel color is black, change it to the custom color
            if (image[heightIndex][widthIndex].rgbtRed == black.rgbtRed &&
                image[heightIndex][widthIndex].rgbtGreen == black.rgbtGreen &&
                image[heightIndex][widthIndex].rgbtBlue == black.rgbtBlue)
            {
                image[heightIndex][widthIndex] = customColor;
            }
        }
    }
}
