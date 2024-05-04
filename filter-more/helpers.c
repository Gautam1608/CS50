#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Convert  image  to  grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE greyscale = (BYTE) round((float) (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtBlue = greyscale;
            image[i][j].rgbtRed = greyscale;
            image[i][j].rgbtGreen = greyscale;
        }
    }
    return;
}

//  Reflect  image  horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

//  Blur  image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];

    for (int row = 0; row < height; row++)

    {

        for (int cols = 0; cols < width; cols++)

        {

            copy_image[row][cols] = image[row][cols];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int cols = 0; cols < width; cols++)
        {
            int red = 0, green = 0, blue = 0;
            float count = 0.00;
            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = cols - 1; j <= cols + 1; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        red += copy_image[i][j].rgbtRed;
                        green += copy_image[i][j].rgbtGreen;
                        blue += copy_image[i][j].rgbtBlue;
                        count++;
                    }
                }
            }
            image[row][cols].rgbtRed = round(red / count);
            image[row][cols].rgbtGreen = round(green / count);
            image[row][cols].rgbtBlue = round(blue / count);
        }
    }
    return;
}

//  Detect  edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];

    for (int row = 0; row < height; row++)

    {

        for (int cols = 0; cols < width; cols++)

        {

            copy_image[row][cols] = image[row][cols];
        }
    }
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE *previousRow = malloc(width * sizeof(RGBTRIPLE));
    RGBTRIPLE *currentRow = malloc(width * sizeof(RGBTRIPLE));
    RGBTRIPLE previousCell;
    RGBTRIPLE currentCell;
    for (int i = 0; i < height; i++)
    {
        memcpy(currentRow, image[i], width * sizeof(RGBTRIPLE));
        for (int j = 0; j < width; j++)
        {
            int rgbx[3] = {0};
            int rgby[3] = {0};
            currentCell = image[i][j];
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (!(i + k < 0) && !(i + k > height - 1) && !(j + l < 0) && !(j + l > width - 1))
                    {
                        if (k == -1)
                        {
                            rgbx[0] += Gx[k + 1][l + 1] * previousRow[j + l].rgbtRed;
                            rgbx[1] += Gx[k + 1][l + 1] * previousRow[j + l].rgbtGreen;
                            rgbx[2] += Gx[k + 1][l + 1] * previousRow[j + l].rgbtBlue;
                            rgby[0] += Gy[k + 1][l + 1] * previousRow[j + l].rgbtRed;
                            rgby[1] += Gy[k + 1][l + 1] * previousRow[j + l].rgbtGreen;
                            rgby[2] += Gy[k + 1][l + 1] * previousRow[j + l].rgbtBlue;
                        }
                        else if (k == 0 && l == -1)
                        {
                            rgbx[0] += Gx[k + 1][l + 1] * previousCell.rgbtRed;
                            rgbx[1] += Gx[k + 1][l + 1] * previousCell.rgbtGreen;
                            rgbx[2] += Gx[k + 1][l + 1] * previousCell.rgbtBlue;
                            rgby[0] += Gy[k + 1][l + 1] * previousCell.rgbtRed;
                            rgby[1] += Gy[k + 1][l + 1] * previousCell.rgbtGreen;
                            rgby[2] += Gy[k + 1][l + 1] * previousCell.rgbtBlue;
                        }
                        else
                        {
                            rgbx[0] += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                            rgbx[1] += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                            rgbx[2] += Gx[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                            rgby[0] += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                            rgby[1] += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                            rgby[2] += Gy[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                        }
                    }
                }
            }
            int red = round(sqrt(rgbx[0] * rgbx[0] + rgby[0] * rgby[0]));
            int green = round(sqrt(rgbx[1] * rgbx[1] + rgby[1] * rgby[1]));
            int blue = round(sqrt(rgbx[2] * rgbx[2] + rgby[2] * rgby[2]));
            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
            previousCell = currentCell;
        }
        memcpy(previousRow, currentRow, width * sizeof(RGBTRIPLE));
    }
    free(previousRow);
    free(currentRow);
    return;
}
