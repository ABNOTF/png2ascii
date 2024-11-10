#include <stdio.h>
#include <stdlib.h>
#include <png.h>

int check_if_png(char *file_name, FILE **fp);
void read_png(FILE *fp);
char get_char_for_brightness(int brightness);
void print_colored_char(int r, int g, int b, char c, FILE *output_file,int iscolor);
void generate_ascii_art(int scale_factor, int h, int w, unsigned char **row_pointers,FILE *output_file,int iscolor);