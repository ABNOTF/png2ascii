#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "functions.h"
#include <wchar.h>

wchar_t get_char_for_brightness(int brightness,int iscolor)
{
    int gary;
    // const wchar_t charset[] = L"电棍操死你们的妈";
    const wchar_t charset[] = L"░▒▒▓▓███";
    switch (iscolor)
    {
    case 1:
        gary = (brightness * 7) / 255;    // 将亮度映射到字符集的索引
    default:
        gary = 7 - (brightness * 7) / 255;
    }
    return charset[gary];
}

void printfascii(int r, int g, int b, wchar_t c,int iscolor)
{
    switch (iscolor)
    {
    case 0:
        wprintf(L"%lc", c);
        break;

    case 1:
        wprintf(L"\033[38;2;%d;%d;%dm%lc\033[0m", r, g, b, c);  // 使用 24 位 RGB 颜色输出
        break;

    default:
        break;
    }
}

void fprintfascii(int r, int g, int b, wchar_t c,int iscolor,int iskind,FILE *output_file)
{
    if (output_file != NULL)
    {
        switch (iscolor)
        {
        case 0:
            switch (iskind)
            {
            case 1:
                fwprintf(output_file,L">%lc</p><p",c);
                break;

            case 0:
                fwprintf(output_file,L"%lc", c);
                break;
            }
            break;

        case 1:
            switch (iskind)
            {
            case 1:
                fwprintf(output_file,L"<span style=\"color:rgb(%d,%d,%d)\">%lc</span>",r,g,b,c);
            break;

            case 0:
                fwprintf(output_file,L"\033[38;2;%d;%d;%dm%lc\033[0m", r, g, b, c);  // 使用 24 位 RGB 颜色输出
            }
            break;
        }
    }
}


void generate_ascii_art(int scale_factor, int h, int w, unsigned char **row_pointers,int iscolor,int iskind,int pixel_size,FILE *output_file)
{
    if (output_file != NULL)
    {
        for (int y = 0; y < h; y++)
        {
            if (y % scale_factor != 0)
            {
                continue;
            }

            for (int x = 0; x < w; x++)
            {
                if (x % scale_factor != 0)
                {
                    continue;
                }

                png_byte *pixel = &row_pointers[y][x * pixel_size];
                int r = pixel[0];
                int g = pixel[1];
                int b = pixel[2];
                int brightness = (r + g + b) / 3;
                char c = get_char_for_brightness(brightness,iscolor);
                fprintfascii(r, g, b, c,iscolor,iskind,output_file);
                fprintf(output_file," ");
            }
            fprintf(output_file,"\n");
        }
        fclose(output_file);
    }
    else
    {
        for (int y = 0; y < h; y++)
        {
            if (y % scale_factor != 0)
            {
                continue;
            }

            for (int x = 0; x < w; x++)
            {
                if (x % scale_factor != 0)
                {
                    continue;
                }

                png_byte *pixel = &row_pointers[y][x * pixel_size];
                int r = pixel[0];
                int g = pixel[1];
                int b = pixel[2];
                int brightness = (r + g + b) / 3;
                wchar_t c = get_char_for_brightness(brightness,iscolor);
                printfascii(r, g, b, c,iscolor);
                wprintf(L" ");
            }
            wprintf(L"\n");
        }
    }
}
