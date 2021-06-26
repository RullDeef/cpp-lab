#pragma once

#include "IManager.hpp"
#include "API/Scene/Scene.hpp"


class SceneManager : public IManager
{
public:
    SceneManager();
    virtual ~SceneManager() = default;

    virtual void createEmptyScene();
    virtual void loadScene(const char* filename);

    virtual Scene& getScene();
    virtual const Scene& getScene() const;

private:
    std::shared_ptr<Scene> scene;
};
