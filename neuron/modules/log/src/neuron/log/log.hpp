#pragma once

#include "neuron/log/compile_mode.hpp"

namespace neuron::log {
    NEURON_LOG_API int version_major();
    NEURON_LOG_API int version_minor();
    NEURON_LOG_API int version_patch();
    NEURON_LOG_API const char* version_str();

    NEURON_LOG_API void setup_default_logger();
}