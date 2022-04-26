#include <iostream>
#include "Grid.h"


namespace logic {

    int Grid::nodeLength;
    std::map<long, CubicNode> Grid::globalKnowledgeBase;

    static long convertToLong(glm::vec3 vectorToConvert){
     return vectorToConvert.x + vectorToConvert.y * 1000 + vectorToConvert.z * 1000000;
    }

    Grid::Grid(glm::vec3 startPosition) {

        std::cout<<"Generating Grid"<<std::endl;

        glm::vec3 discretizedStartPosition;
        discretizedStartPosition.x = std::floor((int) startPosition.x / nodeLength);
        discretizedStartPosition.y = std::floor((int) startPosition.y / nodeLength);
        discretizedStartPosition.z = std::floor((int) startPosition.z / nodeLength);
        std::cout<<"Generated Start Position"<<std::endl;

        auto frontierNodes = std::deque<CubicNode *>();

        auto exploredNodes = std::set<CubicNode *>();

        long discretizedStart = convertToLong(discretizedStartPosition);

        std::cout<<"Inserting origin Node"<<std::endl;

        if (globalKnowledgeBase.count(discretizedStart) == 0) {
            globalKnowledgeBase.insert({discretizedStart, CubicNode()});
            auto startNode = &globalKnowledgeBase.at(discretizedStart);
            frontierNodes.push_back(startNode);
            std::cout<<"Starting to iterate frontier"<<std::endl;

            while (!frontierNodes.empty()) {
                auto currentNode = frontierNodes.front();
                glm::vec3 currentPosition;
                frontierNodes.pop_front();

                auto unexploredNodes = currentNode->checkForNeighbours(&globalKnowledgeBase, &exploredNodes);

                for (auto newFrontierNode: unexploredNodes) {
                    frontierNodes.push_back(newFrontierNode);
                }
                std::cout<<"Finished one Node"<<std::endl;
            }
        }

        std::cout << "Finished Generating Grid" << std::endl;
    }

    void Grid::UpdateGrid() {

    }

    void Grid::SetNodeLength() {

    }

    void Grid::GetNodeLength() {

    }

}