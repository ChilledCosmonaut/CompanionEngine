#include <iostream>
#include "Grid.h"
/*#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"*/


namespace logic{


    CubicNode::CubicNode(int radiusCount) {
        radiusCounter = radiusCount;
        neighbours[glm::vec3(1.0f,0.0f,0.0f)] = nullptr;
        neighbours[glm::vec3(0.0f,1.0f,0.0f)] = nullptr;
        neighbours[glm::vec3(0.0f,0.0f,1.0f)] = nullptr;
        neighbours[glm::vec3(-1.0f,0.0f,0.0f)] = nullptr;
        neighbours[glm::vec3(0.0f,-1.0f,0.0f)] = nullptr;
        neighbours[glm::vec3(0.0f,0.0f,-1.0f)] = nullptr;
    }

    std::vector<CubicNode *> CubicNode::checkForNeighbours(std::unordered_map<glm::vec3, CubicNode> *globalKnowledgeBase,
                                                           std::set<CubicNode *> *exploredNodes) {
        std::vector<CubicNode *> frontierNeighbours;

        if (radiusCounter > 0) {
            for (auto neighbour: neighbours) {
                auto neighbourDirection = neighbour.first;
                auto globalNeighbourPosition = positionInGlobalSpace + neighbourDirection;
                CubicNode *currentNeighbour;

                if (globalKnowledgeBase[globalNeighbourPosition] == nullptr) {
                    globalKnowledgeBase->insert({globalNeighbourPosition, CubicNode(radiusCounter-1)});
                    currentNeighbour = &globalKnowledgeBase->at(globalNeighbourPosition);
                    frontierNeighbours.push_back(currentNeighbour);
                } else {
                    currentNeighbour = &globalKnowledgeBase->at(globalNeighbourPosition);
                    if (exploredNodes->count(currentNeighbour) == 0)
                        frontierNeighbours.push_back(currentNeighbour);
                }
                neighbours[neighbourDirection] = currentNeighbour;
            }
        } else {
            for (auto neighbour: neighbours) {
                auto neighbourDirection = neighbour.first;
                auto globalNeighbourPosition = positionInGlobalSpace + neighbourDirection;
                CubicNode *currentNeighbour = neighbours.at(globalNeighbourPosition);

                if (currentNeighbour != nullptr)
                    currentNeighbour->SetNeighbourAtDirection(neighbourDirection, this);
            }

        }

        return frontierNeighbours;
    }

    void CubicNode::SetNeighbourAtDirection(long directionVector, CubicNode *node) {
        neighbours[directionVector] = node;
    }
}