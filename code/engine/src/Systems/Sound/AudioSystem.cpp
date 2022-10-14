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

    void AudioSystem::SetupAudio() {

        auto& registry = Ecs::Registry::getCurrent();

        auto backgroundSourcesForSetup = registry.view<BackgroundAudioSource, Ecs::Flags::Update<BackgroundAudioSource>>();

        for(auto& entity : backgroundSourcesForSetup){
            auto& audioSource = backgroundSourcesForSetup.get<BackgroundAudioSource>(entity);

            audioSource.sound = SoLoud::Wav();
            audioSource.sound.load(audioSource.soundFilePath.c_str());

            Ecs::Registry::RemoveSetupFlag<BackgroundAudioSource>(entity);
            Ecs::Registry::AddUpdateFlag<BackgroundAudioSource>(entity);
        }

        auto spatialSourcesForSetup = registry.view<SpatialAudioSource, Ecs::Flags::Update<SpatialAudioSource>>();

        for(auto& entity : spatialSourcesForSetup){
            auto& audioSource = spatialSourcesForSetup.get<SpatialAudioSource>(entity);

            audioSource.sound = SoLoud::Wav();
            audioSource.sound.load(audioSource.soundFilePath.c_str());

            Ecs::Registry::RemoveSetupFlag<SpatialAudioSource>(entity);
            Ecs::Registry::AddUpdateFlag<SpatialAudioSource>(entity);
        }
    }

    void AudioSystem::UpdateAudio() {

        auto& registry = Ecs::Registry::getCurrent();

        auto spatialSourcesChanged = registry.view<Graphics::Components::Transform, SpatialAudioSource, Ecs::Flags::Update<SpatialAudioSource>>();

        for(auto& entity : spatialSourcesChanged){
            auto& transform = spatialSourcesChanged.get<Graphics::Components::Transform>(entity);
            auto& audioSource = spatialSourcesChanged.get<SpatialAudioSource>(entity);

            /*audioSource.sound.setLooping(looping);*/
            soLoud.setVolume(audioSource.handle, audioSource.volume);
            soLoud.set3dSourceMinMaxDistance(audioSource.handle, audioSource.minDistance, audioSource.maxDistance);

            if(audioSource.play){
                auto audioPosition = Graphics::Utils::TransformUtils::GetTranslation(transform);

                audioSource.handle = AudioSystem::soLoud.play3d(audioSource.sound,
                                                                audioPosition.x, audioPosition.y, audioPosition.z);
                audioSource.play = false;
            }

            Ecs::Registry::RemoveUpdateFlag<SpatialAudioSource>(entity);
        }

        auto backgroundSourcesChanged = registry.view<Graphics::Components::Transform, BackgroundAudioSource, Ecs::Flags::Update<BackgroundAudioSource>>();

        for(auto& entity : backgroundSourcesChanged){
            auto& transform = backgroundSourcesChanged.get<Graphics::Components::Transform>(entity);
            auto& audioSource = backgroundSourcesChanged.get<BackgroundAudioSource>(entity);

            /*audioSource.sound.setLooping(looping);*/
            soLoud.setVolume(audioSource.handle, audioSource.volume);

            if(audioSource.play){
                audioSource.handle = AudioSystem::soLoud.playBackground(audioSource.sound/*, AudioListener::masterVolume * audioSource.volume*/);
                audioSource.play = false;
            }

            Ecs::Registry::RemoveUpdateFlag<BackgroundAudioSource>(entity);
        }

        auto spatialTransformChanged = registry.view<
                Graphics::Components::Transform, SpatialAudioSource, Ecs::Flags::Update<Graphics::Components::Transform>>();

        for(auto& entity : spatialTransformChanged){
            auto& transform = spatialTransformChanged.get<Graphics::Components::Transform>(entity);
            auto& audioSource = spatialTransformChanged.get<SpatialAudioSource>(entity);

            auto audioPosition = Graphics::Utils::TransformUtils::GetTranslation(transform);

            soLoud.set3dSourcePosition(audioSource.handle,
                                       audioPosition.x, audioPosition.y, audioPosition.z);

            if (registry.all_of<Physics::Components::RigidBody>(entity)){
                auto& rigidBody = registry.get<Physics::Components::RigidBody>(entity);
                auto velocity = rigidBody.rigidBody->getLinearVelocity();
                soLoud.set3dListenerVelocity(velocity.x, velocity.y, velocity.z);
            }

            soLoud.set3dSourceMinMaxDistance(audioSource.handle, audioSource.minDistance, audioSource.maxDistance);
        }

        auto listenerView = registry.view<Graphics::Components::Transform, AudioListener,  Ecs::Flags::Update<Graphics::Components::Transform>>();

        for (auto& entity : listenerView) {
            auto& transform = listenerView.get<Graphics::Components::Transform>(entity);

            auto listenerPosition = Graphics::Utils::TransformUtils::GetTranslation(transform);
            auto modelMatrix = Graphics::Utils::TransformUtils::GetModelMatrix(transform);

            glm::vec4 atVector = modelMatrix * glm::vec4(0., 0., -1., 0.);
            glm::vec4 upVector = modelMatrix * glm::vec4(0., 1., 0., 0.);

            soLoud.set3dListenerParameters(listenerPosition.x, listenerPosition.y, listenerPosition.z,
                                           atVector.x, atVector.y, atVector.z,
                                           upVector.x, upVector.y, upVector.z);

            if (registry.all_of<Physics::Components::RigidBody>(entity)){
                auto& rigidBody = registry.get<Physics::Components::RigidBody>(entity);
                auto velocity = rigidBody.rigidBody->getLinearVelocity();
                soLoud.set3dListenerVelocity(velocity.x, velocity.y, velocity.z);
            }
            break;
        }

        soLoud.update3dAudio();
    }

    void AudioSystem::DestroyAudio() {

        auto& registry = Ecs::Registry::getCurrent();

        auto spatialSourcesForDestruction = registry.view<SpatialAudioSource, Ecs::Flags::Destroy<SpatialAudioSource>>();

        for (auto entity:spatialSourcesForDestruction) {
            auto& audioSource = spatialSourcesForDestruction.get<SpatialAudioSource>(entity);

            soLoud.stop(audioSource.handle);

            registry.remove<SpatialAudioSource>(entity);
            Ecs::Registry::RemoveDestroyFlag<SpatialAudioSource>(entity);
        }

        auto backgroundSourcesForDestruction = registry.view<BackgroundAudioSource, Ecs::Flags::Destroy<BackgroundAudioSource>>();

        for (auto entity:backgroundSourcesForDestruction) {
            auto& audioSource = backgroundSourcesForDestruction.get<BackgroundAudioSource>(entity);

            soLoud.stop(audioSource.handle);

            registry.remove<BackgroundAudioSource>(entity);
            Ecs::Registry::RemoveDestroyFlag<BackgroundAudioSource>(entity);
        }

        auto listenersForDestruction = registry.view<AudioListener, Ecs::Flags::Destroy<AudioListener>>();

        for (auto entity:listenersForDestruction) {
            registry.remove<AudioListener>(entity);
            Ecs::Registry::RemoveDestroyFlag<AudioListener>(entity);
        }
    }
}