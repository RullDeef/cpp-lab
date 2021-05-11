#include "SceneManager.hpp"
#include "Engine/Tools/Logger.hpp"

SceneManager::SceneManager()
{
    createEmptyScene();
}

void SceneManager::createEmptyScene()
{
    LOG_FUNC;

    scene = std::make_shared<Scene>();
}

void SceneManager::loadScene(const char* filename)
{
    LOG_FUNC;
}

bool SceneManager::addSceneObject(std::shared_ptr<ISceneObject> object)
{
    LOG_FUNC;

    scene->addObject(object);
    return true;
}

void SceneManager::renderScene(std::shared_ptr<IRenderer> renderer, std::shared_ptr<ICamera> camera)
{
    renderer->beginFrame(camera);

    for (auto& object : *scene)
        object->draw(renderer);

    renderer->endFrame();
}
