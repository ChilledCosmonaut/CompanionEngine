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

        std::vector<CubicNode*> checkForNeighbours(std::map<long, CubicNode>* globalKnowledgeBase, std::set<CubicNode*>* exploredNodes);

        // Initialized in the constructor with a pair of vector and nullptr.
        // Later each neighbour is set correspondingly
        std::map<long, CubicNode*> neighbours;

        void SetNeighbourAtDirection(long directionVector, CubicNode* node);

    private:
        long positionInGlobalSpace;
        int radiusCounter;
    };
}
