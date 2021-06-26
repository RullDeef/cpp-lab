#pragma once

#include <memory>
#include "IManager.hpp"
#include "SceneManager.hpp"

class ISceneObject;


class ObjectManager : public IManager
{
public:
    explicit ObjectManager(std::shared_ptr<SceneManager> sceneManager);
    virtual ~ObjectManager() = default;

    virtual void addObject(std::shared_ptr<ISceneObject> object);
    virtual void removeObject(std::shared_ptr<ISceneObject> object);

    virtual void removeAllObjects();

private:
    std::shared_ptr<SceneManager> sceneManager;
};
