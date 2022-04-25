#pragma once

#include <vector>
#include <map>
#include <stack>
#include <set>
#include <cmath>
#include "glm/vec3.hpp"
#include "CubicNode.h"

namespace logic {
    /*template<typename node>
    concept node = std::is_base_of<Node, node>::value*/
    class Grid {
    public:
        Grid(glm::vec3 startPosition);

        void UpdateGrid();

        void SetNodeLength();
        void GetNodeLength();

    private:
        static std::map<long, CubicNode> globalKnowledgeBase;
        static int nodeLength;
        std::vector<CubicNode *> localKnowledgeBase;
    };
}
