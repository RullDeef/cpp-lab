#pragma once

#include <string>
#include <memory>
#include "IManager.hpp"

class Scene;
class IObject;


class ObjectManager
{
public:
    void addObject(Scene& scene, std::shared_ptr<IObject> object);

    void deleteObject(Scene& scene, std::shared_ptr<IObject> object);
    void deleteObject(Scene& scene, const std::string& name);

    void clearScene(Scene& scene);
};
