#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include "glm/vec3.hpp"
#include "engine/Systems/Graphics/Components/Transform.h"

namespace std{
    template<>
    struct std::hash<glm::vec3>
    {
        size_t operator()(glm::vec3 const& v) const{
            return hash<std::string>()(/*v.x + v.y * 1000 + v.z * 1000000*/std::to_string(v.x) + "," +
                                       std::to_string(v.y) + "," +
                                       std::to_string(v.z));
        };
    };
}


namespace gl3::engine::tools {

    class CubicNode{
    public:
        explicit CubicNode(int radiusCount, glm::vec3 globalPosition);

        std::vector<CubicNode*> checkForNeighbours(std::unordered_map<glm::vec3, CubicNode>* globalKnowledgeBase, std::set<CubicNode*>* exploredNodes);

        // Initialized in the constructor with a pair of vector and nullptr.
        // Later each neighbour is set correspondingly
        std::vector<std::pair<glm::vec3, CubicNode*>> neighbours{
                {glm::vec3(1.0f,0.0f,0.0f),nullptr},
                {glm::vec3(0.0f,1.0f,0.0f),nullptr},
                {glm::vec3(0.0f,0.0f,1.0f),nullptr},
                {glm::vec3(-1.0f,0.0f,0.0f),nullptr},
                {glm::vec3(0.0f,-1.0f,0.0f),nullptr},
                {glm::vec3(0.0f,0.0f,-1.0f),nullptr}
        };

        void SetNeighbourAtDirection(glm::vec3 directionVector, CubicNode* node);
        Graphics::Transform globalTransform;

    private:
        glm::vec3 positionInGlobalSpace{};
        int radiusCounter;
    };
}
