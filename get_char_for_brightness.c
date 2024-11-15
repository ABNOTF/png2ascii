#include <png.h>
#include "functions.h"

int gary;

char get_char_for_brightness(int brightness)
{
    const char *charset = " .:-=+*#%@";  // 字符集
    int gary = 9 - (brightness * 9 / 255);     // 将亮度映射到字符集的索引
    return charset[gary];
}
// 输出 32 位色（RGB）格式的字符
void print_colored_char(int r, int g, int b, char c, FILE *output_file,int iscolor,int iskind)
{
    // 输出到终端
    if (iscolor != 0)
    {
        printf("\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, c);  // 使用 24 位 RGB 颜色输出
    }
    else
    {
        printf("%c", c);
    }
    // 如果 output_file 不为 NULL，输出到文件
    if (output_file != NULL)
    {
        if(iscolor == 1)
        {
            if (iskind == 1)
            {
                fprintf(output_file,"style=\"color:rgb(%d,%d,%d)\">%c</span><span", r, g, b, c);
            }
            else
            {
                fprintf(output_file, "\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, c);
            }
        }
        else
        {
            fprintf(output_file, "%c", c);
            if (iskind == 1)
            {
                fprintf(output_file,"p>%c</p><",c);
            }
        }
    }
}
