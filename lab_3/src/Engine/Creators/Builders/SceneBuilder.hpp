#pragma once

#include <list>

class IObject;
class Scene;


class SceneBuilder
{
public:
    void addObject(IObject* object);

    Scene* getResult();

private:
    std::list<IObject*> objects;
};
