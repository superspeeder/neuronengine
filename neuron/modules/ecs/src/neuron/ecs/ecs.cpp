#include "neuron/ecs/ecs.hpp"

namespace neuron::ecs {
    int version_major() {
        return NEURON_ECS_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_ECS_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_ECS_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_ECS_VERSION;
    }
}