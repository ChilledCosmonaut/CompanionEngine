#pragma once

#include "../../ECS/CoreSystem.h"

namespace gl3::engine::Graphics {

    class TransformSystem : Ecs::CoreSystem {
    public:
        static TransformSystem *GetTransformSystem();

        static void DestroyTransformSystem();

        void SetupTransform();

        void UpdateTransform();

        void DestroyTransform();

    private:
        TransformSystem();

        ~TransformSystem() override;
    };
}
