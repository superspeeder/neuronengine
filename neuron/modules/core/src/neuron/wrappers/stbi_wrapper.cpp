#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>

#include "neuron/wrappers/stbi_wrapper.hpp"

unsigned char *neuron::stbi::load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels) {
    return stbi_load_from_memory(buffer, len, x, y, channels_in_file, desired_channels);
}

unsigned char *neuron::stbi::load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels) {
    return stbi_load(filename, x, y, channels_in_file, desired_channels);
}

unsigned char *neuron::stbi::load_from_file(FILE *file, int *x, int *y, int *channels_in_file, int desired_channels) {
    return stbi_load_from_file(file, x, y, channels_in_file, desired_channels);
}

void neuron::stbi::image_free(void *retval_from_stbi_load) {
    stbi_image_free(retval_from_stbi_load);
}

void neuron::stbi::set_flip_vertically_on_load(bool flag) {
    stbi_set_flip_vertically_on_load(flag);
}

void neuron::stbi::set_flip_vertically_on_load_thread(bool flag) {
    stbi_set_flip_vertically_on_load_thread(flag);
}
