#include "neuron/os/os.hpp"

namespace neuron::os {
    int version_major() {
        return NEURON_OS_VERSION_MAJOR;
    }

    int version_minor() {
        return NEURON_OS_VERSION_MINOR;
    }

    int version_patch() {
        return NEURON_OS_VERSION_PATCH;
    }

    const char *version_str() {
        return NEURON_OS_VERSION;
    }
}
