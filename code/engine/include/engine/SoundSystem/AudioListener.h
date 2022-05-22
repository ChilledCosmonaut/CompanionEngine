#pragma once

#include "engine/GraphicsEngine/Transform.h"
#include "soloud.h"
#include "AudioSource.h"

namespace Sound {
    /// Provides a static class to interact with @AudioSource to provide a more spatial sound and overall control.
    class AudioListener {
        friend class AudioSource;

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

        /// Sets the master volume for all audio sources in the program.
        /// @param volume New master volume value.
        static void SetMasterVolume(float volume){
            masterVolume = volume;
        }

    private:
        static AudioListener listener;
        static SoLoud::Soloud soLoud;
        static Graphics::Transform* audioTransform;
        static int hearingDistance;
        static float masterVolume;
    };
}