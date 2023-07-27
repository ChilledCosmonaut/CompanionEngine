#pragma once

#include <vector>
#include <stack>
#include <cmath>
#include <unordered_set>
#include "glm/vec3.hpp"
#include "CubicNode.h"/*
#include "engine/GraphicsEngine/Scene.h"
#include "engine/GraphicsEngine/Components/Model.h"*/

namespace gl3::engine::tools {

    class Grid {
    public:
        explicit Grid(glm::vec3 startPosition);

        //void VisualizeGrid(Graphics::Scene* scene, Graphics::Components::Model *model, const Graphics::shader* shader);

        void UpdateGrid();

        void SetNodeLength();
        void GetNodeLength();

        void SwitchVisiblePlane(int plane);

    private:
        std::unordered_set<glm::vec3> knowledgeBase{};
        int nodeLength;
        std::vector<glm::vec3> directions{
                glm::vec3(1.0f,0.0f,0.0f),
                glm::vec3(0.0f,1.0f,0.0f),
                glm::vec3(0.0f,0.0f,1.0f),
                glm::vec3(-1.0f,0.0f,0.0f),
                glm::vec3(0.0f,-1.0f,0.0f),
                glm::vec3(0.0f,0.0f,-1.0f)
        };
        std::vector<Graphics::Transform> positions;
    };
}
