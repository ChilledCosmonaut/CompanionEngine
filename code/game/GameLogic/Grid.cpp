#include "Grid.h"


namespace logic {
    Grid::Grid(glm::vec3 startPosition) {
        glm::vec3 discretizedStartPosition;
        discretizedStartPosition.x = std::floor((int) startPosition.x / nodeLength);
        discretizedStartPosition.y = std::floor((int) startPosition.y / nodeLength);
        discretizedStartPosition.z = std::floor((int) startPosition.z / nodeLength);

        auto frontierNodes = std::deque<Node *>();

        globalKnowledgeBase.insert({discretizedStartPosition, CubicNode()});
        auto startNode  = globalKnowledgeBase.at(discretizedStartPosition);
        frontierNodes.push_back(&startNode);

        while (!frontierNodes.empty()){
            auto currentNode = frontierNodes.front();
            glm::vec3 currentPosition;
            frontierNodes.pop_front();

            auto unexploredNodes = currentNode->checkForNeighbours();

            for (auto newFrontierNode:unexploredNodes) {
                frontierNodes.push_back(newFrontierNode);
            }
        }
    }

    void Grid::UpdateGrid() {

    }

    void Grid::SetNodeLength() {

    }

    void Grid::GetNodeLength() {

    }
}

