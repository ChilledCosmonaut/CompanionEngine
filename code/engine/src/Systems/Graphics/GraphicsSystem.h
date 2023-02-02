#pragma once

#include <iostream>

#include "../FileManager/ModelLoader.h"
#include "../FileManager/TextureLoader.h"
#include "../FileManager/FontLoader.h"

#include "engine/Systems/FileManager/FileManager.h"
#include "engine/Systems/Graphics/Components/Model.h"
#include "engine/Systems/Graphics/Components/Camera.h"
#include "engine/Systems/Graphics/Components/Transform.h"
#include "engine/Systems/Graphics/Components/Skybox.h"
#include "engine/Systems/Graphics/Components/Text.h"
#include "engine/Systems/Graphics/Components/UI.h"
#include "engine/Systems/Graphics/Utils/ModelUtils.h"

#include "LightingSystem.h"

namespace gl3::engine::Graphics {

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

        static void Draw(Model &model);

        glm::vec3 lightPos = glm::vec3(0.0f, -0.5f, 1.0f);

        filesystem::FileManager *fileManager;

        inline static GraphicsSystem *graphicsSystem = nullptr;
    };
}