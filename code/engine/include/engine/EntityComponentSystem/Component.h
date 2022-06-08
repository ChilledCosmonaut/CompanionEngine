#pragma once
#include "Entity.h"

namespace gl3::engine::entityComponentSystem {
    struct Component {

    public:
        //virtual ~Component() = default;

    protected:
        explicit Component(Entity& owner)
                : owner(owner) {};

        Entity& owner;
    };
}