#include "SceneObjectGroup.hpp"

void SceneObjectGroup::addObject(std::shared_ptr<ISceneObject> object)
{
    objects.push_back(object);
}

void SceneObjectGroup::draw(std::shared_ptr<IRenderer> renderer) const
{
    renderer->saveMatrix();
    renderer->multiplyMatrix(getTransform());

    for (auto& object : objects)
        object->draw(renderer);

    renderer->restoreMatrix();
}

std::list<std::shared_ptr<ISceneObject>>::iterator SceneObjectGroup::begin()
{
    return objects.begin();
}

std::list<std::shared_ptr<ISceneObject>>::iterator SceneObjectGroup::end()
{
    return objects.end();
}

std::list<std::shared_ptr<ISceneObject>>::const_iterator SceneObjectGroup::begin() const
{
    return objects.begin();
}

std::list<std::shared_ptr<ISceneObject>>::const_iterator SceneObjectGroup::end() const
{
    return objects.end();
}
