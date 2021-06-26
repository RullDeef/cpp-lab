#pragma once

#include <memory>
#include "IManager.hpp"
#include "SceneManager.hpp"
#include "API/Objects/Camera/ICamera.hpp"


class CameraManager : public IManager
{
public:
    explicit CameraManager(std::shared_ptr<SceneManager> sceneManager);
    virtual ~CameraManager() = default;

    virtual std::shared_ptr<ICamera> getActiveCamera();
    virtual void switchActiveCamera();

private:
    std::shared_ptr<SceneManager> sceneManager;
};
