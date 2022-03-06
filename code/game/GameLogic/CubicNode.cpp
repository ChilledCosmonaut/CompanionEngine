#include "CubicNode.h"

namespace logic{
    CubicNode::CubicNode() {
        neighbours.insert({glm::vec3(1.0f,0.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,1.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,0.0f,1.0f), nullptr});
        neighbours.insert({glm::vec3(-1.0f,0.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,-1.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,0.0f,-1.0f), nullptr});
    }

    std::vector<Node*> CubicNode::checkForNeighbours() {
    }
}