#pragma once

#include "neuron/core/compile_mode.hpp"

#include <cstdio>

namespace neuron::stbi {
    NEURON_CORE_API unsigned char *load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
    NEURON_CORE_API unsigned char *load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
    NEURON_CORE_API unsigned char *load_from_file(FILE *file, int *x, int *y, int *channels_in_file, int desired_channels);
    NEURON_CORE_API void           image_free(void *retval_from_stbi_load);
    NEURON_CORE_API void           set_flip_vertically_on_load(bool flag);
    NEURON_CORE_API void           set_flip_vertically_on_load_thread(bool flag);
} // namespace neuron::stbi
