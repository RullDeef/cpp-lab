#include "SceneObjectGroup.hpp"
#include "API/Objects/IObjectVisitor.hpp"


SceneObjectGroup::SceneObjectGroup(const std::string& name)
    : ISceneObject(name)
{
}

std::shared_ptr<ISceneObject> SceneObjectGroup::clone() const
{
    auto copy = std::make_shared<SceneObjectGroup>(getName());
    for (auto& obj : objects)
        copy->addChild(obj->clone());
    return copy;
}

void SceneObjectGroup::accept(IObjectVisitor* visitor)
{
    visitor->visit(*this);
}

void SceneObjectGroup::addChild(std::shared_ptr<ISceneObject> object)
{
    objects.push_back(object);
}

void SceneObjectGroup::removeChild(std::shared_ptr<ISceneObject> object)
{
    objects.remove(object);
}

bool SceneObjectGroup::hasChild(std::shared_ptr<ISceneObject> object) const
{
    for (const auto& obj : objects)
        if (obj == object)
            return true;
    return false;
}

size_t SceneObjectGroup::size() const
{
    return objects.size();
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
