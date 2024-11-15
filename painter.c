#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "functions.h"

void generate_ascii_art(int scale_factor, int h, int w, unsigned char **row_pointers,FILE *output_file,int iscolor,int iskind)
{
    if (iskind == 1 && iscolor == 1)
    {
        fprintf(output_file,"<span ");
    }
    if (iskind == 1 && iscolor !=1)
    {
        fprintf(output_file,"<p ");
    }
    for (int y = 0; y < h; y++)
    {  // Loop through rows (height)
        if (y % scale_factor != 0)
        {
            continue;  // Skip rows that don't match the scale factor
        }

        for (int x = 0; x < w; x++)
        {  // Loop through columns (width)
            if (x % scale_factor != 0)
            {
                continue;  // Skip columns that don't match the scale factor
            }

            png_byte *pixel = &row_pointers[y][x * 3];  // Get the RGB values for each pixel
            int r = pixel[0];
            int g = pixel[1];
            int b = pixel[2];
            int brightness = (r + g + b) / 3;
            char c = get_char_for_brightness(brightness);
            print_colored_char(r, g, b, c,output_file,iscolor,iskind);
            printf(" ");
            if (output_file != NULL)
            {
                fprintf(output_file," ");
            }
        }
        if (output_file != NULL)
        {
            fprintf(output_file, "\n");
        }
        printf("\n");  // Print a new line after each row
    }
    if (iskind == 1)
    {
        fprintf(output_file,">");
    }
}
