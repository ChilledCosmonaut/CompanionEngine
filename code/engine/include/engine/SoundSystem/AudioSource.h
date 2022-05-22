#pragma once

#include <string>
#include "soloud_wav.h"
#include "engine/GraphicsEngine/Transform.h"

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

    private:
        SoLoud::Wav sound;
        Graphics::Transform* sourceTransform;
    };
}