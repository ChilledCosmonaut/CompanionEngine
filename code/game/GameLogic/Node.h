#pragma once

#include <vector>
#include "glm/vec3.hpp"

namespace logic{
    class Node {
    public:

    private:
        glm::vec3 positionInGlobalSpace;
        std::vector<Node> neighbours;
    };
}
