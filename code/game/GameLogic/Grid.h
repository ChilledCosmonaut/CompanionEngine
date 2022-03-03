#pragma once

#include <vector>
#include <map>
#include <stack>
#include <cmath>
#include "glm/vec3.hpp"
#include "Node.h"

namespace logic {
    class Grid {
    public:
        Grid(glm::vec3 startPosition);

        void UpdateGrid();

        void SetNodeLength();
        void GetNodeLength();

    private:
        static std::map<glm::vec3, Node> globalKnowledgeBase;
        static int nodeLength;
        std::vector<Node *> localKnowledgeBase;
    };
}
