#pragma once

#include "../../ECS/CoreSystem.h"
#include "glm/mat4x4.hpp"

#include "engine/Systems/Graphics/Components/Transform.h"
#include "engine/ECS/Registry.h"
#include "engine/Scene.h"

namespace gl3::engine::Graphics {

    class TransformSystem : Ecs::CoreSystem {
    public:
        static TransformSystem *GetTransformSystem();

        static void DestroyTransformSystem();

        void SetupTransform();

        void UpdateTransform(Scene* currentScene);

        void DestroyTransform();

    private:
        TransformSystem() = default;

        ~TransformSystem() override = default;

        void RecalculateMatrices(Transform &transform);

        static inline TransformSystem *transformSystem = nullptr;
    };
}
