#pragma once

#include <memory>
#include <list>

class IObject;
class Scene;


class SceneBuilder
{
public:
    void addObject(std::shared_ptr<IObject> object);

    std::shared_ptr<Scene> getResult();

private:
    std::list<std::shared_ptr<IObject>> objects;
};
