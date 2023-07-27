#include "engine/Tools/CubicNode.h"

namespace gl3::engine::tools{

    CubicNode::CubicNode(int radiusCount, glm::vec3 globalPosition) {
        radiusCounter = radiusCount;
        globalTransform = Graphics::Transform(glm::vec3(0,0,0), globalPosition, glm::vec3(0.5f,0.5f,0.5f));
        positionInGlobalSpace = globalPosition;
    }

    std::vector<CubicNode *>
    CubicNode::checkForNeighbours(std::unordered_map<glm::vec3, CubicNode> *globalKnowledgeBase,
                                  std::set<CubicNode *> *exploredNodes) {
        std::vector<CubicNode *> frontierNeighbours;

        if (radiusCounter > 0) {
            for (int neighbourIndex = 0; neighbourIndex < neighbours.size(); neighbourIndex++/*auto & [neighbourDirection, neighbour]: neighbours*/) {
                auto &[neighbourDirection, neighbour] = neighbours[neighbourIndex];
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
                neighbours[neighbourIndex].second = currentNeighbour;
            }
        } else {
            for (int neighbourIndex = 0; neighbourIndex < neighbours.size(); neighbourIndex++/*auto neighbour: neighbours*/) {
                auto &[neighbourDirection, neighbour] = neighbours[neighbourIndex];
                auto globalNeighbourPosition = positionInGlobalSpace + neighbourDirection;
                //CubicNode *currentNeighbour = neighbours.at(globalNeighbourPosition);

                if (globalKnowledgeBase->find(globalNeighbourPosition) != globalKnowledgeBase->end())
                    neighbours[neighbourIndex].second = &globalKnowledgeBase->at(globalNeighbourPosition);
            }

        }

        return frontierNeighbours;
    }

    void CubicNode::SetNeighbourAtDirection(glm::vec3 directionVector, CubicNode *node) {
        //neighbours[directionVector] = node;
    }
}