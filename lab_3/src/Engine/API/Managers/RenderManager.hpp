#pragma once

#include "IManager.hpp"
#include "SceneManager.hpp"
#include "CameraManager.hpp"
#include "API/Renderer/IRenderer.hpp"


class RenderManager : public IManager
{
public:
    explicit RenderManager(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<CameraManager> cameraManager, std::shared_ptr<IRenderer> renderer);
    virtual ~RenderManager() = default;

    virtual void renderScene();

private:
    std::shared_ptr<IRenderer> renderer;
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<CameraManager> cameraManager;
};
