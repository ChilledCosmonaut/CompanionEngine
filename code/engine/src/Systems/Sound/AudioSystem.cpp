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

        auto startView = registry->view<Graphics::Components::Transform, AudioSource, Update<AudioSource>>();

        for(auto& entity : startView){
            auto& transform = startView.get<Graphics::Components::Transform>(entity);
            auto& audioSource = startView.get<AudioSource>(entity);
            registry->remove<Update<AudioSource>>(entity);

            auto audioPosition = Graphics::Utils::TransformUtils::GetTranslation(transform);

            audioSource.handle = AudioSystem::soLoud.play3d(audioSource.sound,
                                                           audioPosition.x, audioPosition.y, audioPosition.z);
        }

        auto listenerView = registry->view<Graphics::Components::Transform, AudioListener>();

        for (auto& entity : listenerView) {
            auto& transform = listenerView.get<Graphics::Components::Transform>(entity);

            auto listenerPosition = Graphics::Utils::TransformUtils::GetTranslation(transform);
            auto modelMatrix = Graphics::Utils::TransformUtils::GetModelMatrix(transform);

            glm::vec4 atVector = modelMatrix * glm::vec4(0., 0., -1., 0.);
            glm::vec4 upVector = modelMatrix * glm::vec4(0., 1., 0., 0.);

            soLoud.set3dListenerParameters(listenerPosition.x, listenerPosition.y, listenerPosition.z,
                                           atVector.x, atVector.y, atVector.z,
                                           upVector.x, upVector.y, upVector.z);

            if (registry->all_of<Physics::Components::RigidBody>(entity)){
                auto& rigidBody = registry->get<Physics::Components::RigidBody>(entity);
                auto velocity = rigidBody.rigidBody->getLinearVelocity();
                soLoud.set3dListenerVelocity(velocity.x, velocity.y, velocity.z);
            }
            break;
        }

        auto componentView = registry->view<Graphics::Components::Transform, AudioSource>();

        for(auto& entity : componentView){
            auto& transform = componentView.get<Graphics::Components::Transform>(entity);
            auto& audioSource = componentView.get<AudioSource>(entity);

            auto audioPosition = Graphics::Utils::TransformUtils::GetTranslation(transform);

            if (!audioSource.isBackground)
                break;

            soLoud.set3dSourcePosition(audioSource.handle,
                                       audioPosition.x, audioPosition.y, audioPosition.z);

            if (registry->all_of<Physics::Components::RigidBody>(entity)){
                auto& rigidBody = registry->get<Physics::Components::RigidBody>(entity);
                auto velocity = rigidBody.rigidBody->getLinearVelocity();
                soLoud.set3dListenerVelocity(velocity.x, velocity.y, velocity.z);
            }
        }

        soLoud.update3dAudio();
    }
}