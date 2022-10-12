#pragma once

#include <vector>

namespace gl3::engine::tools {
    class Node {
    public:
        virtual std::vector<Node *> checkForNeighbours() = 0;

    private:
    };
}