#pragma once

#include "soloud_wav.h"

namespace gl3::engine::soundSystem {
    /// Provides a wrapper for some simplified spatial audio.
    struct SpatialAudioSource{
    public:
        SoLoud::Wav sound {}; ///< Wav data of sound file
        std::string soundFilePath; ///< Path to sound file ToDo: Let this be manageable via FileManager
        int handle = -1; ///< Handle for sound library
        bool play = false; ///< Notifier for if sound should be played or not
        bool interrupt = false; ///< Notifier for if sound should be interrupted or not
        float volume = 1.0f; ///< Volume of the sound
        float minDistance = 0.1f; ///< Minimum distance required to hear the sound (Default is equal to clipping plane)
        float maxDistance = 1000.0f; ///< Maximum distance possible to hear the sound (Default is equal to clipping plane)
    };
}