#include "neuron/ecs_application/ecs_application.hpp"

namespace neuron::ecs_application {
    int version_major() {
        return NEURON_ECS_APP_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_ECS_APP_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_ECS_APP_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_ECS_APP_VERSION;
    }
}