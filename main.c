/* imas: image to ascii converter */
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define MAX_WIDTH 40
#include "stb_image.h"


const char ascii_chars[] = "@%#*+=-;:.";

void convertToAscii(unsigned char* image_data, int width, int height, int channels) {
  printf("\n");
  int i, j, k;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      int pixel_offset = (i * width + j) * channels;
      int intensity = 0;
      for (k = 0; k < channels; k++) {
          intensity += image_data[pixel_offset + k];
      }
      intensity /= channels;

      int char_index = intensity * (sizeof(ascii_chars) - 1) / 255;
      char ascii_char = ascii_chars[char_index];

      printf("%c", ascii_char);
    }
    printf("\n");
  }
}

unsigned char* resizeImage(unsigned char* image_data, int width, int height, int channels, float ratio) {
  int new_width = (int)(width * ratio);
  int new_height = (int)(height * ratio);
  int new_channels = channels;

  unsigned char* resized_data = (unsigned char*)malloc(new_width * new_height * new_channels);

  int i, j, k;
  for (i = 0; i < new_height; i++) {
    for (j = 0; j < new_width; j++) {
      int orig_i = (int)(i / ratio);
      int orig_j = (int)(j / ratio);

      for (k = 0; k < channels; k++) {
          resized_data[(i * new_width + j) * new_channels + k] = image_data[(orig_i * width + orig_j) * channels + k];
      }
    }
  }

  return resized_data;
}

int main(int argc, char **argv) {

  if (argc != 2) { 
    printf("use: imas [options] <source> \n");
    return 1;
  }
  int width, height, channels;
  unsigned char* image_data = stbi_load(argv[1], &width, &height, &channels, 0);
  if (image_data == NULL) {
      printf("Error: loading the image\n");
      return 1;
  }
  float resize_ratio = MAX_WIDTH / (float) width; 

  unsigned char* resized_image_data = resizeImage(image_data, width, height, channels, resize_ratio);
  convertToAscii(resized_image_data, width * resize_ratio, height * resize_ratio, channels);

  stbi_image_free(image_data);
  free(resized_image_data);

  return 0;
}
