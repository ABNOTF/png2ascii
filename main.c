#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <fcntl.h>
#include <io.h>
#include <windows.h>

int ac;
int iskind = 0;
int iscolor = 0;
int scale_factor = 2;
FILE *fp = NULL;
int w = 0, h = 0;
int pixel_size = 3;
png_structp png_ptr = NULL;
png_infop info_ptr = NULL;
png_bytep *row_pointers = NULL;


FILE *output_file;

int main(int argc,char* argv[])
{
    if (argc < 1)
    {
        printf("Please enter valid parameters.");
        exit(0);
    }
    check_if_png(argv[1],&fp);
    read_png(fp);
    for (ac = 2; ac < argc && argv[ac][0] == '-'; ac++)
    {
        switch (argv[ac][1])
        {
        case 's':
            scale_factor = atoi(argv[ac+1]);
            ac++;
            break;

        case 'c':
            iscolor = 1;
            break;

        case 'h':
            iskind = 1;
            break;

        case 'p':
            pixel_size = atoi(argv[ac+1]);
            ac++;
            break;
        }
    }

    output_file = fopen(argv[ac],"wb");
    _setmode(_fileno(stdout), _O_U8TEXT);
    generate_ascii_art(scale_factor,h,w,row_pointers,iscolor,iskind,pixel_size,output_file);
}