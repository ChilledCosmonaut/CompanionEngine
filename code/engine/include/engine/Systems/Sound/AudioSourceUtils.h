#pragma once

#include "AudioSource.h"

namespace gl3::engine::soundSystem {

    class AudioSourceUtils {
    public:
        /// Creates the AudioSource.
        /// @param soundPath Defines the filepath for the to be played sound.
        /// @param transform The global position of the audio source.
        static void SetupAudioSource(AudioSource &audioSource, const std::string& soundPath){
            audioSource.sound = SoLoud::Wav();
            audioSource.sound.load(soundPath.c_str());
        }

        /// Starts to play the sound the is loaded via the constructor.
        /// @param looping Toggles the loop option for the sound.
        static void Play(AudioSource &audioSource, bool looping){
            audioSource.sound.setLooping(looping);
            audioSource.soundHandle = AudioSystem::soLoud.play(audioSource.sound, AudioSystem::masterVolume * audioSource.volume);
        }

        /// Starts to play the sound in the background as e.g. Music etc.
        /// @param looping Toggles the loop option for the sound.
        static void PlayBackground(AudioSource &audioSource, bool looping){
            audioSource.sound.setLooping(looping);
            audioSource.soundHandle = AudioSystem::soLoud.playBackground(audioSource.sound/*, AudioListener::masterVolume * audioSource.volume*/);
        }

        /// Stops the sound if currently played.
        static void Stop(AudioSource &audioSource) {
            if(audioSource.soundHandle == -1) return;
            AudioSystem::soLoud.stop(audioSource.soundHandle);
        }
    };
}