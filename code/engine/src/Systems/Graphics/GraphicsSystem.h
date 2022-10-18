#pragma once

#include <iostream>

#include "engine/Systems/FileManager/FileManager.h"

#include "engine/Systems/Graphics/Components/Model.h"
#include "engine/Systems/Graphics/Components/Camera.h"
#include "engine/Systems/Graphics/Components/Transform.h"

#include "engine/Systems/Graphics/Utils/SkyboxUtils.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"
#include "engine/Systems/Graphics/Utils/CameraUtils.h"

namespace gl3::engine::Graphics::Systems{

    class GraphicsSystem {
    public:
        /// Need to adhere to the singleton pattern
        static GraphicsSystem *GetGraphicsSystem();


        /// Need to adhere to the singleton pattern
        static void DestroyGraphicsSystem();

        void SetUp();

        void Update();

        void Shutdown();

    private:

        GraphicsSystem();

        ~GraphicsSystem();

        static void Draw(Components::Model &modelData);

        glm::vec3 lightPos = glm::vec3(0.0f, -0.5f, 1.0f);
    };
}