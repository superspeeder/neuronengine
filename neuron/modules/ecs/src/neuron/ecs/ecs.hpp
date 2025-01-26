#pragma once
#include "neuron/ecs/compile_mode.hpp"

namespace neuron::ecs {
    NEURON_ECS_API int version_major();
    NEURON_ECS_API int version_minor();
    NEURON_ECS_API int version_patch();
    NEURON_ECS_API const char* version_str();
}
