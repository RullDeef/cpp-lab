#include "ObjectManager.hpp"
#include "Utils/Logger.hpp"


ObjectManager::ObjectManager(std::shared_ptr<SceneManager> sceneManager)
    : sceneManager(sceneManager)
{
}

void ObjectManager::addObject(std::shared_ptr<ISceneObject> object)
{
    LOG_FUNC;

    auto scene = sceneManager->getScene();
    scene.addChild(object);
}

void ObjectManager::removeObject(std::shared_ptr<ISceneObject> object)
{
    LOG_FUNC;

    auto scene = sceneManager->getScene();
    scene.removeChild(object);
}

void ObjectManager::removeAllObjects()
{
    LOG_FUNC;

    auto scene = sceneManager->getScene();

    while (scene.begin() != scene.end())
        scene.removeChild(*scene.begin());
}
