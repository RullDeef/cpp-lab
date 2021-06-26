#pragma once

#include "API/Managers/IManagerFactory.hpp"
#include "Renderer/QtRenderer.hpp"


class QtManagerFactory : public IManagerFactory
{
public:
    QtManagerFactory(RenderViewport* viewport);
    virtual ~QtManagerFactory() = default;

    virtual std::shared_ptr<SceneManager> createSceneManager() override;
    virtual std::shared_ptr<RenderManager> createRenderManager() override;
    virtual std::shared_ptr<ObjectManager> createObjectManager() override;
    virtual std::shared_ptr<TransformManager> createTransformManager() override;
    virtual std::shared_ptr<CameraManager> createCameraManager() override;

private:
    RenderViewport* viewport;
    std::shared_ptr<QtRenderer> renderer;

    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<ObjectManager> objectManager;
    std::shared_ptr<RenderManager> renderManager;
    std::shared_ptr<TransformManager> transformManager;
    std::shared_ptr<CameraManager> cameraManager;
};
