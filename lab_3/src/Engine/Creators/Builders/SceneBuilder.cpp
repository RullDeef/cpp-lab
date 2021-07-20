#include "SceneBuilder.hpp"
#include "Scene/Scene.hpp"
#include "Utils/Logger.hpp"


void SceneBuilder::addObject(std::shared_ptr<IObject> object)
{
    LOG_FUNC;

    objects.push_back(object);
}

std::shared_ptr<Scene> SceneBuilder::getResult()
{
    LOG_FUNC;

    std::shared_ptr<Scene> result = std::make_shared<Scene>(objects.begin(), objects.end());
    objects.clear();
    return result;
}
