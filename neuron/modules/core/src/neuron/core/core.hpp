#pragma once
#include "neuron/core/compile_mode.hpp"

namespace neuron {
    NEURON_CORE_API int version_major();
    NEURON_CORE_API int version_minor();
    NEURON_CORE_API int version_patch();
    NEURON_CORE_API const char* version_str();
}