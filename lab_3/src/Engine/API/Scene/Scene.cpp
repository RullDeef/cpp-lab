#include "Scene.hpp"


Scene::Scene(const SceneObjectGroup& objectGroup)
    : objectGroup(objectGroup)
{
}

std::list<std::shared_ptr<ISceneObject>>::iterator Scene::begin()
{
    return objectGroup.begin();
}

std::list<std::shared_ptr<ISceneObject>>::iterator Scene::end()
{
    return objectGroup.end();
}

std::list<std::shared_ptr<ISceneObject>>::const_iterator Scene::begin() const
{
    return objectGroup.begin();
}

std::list<std::shared_ptr<ISceneObject>>::const_iterator Scene::end() const
{
    return objectGroup.end();
}
