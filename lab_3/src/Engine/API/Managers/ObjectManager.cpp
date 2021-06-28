#include <stdexcept>
#include <algorithm>
#include "ObjectManager.hpp"
#include "Scene/Scene.hpp"
#include "Objects/IObject.hpp"
#include "Objects/ObjectGroup.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Creators/Directors/DefaultCameraDirector.hpp"
#include "Utils/Logger.hpp"


void ObjectManager::addObject(Scene& scene, IObject* object)
{
    LOG_FUNC;

    if (!object)
        throw std::runtime_error("ObjectManager::addObject: bad object pointer");

    if (std::find(scene.begin(), scene.end(), object) != scene.end())
        return;

    std::string name = object->getName();
    int counter = 0;
    std::find_if(scene.begin(), scene.end(), [&name, &counter](IObject* obj)
    {
        if (obj->getName() == name)
            counter++;
        return false;
    });

    if (counter > 0)
        object->setName(object->getName() + " (" + std::to_string(counter) + ")");

    scene.insert(scene.end(), object);
}

void ObjectManager::deleteObject(Scene& scene, IObject* object)
{
    LOG_FUNC;

    if (!object)
        throw std::runtime_error("ObjectManager::deleteObject: bad object pointer");

    if (std::find(scene.begin(), scene.end(), object) == scene.end())
    {
        if (auto group = dynamic_cast<ObjectGroup*>(object))
        {
            for (auto& obj : *group)
                deleteObject(scene, obj);
        }
        else
            throw std::runtime_error("ObjectManager::deleteObject: object is not in scene");
    }
    else
        scene.erase(std::remove(scene.begin(), scene.end(), object), scene.end());
}

void ObjectManager::deleteObject(Scene& scene, const std::string& name)
{
    LOG_FUNC;

    auto sameName = [&name](IObject* obj) { return obj->getName() == name; };

    if (std::find_if(scene.begin(), scene.end(), sameName) == scene.end())
        throw std::runtime_error("ObjectManager::deleteObject: object not found");

    scene.erase(std::remove_if(scene.begin(), scene.end(), sameName), scene.end());
}

void ObjectManager::clearScene(Scene& scene)
{
    LOG_FUNC;

    scene.erase(scene.begin(), scene.end());
    scene.insert(scene.end(), DefaultCameraDirector().makeObject());
}
