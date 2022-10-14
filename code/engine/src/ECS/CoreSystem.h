#pragma once

namespace gl3::engine::Ecs {
    class CoreSystem {

    public:
        CoreSystem(CoreSystem &&) = delete;
        CoreSystem(const CoreSystem &) = delete;

    protected:
        CoreSystem() = default;
        virtual ~CoreSystem() = default;
    };
}