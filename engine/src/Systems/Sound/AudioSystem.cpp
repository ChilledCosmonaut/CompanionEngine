#include "AudioSystem.h"

namespace gl3::engine::soundSystem {

    AudioSystem *AudioSystem::GetAudioSystem() {
        if (audioSystem == nullptr)
            audioSystem = new AudioSystem();
        return audioSystem;
    }

    void AudioSystem::DestroyAudioSystem() {
        audioSystem->~AudioSystem();
        audioSystem = nullptr;
    }

    AudioSystem::AudioSystem() {
        soLoud = SoLoud::Soloud();
        soLoud.init();
        fileManager = filesystem::FileManager::GetFileManager();
    }

    AudioSystem::~AudioSystem() {
        soLoud.stopAll();
        soLoud.deinit();
    }

    void AudioSystem::SetupAudio() {

        auto& registry = Ecs::Registry::getCurrent();

        auto backgroundSourcesForSetup = registry.view<BackgroundAudioSource, Ecs::Flags::Setup<BackgroundAudioSource>>();

        for(auto& entity : backgroundSourcesForSetup){
            auto& audioSource = backgroundSourcesForSetup.get<BackgroundAudioSource>(entity);

            audioSource.sound = *fileManager->getAsset(audioSource.fileName);

            Ecs::Registry::RemoveSetupFlag<BackgroundAudioSource>(entity);
            Ecs::Registry::UpdateComponent<BackgroundAudioSource>(entity);
        }

        auto spatialSourcesForSetup = registry.view<SpatialAudioSource, Ecs::Flags::Setup<SpatialAudioSource>>();

        for(auto& entity : spatialSourcesForSetup){
            auto& audioSource = spatialSourcesForSetup.get<SpatialAudioSource>(entity);

            audioSource.sound = *fileManager->getAsset(audioSource.fileName);

            Ecs::Registry::RemoveSetupFlag<SpatialAudioSource>(entity);
            Ecs::Registry::UpdateComponent<SpatialAudioSource>(entity);
        }
    }

    void AudioSystem::UpdateAudio() {

        auto& registry = Ecs::Registry::getCurrent();

        auto spatialSourcesChanged = registry.view<Graphics::Transform, SpatialAudioSource, Ecs::Flags::Update<SpatialAudioSource>>();

        for(auto& entity : spatialSourcesChanged){
            auto& transform = spatialSourcesChanged.get<Graphics::Transform>(entity);
            auto& audioSource = spatialSourcesChanged.get<SpatialAudioSource>(entity);

            /*audioSource.sound.setLooping(looping);*/
            soLoud.setVolume(audioSource.handle, audioSource.volume);
            soLoud.set3dSourceMinMaxDistance(audioSource.handle, audioSource.minDistance, audioSource.maxDistance);

            if(audioSource.play){
                audioSource.handle = soLoud.play3d(audioSource.sound,transform.translation.x, transform.translation.y, transform.translation.z);
                audioSource.play = false;
            }
            if (audioSource.interrupt){
                soLoud.stop(audioSource.handle);
                audioSource.interrupt = false;
            }

            Ecs::Registry::RemoveUpdateFlag<SpatialAudioSource>(entity);
        }

        auto backgroundSourcesChanged = registry.view<Graphics::Transform, BackgroundAudioSource, Ecs::Flags::Update<BackgroundAudioSource>>();

        for(auto& entity : backgroundSourcesChanged){
            auto& transform = backgroundSourcesChanged.get<Graphics::Transform>(entity);
            auto& audioSource = backgroundSourcesChanged.get<BackgroundAudioSource>(entity);

            /*audioSource.sound.setLooping(looping);*/
            soLoud.setVolume(audioSource.handle, audioSource.volume);

            if(audioSource.play){
                audioSource.handle = soLoud.playBackground(audioSource.sound/*, AudioListener::masterVolume * audioSource.volume*/);
                audioSource.play = false;
            }
            if (audioSource.interrupt){
                soLoud.stop(audioSource.handle);
                audioSource.interrupt = false;
            }

            Ecs::Registry::RemoveUpdateFlag<BackgroundAudioSource>(entity);
        }

        auto spatialTransformChanged = registry.view<
                Graphics::Transform, SpatialAudioSource, Ecs::Flags::Update<Graphics::Transform>>();

        for(auto& entity : spatialTransformChanged){
            auto& transform = spatialTransformChanged.get<Graphics::Transform>(entity);
            auto& audioSource = spatialTransformChanged.get<SpatialAudioSource>(entity);

            soLoud.set3dSourcePosition(audioSource.handle,
                                       transform.translation.x, transform.translation.y, transform.translation.z);

            if (registry.all_of<Physics::RigidBody>(entity)){
                auto& rigidBody = registry.get<Physics::RigidBody>(entity);
                auto velocity = rigidBody.rigidBody->getLinearVelocity();
                soLoud.set3dListenerVelocity(velocity.x, velocity.y, velocity.z);
            }

            soLoud.set3dSourceMinMaxDistance(audioSource.handle, audioSource.minDistance, audioSource.maxDistance);
        }

        auto listenerView = registry.view<Graphics::Transform, AudioListener,  Ecs::Flags::Update<Graphics::Transform>>();

        for (auto& entity : listenerView) {
            auto& transform = listenerView.get<Graphics::Transform>(entity);

            glm::vec4 atVector = transform.modelMatrix * glm::vec4(0., 0., -1., 0.);
            glm::vec4 upVector = transform.modelMatrix * glm::vec4(0., 1., 0., 0.);

            soLoud.set3dListenerParameters(transform.translation.x, transform.translation.y, transform.translation.z,
                                           atVector.x, atVector.y, atVector.z,
                                           upVector.x, upVector.y, upVector.z);

            if (registry.all_of<Physics::RigidBody>(entity)){
                auto& rigidBody = registry.get<Physics::RigidBody>(entity);
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

        auto spatialSourceEntitiesForDestruction = registry.view<SpatialAudioSource, Ecs::Flags::DestroyEntity>();

        for (auto entity:spatialSourceEntitiesForDestruction) {
            auto& audioSource = spatialSourceEntitiesForDestruction.get<SpatialAudioSource>(entity);

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

        auto backgroundSourceEntitiesForDestruction = registry.view<BackgroundAudioSource, Ecs::Flags::DestroyEntity>();

        for (auto entity:backgroundSourceEntitiesForDestruction) {
            auto& audioSource = backgroundSourceEntitiesForDestruction.get<BackgroundAudioSource>(entity);

            soLoud.stop(audioSource.handle);

            registry.remove<BackgroundAudioSource>(entity);
            Ecs::Registry::RemoveDestroyFlag<BackgroundAudioSource>(entity);
        }

        auto listenersForDestruction = registry.view<AudioListener, Ecs::Flags::Destroy<AudioListener>>();

        for (auto entity:listenersForDestruction) {
            registry.remove<AudioListener>(entity);
            Ecs::Registry::RemoveDestroyFlag<AudioListener>(entity);
        }

        auto listenerEntitiesForDestruction = registry.view<AudioListener, Ecs::Flags::DestroyEntity>();

        for (auto entity:listenerEntitiesForDestruction) {
            registry.remove<AudioListener>(entity);
            Ecs::Registry::RemoveDestroyFlag<AudioListener>(entity);
        }
    }
}