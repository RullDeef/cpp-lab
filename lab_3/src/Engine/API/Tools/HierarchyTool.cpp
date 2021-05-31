#include "HierarchyTool.hpp"

HierarchyTool::HierarchyTool()
{
}

void HierarchyTool::setScene(std::shared_ptr<Scene> scene)
{
    this->scene = scene;
}
