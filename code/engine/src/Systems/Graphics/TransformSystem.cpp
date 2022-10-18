#include "TransformSystem.h"

namespace gl3::engine::Graphics {

    TransformSystem *TransformSystem::GetTransformSystem() {
        if (transformSystem == nullptr)
            transformSystem = new TransformSystem();
        return transformSystem;
    }

    void TransformSystem::DestroyTransformSystem() {
        transformSystem->~TransformSystem();
        transformSystem = nullptr;
    }
}