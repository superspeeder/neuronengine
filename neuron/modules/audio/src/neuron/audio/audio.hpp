#pragma once
#include "neuron/audio/compile_mode.hpp"

namespace neuron::audio {
    NEURON_AUDIO_API int version_major();
    NEURON_AUDIO_API int version_minor();
    NEURON_AUDIO_API int version_patch();
    NEURON_AUDIO_API const char* version_str();
}
