#pragma once

#include <string>
#include "soloud_wav.h"
#include "engine/GraphicsEngine/Transform.h"
#include "AudioListener.h"

namespace Sound{
    /// Provides a wrapper for some simplified spatial audio.
    class AudioSource{
    public:

        /// Creates the AudioSource.
        /// @param soundPath Defines the filepath for the to be played sound.
        /// @param transform The global position of the audio source.
        explicit AudioSource(const std::string& soundPath, Graphics::Transform* transform){
            sound = SoLoud::Wav();
            sound.load(soundPath.c_str());
            sourceTransform = transform;
        }

        /// Starts to play the sound the is loaded via the constructor.
        /// @param looping Toggles the loop option for the sound.
        void Play(bool looping){
            sound.setLooping(looping);
            soundHandle = AudioListener::soLoud.play(sound, AudioListener::masterVolume);
        }

        /// Starts to play the sound in the background as e.g. Music etc.
        /// @param looping Toggles the loop option for the sound.
        void PlayBackground(bool looping){
            sound.setLooping(looping);
            soundHandle = AudioListener::soLoud.playBackground(sound, AudioListener::masterVolume);
        }

    private:
        SoLoud::Wav sound;
        int soundHandle;
        Graphics::Transform* sourceTransform;
    };
}