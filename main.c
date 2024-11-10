#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

FILE *fp = NULL;
int w = 0, h = 0;
char file_path[256] = {0};
char *file_name = NULL;
png_structp png_ptr = NULL;
png_infop info_ptr = NULL;
png_bytep *row_pointers = NULL;
FILE *output_file;

int main()
{
    printf("Enter PNG file path: ");
    scanf("%s", file_path);  // Read file path
    // Check if it's a PNG file
    if (check_if_png(file_path, &fp))
    {
        printf("This is a valid PNG file.\n");

        // Read the PNG file
        read_png(fp);

        printf("The height is: %d, The width is: %d\nThe rows is: %o\n", h, w,row_pointers);
		printf("%s", "Input scale factor:");
        int scale_factor = 2;
		scanf("%d", &scale_factor);
        printf("If U want to have color,please enter 1:");
        int iscolor = 0;
        scanf("%d",&iscolor);
        getchar();
        printf("If U want to save as a file,please enter the file name:");
        char output_filename[256];
        fgets(output_filename,sizeof(output_filename), stdin);
        output_filename[strlen(output_filename) - 1] = '\0';
        if (strlen(output_filename)>=0)
        {
            output_file = fopen(output_filename,"w+");
            generate_ascii_art(scale_factor,h,w,row_pointers,output_file,iscolor);
            fclose(output_file);
        }
    }
    else
    {
        printf("Not a valid PNG file.\n");
    }

    fclose(fp);  // Close the file when done
    return 0;
}
