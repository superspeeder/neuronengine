#pragma once

#include "neuron/os/compile_mode.hpp"

namespace neuron::os {
    NEURON_OS_API int version_major();
    NEURON_OS_API int version_minor();
    NEURON_OS_API int version_patch();
    NEURON_OS_API const char* version_str();
}