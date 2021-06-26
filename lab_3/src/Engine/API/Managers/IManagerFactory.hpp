#pragma once

#include <memory>
#include "SceneManager.hpp"
#include "RenderManager.hpp"


class IManagerFactory
{
public:
    virtual ~IManagerFactory() = default;

    virtual std::shared_ptr<RenderManager> getRenderManager() = 0;
    virtual std::shared_ptr<SceneManager> getSceneManager() = 0;
};
