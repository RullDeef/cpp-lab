#include "QtStateManager.hpp"

std::shared_ptr<Scene> QtStateManager::getScene()
{
    return scene;
}

void QtStateManager::setScene(std::shared_ptr<Scene> newScene)
{
    scene = newScene;
}

std::shared_ptr<SceneObjectGroup> QtStateManager::getSelection()
{
    return selection;
}

void QtStateManager::setSelection(std::shared_ptr<SceneObjectGroup> newSelection)
{
    selection = newSelection;
}
