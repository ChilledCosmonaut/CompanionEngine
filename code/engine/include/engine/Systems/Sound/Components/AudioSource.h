#pragma once

#include "soloud_wav.h"

namespace gl3::engine::soundSystem {
    /// Provides a wrapper for some simplified spatial audio.
    struct AudioSource{
        friend class AudioSourceUtils;
        friend class AudioSystem;
    private:
        SoLoud::Wav sound {}; ///< Wav data of sound file
        int handle = -1; ///< Handle for sound library
        float volume = 1.0f; ///< Volume of the sound
        bool isBackground = false; ///< Ignores position when playing the audio
        float minDistance = 0.1f; ///< Minimum distance required to hear the sound (Default is equal to clipping plane)
        float maxDistance = 1000.0f; ///< Maximum distance possible to hear the sound (Default is equal to clipping plane)
    };
}