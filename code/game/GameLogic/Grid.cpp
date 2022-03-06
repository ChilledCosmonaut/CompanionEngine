#include "Grid.h"


namespace logic {
    Grid::Grid(glm::vec3 startPosition) {
        glm::vec3 discretizedStartPosition;
        discretizedStartPosition.x = std::floor(startPosition.x / (int) nodeLength);
        discretizedStartPosition.y = std::floor(startPosition.y / (int) nodeLength);
        discretizedStartPosition.z = std::floor(startPosition.z / (int) nodeLength);

        auto frontierNodes = std::deque<CubicNode>();

        CubicNode startNode = CubicNode();
        globalKnowledgeBase.insert({discretizedStartPosition, startNode});
        frontierNodes.push_back(startNode);

        while (!frontierNodes.empty()){
            auto currentNode = &frontierNodes.front();
            glm::vec3 currentPosition;
            frontierNodes.pop_front();

            for (auto &neighbourPair : currentNode->neighbours) {
                glm::vec3 nextPosition = neighbourPair.first + currentPosition;
                if(!globalKnowledgeBase.count(nextPosition))
                     globalKnowledgeBase.insert({nextPosition, CubicNode()});
                CubicNode* currentNeighbour = &globalKnowledgeBase[nextPosition];
                currentNode->neighbours.push_back(currentNeighbour);
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

