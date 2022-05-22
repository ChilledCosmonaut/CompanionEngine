#pragma once

#include "engine/GraphicsEngine/Transform.h"
#include "soloud.h"

namespace Sound {

    class AudioListener {
    public:
        static void StartAudioListener(Graphics::Transform* transform){
            audioTransform = transform;
            soLoud = SoLoud::Soloud();
            soLoud.init();
        }

        static void StopAudioListener(){
            soLoud.deinit();
        }

    private:

        static AudioListener listener;
        static SoLoud::Soloud soLoud;
        static Graphics::Transform* audioTransform;
    };
}