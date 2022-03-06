#pragma once

#include <vector>
#include <map>
#include "glm/vec3.hpp"
#include "Node.h"

namespace logic{
    class CubicNode : public Node{
    public:
        CubicNode();

        Node *checkForNeighbours() override;

        // Initialized in the constructor with a pair of vector and nullptr.
        // Later each neighbour is set correspondingly
        std::map<glm::vec3, CubicNode*> neighbours;

    private:
        glm::vec3 positionInGlobalSpace;
    };
}
