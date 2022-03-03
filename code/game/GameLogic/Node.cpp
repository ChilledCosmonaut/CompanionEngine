#include "Node.h"

namespace logic{
    Node::Node() {
        neighbours.insert({glm::vec3(1.0f,0.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,1.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,0.0f,1.0f), nullptr});
        neighbours.insert({glm::vec3(-1.0f,0.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,-1.0f,0.0f), nullptr});
        neighbours.insert({glm::vec3(0.0f,0.0f,-1.0f), nullptr});
    }
}