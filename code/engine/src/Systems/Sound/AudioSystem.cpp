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

    void AudioSystem::UpdateAudio(Graphics::Scene &scene) {

        auto registry = scene.getRegistry();
        auto componentView = registry->view<Graphics::Components::Transform, AudioSource>();

        for(auto& entity : componentView){
            auto& transform = componentView.get<Graphics::Components::Transform>(entity);
            auto& audioSource = componentView.get<AudioSource>(entity);

            auto audioPosition = Graphics::Utils::TransformUtils::GetTranslation(transform);

            if (audioSource.play){
                audioSource.handle = AudioSystem::soLoud.play3d(audioSource.sound,
                                                                audioPosition.x, audioPosition.y, audioPosition.z);
                audioSource.play = false;
            }

            if (!audioSource.isBackground)
                break;

            soLoud.set3dSourcePosition(audioSource.handle,
                                       audioPosition.x, audioPosition.y, audioPosition.z);
        }

        soLoud.update3dAudio();
    }
}