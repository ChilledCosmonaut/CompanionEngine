#pragma once

namespace gl3::engine::inputSystem {

    template<typename translatedInput>
    class InputGroup {
    public:
        virtual void UpdateKeys();

        virtual translatedInput GetValue();
    };
}