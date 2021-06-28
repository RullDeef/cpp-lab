#include "Scene.hpp"


void Scene::insert(ObjectIterator iter, IObject* object)
{
    objects.insert(iter, object);
}

void Scene::erase(ConstObjectIterator iter)
{
    objects.erase(iter);
}

void Scene::erase(ConstObjectIterator iterFirst, ConstObjectIterator iterLast)
{
    objects.erase(iterFirst, iterLast);
}

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
