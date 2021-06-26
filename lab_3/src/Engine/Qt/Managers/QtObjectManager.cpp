#include "Utils/Logger.hpp"
#include "API/Objects/ISceneObject.hpp"
#include "QtObjectManager.hpp"


QtObjectManager::QtObjectManager(std::shared_ptr<IStateManager> stateManager)
    : stateManager(stateManager)
{
    LOG_FUNC;
}

void QtObjectManager::addObject(std::shared_ptr<ISceneObject> object)
{
    LOG_FUNC;
 
    auto scene = stateManager->getScene();
    scene->addChild(object);
}

void QtObjectManager::removeObject(std::shared_ptr<ISceneObject> object)
{
    LOG_FUNC;

    auto scene = stateManager->getScene();
    scene->removeChild(object);
}

void QtObjectManager::removeAllObjects()
{
    LOG_FUNC;

    auto scene = stateManager->getScene();

    while (scene->begin() != scene->end())
        scene->removeChild(*scene->begin());
}
