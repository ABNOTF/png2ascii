#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <locale.h>

int check_if_png(char *file_name, FILE **fp);
void read_png(FILE *fp);
wchar_t get_char_for_brightness(int brightness,int iscolor);
void printfascii(int r, int g, int b, wchar_t c,int iscolor);
void fprintfascii(int r, int g, int b, wchar_t c,int iscolor,int iskind,FILE* output_file);
void generate_ascii_art(int scale_factor, int h, int w, unsigned char **row_pointers,int iscolor,int iskind,int pixel_size,FILE* output_file);