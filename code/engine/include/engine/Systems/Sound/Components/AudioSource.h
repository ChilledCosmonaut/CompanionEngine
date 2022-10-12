#pragma once

#include "soloud_wav.h"

namespace gl3::engine::soundSystem {
    /// Provides a wrapper for some simplified spatial audio.
    struct AudioSource{
        friend class AudioSourceUtils;
        friend class AudioSystem;
    private:
        SoLoud::Wav sound {};
        int handle = -1;
        float volume = 1.0f;
        bool isBackground = false;
        bool play = false;
    };

    template <typename Component>
    struct Update{};

    template <typename Component>
    struct Start{};

    template <typename Component>
    struct Destroy{};
}