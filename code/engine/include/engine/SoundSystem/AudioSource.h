#pragma once

#include <string>
#include "soloud_wav.h"
#include "engine/GraphicsEngine/Components/Transform.h"
#include "AudioListener.h"

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