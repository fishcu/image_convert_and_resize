/* 
Read an input image, resize it to maximum dimensions, and save it as PNG.
Uses the STB image header libraries.
Compile with: 
$ gcc main.c -lm
Example usage:
$ ./a.out /path/to/lena.jpg /path/to/lena_conv.png 250 360
*/

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"

int main(int argc, char **argv) {
    /* Check input arguments */
    if (argc != 5) {
        printf("Usage: %s <input image file path> <output image file path> <max width> <max height>\n", argv[0]);
        return 1;
    }

    /* Parse input arguments */
    const char *input_file_path = argv[1];
    const char *output_file_path = argv[2];
    const int max_width = atoi(argv[3]);
    const int max_height = atoi(argv[4]);

    /* Load image */
    int width, height, channels;
    unsigned char *image_data = stbi_load(input_file_path, &width, &height, &channels, 0);
    if (!image_data) {
        printf("Error loading image: %s\n", stbi_failure_reason());
        return 1;
    }

    /* Resize image */
    int new_width, new_height;
    if (width > max_width && height > max_height) {
        /* Aspect ratio is wider */
        if (width * max_height > height * max_width) {
            new_width = max_width;
            new_height = height * max_width / width;
        } else { /* Aspect ratio is taller */
            new_width = width * max_height / height;
            new_height = max_height;
        }
    } else if (width > max_width) {
        new_width = max_width;
        new_height = height * max_width / width;
    } else if (height > max_height) {
        new_width = width * max_height / height;
        new_height = max_height;
    } else {
        new_width = width;
        new_height = height;
    }

    unsigned char *resized_data = malloc(new_width * new_height * channels);
    stbir_resize_uint8(image_data, width, height, 0, resized_data, new_width, new_height, 0, channels);

    /* Save image */
    if (!stbi_write_png(output_file_path, new_width, new_height, channels, resized_data, new_width * channels)) {
        printf("Error saving image: %s\n", stbi_failure_reason());
        return 1;
    }

    /* Free memory */
    stbi_image_free(image_data);
    free(resized_data);

    return 0;
}
