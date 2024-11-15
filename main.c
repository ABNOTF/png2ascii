#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int iskind = 0;
char output_filename[256];
int iscolor = 0;
int scale_factor = 2;
FILE *fp = NULL;
int w = 0, h = 0;
char file_path[256] = {0};
//char *file_name = NULL;
png_structp png_ptr = NULL;
png_infop info_ptr = NULL;
png_bytep *row_pointers = NULL;
FILE *output_file;

int main(int argc,char **argv)
{
    if(argv[1]!=NULL)
    {
        strcpy(file_path,argv[1]);
            if(argv[2]!=NULL)
        {
            scale_factor = atoi(argv[2]);
        }
        if(argv[3]!=NULL)
        {
            iscolor = atoi(argv[3]);
        }
        if (check_if_png(file_path, &fp))
        {
            read_png(fp);
            generate_ascii_art(scale_factor,h,w,row_pointers,NULL,iscolor,0);
            if(argv[4]!=NULL)
            {
            if(argv[5]!=NULL)
            {
                iskind=atoi(argv[5]);
            }
                strcpy(output_filename, argv[4]);
                output_file = fopen(output_filename,"w+");
                generate_ascii_art(scale_factor,h,w,row_pointers,output_file,iscolor,iskind);
                fclose(output_file);
            }
        fclose(fp);
        return(0);
        }
    }
    printf("Enter PNG file path: ");
    scanf("%s", file_path);  // Read file path
    // Check if it's a PNG file
    if (check_if_png(file_path, &fp))
    {
        printf("This is a valid PNG file.\n");

        // Read the PNG file
        read_png(fp);

        printf("The height is: %d, The width is: %d\nThe rows is: %p\n", h, w,row_pointers);
		printf("%s", "Input scale factor:");
		
		scanf("%d", &scale_factor);
		
        printf("If U want to have color,please enter 1:");

        scanf("%d",&iscolor);
        getchar();
        
        printf("If U want to save as html,please enter 1:");

        scanf("%d",&iskind);
        getchar();
        
        printf("If U want to save as a file,please enter the file name:");
        fgets(output_filename,sizeof(output_filename), stdin);
        
        output_filename[strlen(output_filename) - 1] = '\0';
        if (strlen(output_filename)>0)
        {
            output_file = fopen(output_filename,"w+");
            generate_ascii_art(scale_factor,h,w,row_pointers,output_file,iscolor,iskind);
            fclose(output_file);
        }
        else
        {
        generate_ascii_art(scale_factor,h,w,row_pointers,NULL,iscolor,0);
        }
    }
    else
    {
        printf("Not a valid PNG file.\n");
    }

    fclose(fp);  // Close the file when done
    return 0;
}
