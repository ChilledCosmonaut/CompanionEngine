#include <iostream>
#include "engine/Tools/Grid.h"


namespace gl3::engine::tools {

    Grid::Grid(glm::vec3 startPosition) {
        glm::vec3 discreteStartPosition = glm::vec3(std::floor((int) startPosition.x / nodeLength),
                                                    std::floor((int) startPosition.y / nodeLength),
                                                    std::floor((int) startPosition.z / nodeLength));

        auto frontierNodes = std::deque<std::pair<glm::vec3, int>>();
        auto exploredNodes = std::unordered_set<glm::vec3>();

        if (knowledgeBase.count(discreteStartPosition) == 0) {
            knowledgeBase.insert(discreteStartPosition);
            frontierNodes.emplace_back(discreteStartPosition, 7);

            while (!frontierNodes.empty()) {
                auto [currentNode, radiusCounter] = frontierNodes.front();
                exploredNodes.insert(currentNode);

                if (radiusCounter > 0) {
                    for (auto currentDirection : directions) {
                        auto nextPosition = currentNode + currentDirection;

                        if (knowledgeBase.count(nextPosition) == 0) {
                            knowledgeBase.insert(nextPosition);
                            frontierNodes.emplace_back(nextPosition, radiusCounter - 1);
                        }
                    }
                }

                frontierNodes.pop_front();
            }
        }

        for(auto position:knowledgeBase){
            positions.emplace_back(Graphics::Transform(
                    glm::vec3(0, 0, 0),
                    position,
                    glm::vec3(0.5f, 0.5f, 0.5f)));
        }
    }

    void Grid::UpdateGrid() {

    }

    void Grid::SetNodeLength() {

    }

    void Grid::GetNodeLength() {

    }

    /*void Grid::VisualizeGrid(Graphics::Scene* scene, Graphics::Components::Model *model, const Graphics::shader* shader) {
        std::cout<<"Beginning Visualizing"<<std::endl;

        for (auto &position:positions) {
            //scene->AddSceneModels(*model, shader, &position);
        }
    }*/

    void Grid::SwitchVisiblePlane(int plane) {
        /*for (auto &position:positions) {
            if (position.GetTranslation().y != plane){
                position.SetActive(false);
            } else {
                position.SetActive(true);
            }
        }*/
    }
}