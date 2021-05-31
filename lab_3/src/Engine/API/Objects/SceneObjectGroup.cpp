#include "SceneObjectGroup.hpp"

SceneObjectGroup::SceneObjectGroup(const std::string& name)
    : ISceneObject(name)
{
}

void SceneObjectGroup::addObject(std::shared_ptr<ISceneObject> object)
{
    objects.push_back(object);
}

void SceneObjectGroup::applyTransform(const Transform& t)
{
}

std::shared_ptr<ISceneObject> SceneObjectGroup::clone() const
{
    auto copy = std::make_shared<SceneObjectGroup>(getName());
    for (auto& obj : objects)
        copy->addChild(obj->clone());
    return copy;
}

/*
void SceneObjectGroup::draw(std::shared_ptr<IRenderer> renderer) const
{
    renderer->saveMatrix();
    renderer->multiplyMatrix(getTransform());

    for (auto& object : objects)
        object->draw(renderer);

    renderer->restoreMatrix();
}
*/

void SceneObjectGroup::accept(std::shared_ptr<IObjectVisitor> visitor)
{
    for (auto& obj : objects)
        obj->accept(visitor);
}

void SceneObjectGroup::addChild(std::shared_ptr<ISceneObject> object)
{
    objects.push_back(object);
}

void SceneObjectGroup::removeChild(std::shared_ptr<ISceneObject> object)
{
    objects.remove(object);
}

bool SceneObjectGroup::isVisible() const
{
    for (const auto& obj : objects)
        if (obj->isVisible())
            return true;
    return false;
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
