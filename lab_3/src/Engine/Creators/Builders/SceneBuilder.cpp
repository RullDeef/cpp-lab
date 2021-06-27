#include "SceneBuilder.hpp"
#include "Scene/Scene.hpp"
#include "Utils/Logger.hpp"


void SceneBuilder::addObject(IObject* object)
{
    LOG_FUNC;

    objects.push_back(object);
}

Scene* SceneBuilder::getResult()
{
    LOG_FUNC;

    Scene* result = new Scene(objects.begin(), objects.end());
    objects.clear();
    return result;
}
