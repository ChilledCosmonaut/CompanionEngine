#pragma once

#include <vector>
#include <unordered_map>
#include "glm/vec3.hpp"
#include "Node.h"
#include "CubicNode.h"

namespace logic{
    class CubicNode{
    public:
        explicit CubicNode(int radiusCount);

        std::vector<CubicNode*> checkForNeighbours(std::unordered_map<glm::vec3, CubicNode>* globalKnowledgeBase, std::set<CubicNode*>* exploredNodes);

        // Initialized in the constructor with a pair of vector and nullptr.
        // Later each neighbour is set correspondingly
        std::unordered_map<glm::vec3, CubicNode*> neighbours;

        void SetNeighbourAtDirection(long directionVector, CubicNode* node);

    private:
        glm::vec3 positionInGlobalSpace;
        int radiusCounter;
    };
}
