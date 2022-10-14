#pragma once

#include "engine/Systems/Graphics/Components/Transform.h"
#include "soloud.h"
#include <stdexcept>
#include "engine/Scene.h"
#include "engine/Systems/Sound/Components/SpatialAudioSource.h"
#include "engine/Systems/Sound/Components/BackgroundAudioSource.h"
#include "engine/Systems/Sound/Components/AudioListener.h"
#include "engine/Systems/Physics/Components/Rigidbody.h"

namespace gl3::engine::soundSystem {
    /// Provides a static class to interact with @AudioSource to provide a more spatial sound and overall control.
    class AudioSystem {
        friend class AudioSourceUtils;

    public:
        /// Need to adhere to the singleton pattern
        static AudioSystem &GetAudioSystem();

        /// Sets up the audio system by initializing SoLoud.
        AudioSystem();

        /// Stops all sounds and deinitializes SoLoud.
        ~AudioSystem();

        void SetupAudio();

        void UpdateAudio();

        void DestroyAudio();

    private:
        inline static AudioSystem *audioSystem = nullptr;
        static inline SoLoud::Soloud soLoud {};
        static inline float masterVolume = 1.0f;
    };
}