#pragma once

#include "engine/GraphicsEngine/Transform.h"
#include "soloud.h"

namespace Sound {

    class AudioListener {
    public:
        static AudioListener* GetAudioListener(Graphics::Transform* newTransform){
            __if_not_exists(listener) {
                listener = AudioListener();
            }
            AudioListener::transform = newTransform;
            return &listener;
        }

    private:
        AudioListener() = delete;

        static AudioListener listener;

        static Graphics::Transform* transform;
    };
}