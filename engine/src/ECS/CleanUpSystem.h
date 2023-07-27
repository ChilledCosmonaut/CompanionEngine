#pragma once

#include "engine/ECS/Registry.h"

#include "CoreSystem.h"

namespace gl3::engine::Ecs {
    class CleanUpSystem : Ecs::CoreSystem {

    public:
        /// Need to adhere to the singleton pattern
        static CleanUpSystem *GetCleanUpSystem();

        /// Need to adhere to the singleton pattern
        static void DestroyCleanUpSystem();

        void SetUp() {};

        void Update() {};

        void Shutdown();

    private:

        CleanUpSystem() {};

        ~CleanUpSystem()  override {};

        inline static CleanUpSystem* cleanUpSystem = nullptr;
    };
}
