#pragma once

#include <string>
#include "soloud_wav.h"

namespace gl3::engine::soundSystem {
    /// Provides a wrapper for some simplified spatial audio.
    class AudioSource{
        friend class AudioSourceUtils;
    private:
        SoLoud::Wav sound;
        int soundHandle = -1;
        float volume = 1.0f;
    };
}