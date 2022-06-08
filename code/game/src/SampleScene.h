#pragma once

#include "engine/GraphicsEngine/Scene.h"

namespace gl3::game {

    class SampleScene : public engine::Graphics::Scene {
        void onSetup(){
            addSkybox();
        }
    };
}
