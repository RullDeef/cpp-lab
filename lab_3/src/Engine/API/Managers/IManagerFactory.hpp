#pragma once

#include <memory>
#include "SceneManager.hpp"
#include "CameraManager.hpp"
#include "RenderManager.hpp"
#include "LoadManager.hpp"


class IManagerFactory
{
public:
    virtual ~IManagerFactory() = default;

    virtual std::shared_ptr<RenderManager> getRenderManager() = 0;
    virtual std::shared_ptr<CameraManager> getCameraManager() = 0;
    virtual std::shared_ptr<SceneManager> getSceneManager() = 0;
    virtual std::shared_ptr<LoadManager> getLoadManager() = 0;
};
