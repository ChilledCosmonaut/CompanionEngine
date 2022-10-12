#pragma once

#include "engine/Systems/Graphics/Components/Transform.h"
#include "soloud.h"

namespace gl3::engine::soundSystem {
    /// Provides a static class to interact with @AudioSource to provide a more spatial sound and overall control.
    class AudioSystem {
        friend class AudioSource;
        friend class AudioSourceUtils;

    public:
        /// Sets up the audio system by initializing SoLoud.
        AudioSystem(){
            soLoud = SoLoud::Soloud();
            soLoud.init();
        }

        /// Stops all sounds and deinitializes SoLoud.
        ~AudioSystem(){
            soLoud.stopAll();
            soLoud.deinit();
        }
/*
        /// Sets a maximum range for when audio sources can be heard. (Does currently nothing)
        /// @param distance Maximum hearing range.
        static void SetMaxHearingDistance(int distance){
            hearingDistance = distance;
        }

        /// Sets the master volume for all audio sources in the program. (Does currently nothing)
        /// @param volume New master volume value.
        static void SetMasterVolume(float volume){
            masterVolume = volume;
        }*/

    private:
        static inline SoLoud::Soloud soLoud {};
        /*static inline Graphics::Components::Transform* audioTransform = nullptr;
        static inline int hearingDistance = 100;*/
        static inline float masterVolume = 1.0f;
    };
}