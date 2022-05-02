#include <iostream>
#include "Grid.h"


namespace logic {

    int Grid::nodeLength = 3;
    std::unordered_map<glm::vec3, CubicNode> Grid::globalKnowledgeBase = std::unordered_map<glm::vec3, CubicNode>();

    static long convertToLong(glm::vec3 vectorToConvert){
     return vectorToConvert.x + vectorToConvert.y * 1000 + vectorToConvert.z * 1000000;
    }

    Grid::Grid(glm::vec3 startPosition, Graphics::Scene* scene, Model *model, const gl3::shader* shader) {
        glm::vec3 discretizedStartPosition = glm::vec3(std::floor((int) startPosition.x / nodeLength),
                                                       std::floor((int) startPosition.y / nodeLength),
                                                       std::floor((int) startPosition.z / nodeLength));

        auto frontierNodes = std::deque<CubicNode *>();
        auto exploredNodes = std::set<CubicNode *>();

        if (globalKnowledgeBase.count(discretizedStartPosition) == 0) {
            globalKnowledgeBase.insert({discretizedStartPosition, CubicNode(20, discretizedStartPosition)});
            auto startNode = &globalKnowledgeBase.at(discretizedStartPosition);
            frontierNodes.push_back(startNode);

            while (!frontierNodes.empty()) {
                auto currentNode = frontierNodes.front();
                glm::vec3 currentPosition;
                exploredNodes.insert(currentNode);

                auto unexploredNodes = currentNode->checkForNeighbours(&globalKnowledgeBase, &exploredNodes);

                for (auto newFrontierNode: unexploredNodes) {
                    frontierNodes.push_back(newFrontierNode);
                }

                frontierNodes.pop_front();
            }
        }

        for (auto& [position, node]:globalKnowledgeBase) {
            scene->AddSceneModels(*model, shader, &node.globalTransform);
        }
    }

    void Grid::UpdateGrid() {

    }

    void Grid::SetNodeLength() {

    }

    void Grid::GetNodeLength() {

    }
}