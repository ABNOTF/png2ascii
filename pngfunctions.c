#include <png.h>
#include "functions.h"
#define PNG_BYTES_TO_CHECK 4

extern png_structp png_ptr;
extern png_infop info_ptr;
extern png_bytep *row_pointers;
extern int w, h;

int check_if_png(char *file_name, FILE **fp)
{
    char buf[PNG_BYTES_TO_CHECK];
    /* Open the prospective PNG file. */
    if ((*fp = fopen(file_name, "rb")) == NULL) {
        perror("Error opening file");
        return 0;
    }
    /* Read in some of the signature bytes. */
    long bytes_read = fread(buf, 1, PNG_BYTES_TO_CHECK, *fp);
    if (bytes_read != PNG_BYTES_TO_CHECK) {
        fclose(*fp);
        printf("Error reading file: only %zu bytes read\n", bytes_read);
        return 0;
    }

    /* Output the read signature for debugging */
    printf("Read Signature: ");
    for (int i = 0; i < PNG_BYTES_TO_CHECK; i++) {
        printf("%02x ", (unsigned char)buf[i]);
    }
    printf("\n");

    /* Compare the first PNG_BYTES_TO_CHECK bytes of the signature.
     * Return true if they match.
     */
    if (png_sig_cmp((png_bytep)buf, 0, PNG_BYTES_TO_CHECK) != 0) {
        fclose(*fp);
        return 0;
    }

    return 1; // It's a PNG file
}

void read_png(FILE *fp)  /* File is already open */
{
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        fclose(fp);
        printf("Error: png_create_read_struct failed\n");
        return;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        printf("Error: png_create_info_struct failed\n");
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        printf("Error: libpng read error\n");
        return;
    }

    // Ensure the file pointer is at the beginning of the file before initializing png_io
    rewind(fp);

    // Initialize PNG IO
    png_init_io(png_ptr, fp);

    // Read PNG file
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, NULL);

    // Get image width and height
    w = png_get_image_width(png_ptr, info_ptr);
    h = png_get_image_height(png_ptr, info_ptr);
    row_pointers = png_get_rows(png_ptr,info_ptr);
}