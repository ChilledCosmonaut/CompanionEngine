#pragma once

#include "soloud_wav.h"
#include "generated/Assets.h"

namespace gl3::engine::soundSystem{
    /// Provides component info for background audio.
    struct BackgroundAudioSource{
    public:
        SoLoud::Wav sound {}; ///< Wav data of sound file
        assets::Sounds fileName; ///< Path to sound file
        int handle = -1; ///< Handle for sound library
        bool play = false; ///< Notifier for if sound should be played or not
        bool interrupt = false; ///< Notifier for if sound should be interrupted or not
        float volume = 1.0f; ///< Volume of the sound
    };
}
