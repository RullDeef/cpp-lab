#include "Scene.hpp"


Scene::ObjectIterator Scene::begin()
{
    return objects.begin();
}

Scene::ObjectIterator Scene::end()
{
    return objects.end();
}

Scene::ConstObjectIterator Scene::begin() const
{
    return objects.begin();
}

Scene::ConstObjectIterator Scene::end() const
{
    return objects.end();
}
