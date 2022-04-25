#include "Grid.h"


namespace logic {

    static long convertToLong(glm::vec3 vectorToConvert){
     return vectorToConvert.x + vectorToConvert.y * 1000 + vectorToConvert.z * 1000000;
    }


    Grid::Grid(glm::vec3 startPosition) {
        glm::vec3 discretizedStartPosition;
        discretizedStartPosition.x = std::floor((int) startPosition.x / nodeLength);
        discretizedStartPosition.y = std::floor((int) startPosition.y / nodeLength);
        discretizedStartPosition.z = std::floor((int) startPosition.z / nodeLength);

        auto frontierNodes = std::deque<CubicNode *>();

        auto exploredNodes = std::set<CubicNode *>();

        long discretizedStart = convertToLong(discretizedStartPosition);

        if (globalKnowledgeBase.count(discretizedStart) == 0) {
            globalKnowledgeBase.insert({discretizedStart, CubicNode()});
            auto startNode = &globalKnowledgeBase.at(discretizedStart);
            frontierNodes.push_back(startNode);

            while (!frontierNodes.empty()) {
                auto currentNode = frontierNodes.front();
                glm::vec3 currentPosition;
                frontierNodes.pop_front();

                auto unexploredNodes = currentNode->checkForNeighbours(&globalKnowledgeBase, &exploredNodes);

                for (auto newFrontierNode: unexploredNodes) {
                    frontierNodes.push_back(newFrontierNode);
                }
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