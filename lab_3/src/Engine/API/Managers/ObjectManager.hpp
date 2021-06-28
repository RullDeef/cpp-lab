#pragma once

#include <string>
#include "IManager.hpp"

class Scene;
class IObject;


class ObjectManager
{
public:
    void addObject(Scene& scene, IObject* object);

    void deleteObject(Scene& scene, IObject* object);
    void deleteObject(Scene& scene, const std::string& name);

    void clearScene(Scene& scene);
};
