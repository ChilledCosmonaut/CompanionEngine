#pragma once

#include "soloud.h"
#include <stdexcept>

#include "../../ECS/CoreSystem.h"
#include "engine/ECS/Registry.h"

#include "engine/Systems/FileManager/FileManager.h"

#include "engine/Systems/Graphics/Components/Transform.h"
#include "engine/Systems/Graphics/Utils/TransformationUtils.h"

#include "engine/Systems/Physics/Components/RigidBody.h"

#include "engine/Systems/Sound/Components/SpatialAudioSource.h"
#include "engine/Systems/Sound/Components/BackgroundAudioSource.h"
#include "engine/Systems/Sound/Components/AudioListener.h"

namespace gl3::engine::soundSystem {
    /// Provides a static class to interact with @AudioSource to provide a more spatial sound and overall control.
    class AudioSystem : Ecs::CoreSystem {
        friend class AudioSourceUtils;

    public:
        /// Need to adhere to the singleton pattern
        static AudioSystem *GetAudioSystem();

        /// Need to adhere to the singleton pattern
        static void DestroyAudioSystem();

        void SetupAudio();

        void UpdateAudio();

        void DestroyAudio();

    private:
        /// Sets up the audio system by initializing SoLoud.
        AudioSystem();

        /// Stops all sounds and deinitializes SoLoud.
        ~AudioSystem() override;


        static inline AudioSystem* audioSystem;
        SoLoud::Soloud soLoud {};
        float masterVolume = 1.0f;
        filesystem::FileManager* fileManager;
    };
}