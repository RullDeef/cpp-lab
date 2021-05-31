#pragma once

#include <memory>
#include "Engine/API/Scene/Scene.hpp"
#include "IToolBase.hpp"


class HierarchyTool : public IToolBase
{
public:
    HierarchyTool();
    
    void setScene(std::shared_ptr<Scene> scene);

private:
    std::weak_ptr<Scene> scene;
};