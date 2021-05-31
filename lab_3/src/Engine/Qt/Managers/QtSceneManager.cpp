#include "Utils/Logger.hpp"
#include "QtSceneManager.hpp"
#include "API/Scene/Directors/EmptySceneDirector.hpp"


QtSceneManager::QtSceneManager(std::shared_ptr<IStateManager> stateManager)
    : stateManager(stateManager)
{
}

void QtSceneManager::createEmptyScene()
{
    LOG_FUNC;

    auto builder = std::make_shared<SceneBuilder>();
    EmptySceneDirector director(builder);

    auto scene = director.makeScene();
    stateManager->setScene(scene);
}

void QtSceneManager::loadScene()
{
    LOG_FUNC;
}
