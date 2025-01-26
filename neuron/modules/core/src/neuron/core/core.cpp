#include "core.hpp"

namespace neuron {
    int version_major() {
        return NEURON_CORE_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_CORE_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_CORE_VERSION_PATCH;
    }

    const char *version_string() {
        return NEURON_CORE_VERSION;
    }
}