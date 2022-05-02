#include <iostream>
#include "Grid.h"


namespace logic {

    int Grid::nodeLength = 3;
    std::unordered_map<glm::vec3, CubicNode> Grid::globalKnowledgeBase = std::unordered_map<glm::vec3, CubicNode>();

    Grid::Grid(glm::vec3 startPosition) {
        glm::vec3 discretizedStartPosition = glm::vec3(std::floor((int) startPosition.x / nodeLength),
                                                       std::floor((int) startPosition.y / nodeLength),
                                                       std::floor((int) startPosition.z / nodeLength));

        auto frontierNodes = std::deque<CubicNode *>();
        auto exploredNodes = std::set<CubicNode *>();

        if (globalKnowledgeBase.count(discretizedStartPosition) == 0) {
            globalKnowledgeBase.insert({discretizedStartPosition, CubicNode(7, discretizedStartPosition)});
            auto startNode = &globalKnowledgeBase.at(discretizedStartPosition);
            frontierNodes.push_back(startNode);


            while (!frontierNodes.empty()) {
                auto currentNode = frontierNodes.front();
                glm::vec3 currentPosition;
                exploredNodes.insert(currentNode);

                auto unexploredNodes = currentNode->checkForNeighbours(&globalKnowledgeBase, &exploredNodes);

                for (auto newFrontierNode: unexploredNodes) {
                    frontierNodes.push_back(newFrontierNode);
                    exploredNodes.insert(newFrontierNode);
                }

                frontierNodes.pop_front();
            }
        }
    }

    void Grid::UpdateGrid() {

    }

    void Grid::SetNodeLength() {

    }

    void Grid::GetNodeLength() {

    }

    void Grid::VisualizeGrid(Graphics::Scene* scene, Model *model, const gl3::shader* shader) {
        std::cout<<"Beginning Visualizing"<<std::endl;

        for (auto& [position, node]:globalKnowledgeBase) {
            scene->AddSceneModels(*model, shader, &node.globalTransform);
        }
    }
}