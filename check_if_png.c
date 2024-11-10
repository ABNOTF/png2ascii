#include <png.h>
#include "functions.h"
#define PNG_BYTES_TO_CHECK 4

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