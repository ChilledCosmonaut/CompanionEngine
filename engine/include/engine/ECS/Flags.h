#pragma once

namespace gl3::engine::Ecs::Flags {

    /**
     * A simple set up flag.
     * @tparam Component Specified component type
     */
    template <typename  Component>
    struct Setup {};

    /**
     * A simple update flag.
     * @tparam Component Specified component type
     */
    template <typename  Component>
    struct Update {};

    /**
     * A simple destroy flag.
     * @tparam Component Specified component type
     */
    template <typename  Component>
    struct Destroy {};

    /**
     * General purpose destroy flag for entity wide destruction.
     */
    struct DestroyEntity {};
}
