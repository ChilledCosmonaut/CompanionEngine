#pragma once

#include <vector>
#include <map>
#include "glm/vec3.hpp"

namespace logic{
    class Node {
    public:
        Node();

        // Initialized in the constructor with a pair of vector and nullptr.
        // Later each neighbour is set correspondingly
        std::map<glm::vec3, Node*> neighbours;

    private:
        glm::vec3 positionInGlobalSpace;
    };
}
