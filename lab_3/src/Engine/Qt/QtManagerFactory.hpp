#pragma once

#include "API/Managers/IManagerFactory.hpp"


class QtManagerFactory : public IManagerFactory
{
public:
    QtManagerFactory(RenderViewport* viewport);
    virtual ~QtManagerFactory() = default;

    virtual std::shared_ptr<SceneManager> getSceneManager() override;
    virtual std::shared_ptr<CameraManager> getCameraManager() override;
    virtual std::shared_ptr<RenderManager> getRenderManager() override;
    virtual std::shared_ptr<LoadManager> getLoadManager() override;
    virtual std::shared_ptr<ObjectManager> getObjectManager() override;
    virtual std::shared_ptr<TransformManager> getTransformManager() override;
    virtual std::shared_ptr<SelectionManager> getSelectionManager() override;

private:
    RenderViewport* viewport;

    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<CameraManager> cameraManager;
    std::shared_ptr<RenderManager> renderManager;
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<ObjectManager> objectManager;
    std::shared_ptr<TransformManager> transformManager;
    std::shared_ptr<SelectionManager> selectionManager;
};
