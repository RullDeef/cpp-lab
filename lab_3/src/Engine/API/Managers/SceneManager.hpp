#pragma once

#include <memory>
#include "IManager.hpp"

class Scene;


class SceneManager : public IManager
{
public:
    void setScene(std::shared_ptr<Scene> newScene);

    Scene& getScene();
    const Scene& getScene() const;

private:
    std::shared_ptr<Scene> scene;
};
