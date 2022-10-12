#include "engine/Systems/Sound/AudioSystem.h"

namespace gl3::engine::soundSystem {

    AudioSystem &AudioSystem::GetAudioSystem() {
        if (audioSystem != nullptr)
            return *audioSystem;
        throw std::domain_error("AudioSystem is not yet created");
    }

    AudioSystem::AudioSystem() {
        soLoud = SoLoud::Soloud();
        soLoud.init();
    }

    AudioSystem::~AudioSystem() {
        soLoud.stopAll();
        soLoud.deinit();
    }
}