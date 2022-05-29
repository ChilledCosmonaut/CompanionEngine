#pragma once
#include "Entity.h"
#include "engine/GraphicsEngine/Scene.h"

namespace gl3::engine::entityComponentSystem {
    class Component {
        friend class Graphics::Scene;

    public:
        virtual ~Component() = default;

    protected:
        explicit Component(Entity& owner)
                : owner(owner) {};

        Entity& owner;
    };
}