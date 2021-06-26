#include "QtStateManager.hpp"
#include "API/Scene/Directors/EmptySceneDirector.hpp"
#include "API/Objects/Builders/DefaultHullCubeBuilder.hpp"
#include "API/Objects/Builders/TransformBuilder.hpp"


QtStateManager::QtStateManager()
{
    scene = EmptySceneDirector(std::make_shared<SceneBuilder>()).makeScene();
    selection = std::make_shared<SceneObjectGroup>();
}

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
