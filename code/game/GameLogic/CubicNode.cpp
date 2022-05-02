#include "CubicNode.h"
#include "Grid.h"

namespace logic{

    CubicNode::CubicNode(int radiusCount, glm::vec3 globalPosition) {
        radiusCounter = radiusCount;
        globalTransform = Graphics::Transform(glm::vec3(0,0,0), globalPosition, glm::vec3(0.1f,0.1f,0.1f));
    }

    std::vector<CubicNode *>
    CubicNode::checkForNeighbours(std::unordered_map<glm::vec3, CubicNode> *globalKnowledgeBase,
                                  std::set<CubicNode *> *exploredNodes) {
        std::vector<CubicNode *> frontierNeighbours;

        if (radiusCounter > 0) {
            for (auto neighbour: neighbours) {
                auto neighbourDirection = neighbour.first;
                auto globalNeighbourPosition = positionInGlobalSpace + neighbourDirection;
                CubicNode *currentNeighbour;

                if (globalKnowledgeBase->count(globalNeighbourPosition) == 0) {
                    globalKnowledgeBase->insert({globalNeighbourPosition, CubicNode(radiusCounter-1, globalNeighbourPosition)});
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

    void CubicNode::SetNeighbourAtDirection(glm::vec3 directionVector, CubicNode *node) {
        neighbours[directionVector] = node;
    }
}