#pragma once

#include "engine/GraphicsEngine/Transform.h"
#include "soloud.h"

namespace Sound {
    /// Provides a static class to interact with @AudioSource to provide a more spatial sound and overall control.
    class AudioListener {
    public:
        /// Starts the audio listener by initializing SoLoud and setting the location of the listener.
        /// @param transform Global position of the AudioListener
        static void StartAudioListener(Graphics::Transform* transform){
            audioTransform = transform;
            soLoud = SoLoud::Soloud();
            soLoud.init();
        }

        /// Stops the AudioListener and deinitializes SoLoud.
        static void StopAudioListener(){
            soLoud.deinit();
        }

        /// Sets a maximum range for when audio sources can be heard.
        /// @param distance Maximum hearing range.
        static void SetMaxHearingDistance(int distance){
            hearingDistance = distance;
        }

    private:
        static AudioListener listener;
        static SoLoud::Soloud soLoud;
        static Graphics::Transform* audioTransform;
        static int hearingDistance;

    };
}