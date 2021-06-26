#pragma once

#include <memory>
#include "SceneManager.hpp"
#include "RenderManager.hpp"
#include "ObjectManager.hpp"
#include "CameraManager.hpp"
#include "TransformManager.hpp"


class IManagerFactory
{
public:
    virtual ~IManagerFactory() = default;

    virtual std::shared_ptr<IManager> createManager(type_info managerType) = 0;

    // virtual std::shared_ptr<SceneManager> createSceneManager() = 0;
    // virtual std::shared_ptr<RenderManager> createRenderManager() = 0;
    // virtual std::shared_ptr<ObjectManager> createObjectManager() = 0;
    // virtual std::shared_ptr<TransformManager> createTransformManager() = 0;
    // virtual std::shared_ptr<CameraManager> createCameraManager() = 0;
};
