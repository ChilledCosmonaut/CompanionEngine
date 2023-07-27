#include "CleanUpSystem.h"

namespace gl3::engine::Ecs {
    CleanUpSystem *CleanUpSystem::GetCleanUpSystem() {
        if (cleanUpSystem == nullptr)
            cleanUpSystem = new CleanUpSystem();
        return cleanUpSystem;
    }

    void CleanUpSystem::DestroyCleanUpSystem() {
        cleanUpSystem->~CleanUpSystem();
        cleanUpSystem = nullptr;
    }

    void CleanUpSystem::Shutdown() {
        auto &registry = Ecs::Registry::getCurrent();

        auto toBeDestroyed = registry.view<Ecs::Flags::DestroyEntity>();

        for (auto &entity: toBeDestroyed)
            registry.destroy(entity);
    }
}
