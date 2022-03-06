#pragma once

#include <vector>

class Node {
public:
    virtual std::vector<Node*> checkForNeighbours() = 0;
private:
};
