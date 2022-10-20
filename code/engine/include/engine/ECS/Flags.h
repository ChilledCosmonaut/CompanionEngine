#pragma once

namespace gl3::engine::Ecs::Flags {

    template <typename  Component>
    struct Setup {};

    template <typename  Component>
    struct Update {};

    template <typename  Component>
    struct Destroy {};
}
