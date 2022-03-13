#pragma once

#include <vector>
#include <map>
#include "glm/vec3.hpp"
#include "Node.h"
#include "CubicNode.h"

namespace logic{
    class CubicNode{
    public:
        CubicNode();

        std::vector<CubicNode*> checkForNeighbours(std::map<glm::vec3, CubicNode>* globalKnowledgeBase, std::set<CubicNode*>* exploredNodes);

        // Initialized in the constructor with a pair of vector and nullptr.
        // Later each neighbour is set correspondingly
        std::map<glm::vec3, CubicNode*> neighbours;

        void SetNeighbourAtDirection(glm::vec3 directionVector, CubicNode* node);

    private:
        glm::vec3 positionInGlobalSpace;
        int radiusCounter;
    };
}
