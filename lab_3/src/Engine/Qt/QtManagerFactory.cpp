#include "QtManagerFactory.hpp"


QtManagerFactory::QtManagerFactory(RenderViewport* viewport)
    : viewport(viewport)
{
}

std::shared_ptr<SceneManager> QtManagerFactory::createSceneManager()
{
    if (!sceneManager)
    {
        sceneManager = std::make_shared<SceneManager>();
    }

    return sceneManager;
}

std::shared_ptr<RenderManager> QtManagerFactory::createRenderManager()
{
    if (!renderManager)
    {
        createSceneManager();
        createCameraManager();
        renderer = std::make_shared<QtRenderer>(viewport);
        renderManager = std::make_shared<RenderManager>(sceneManager, cameraManager, renderer);
    }

    return renderManager;
}

std::shared_ptr<ObjectManager> QtManagerFactory::createObjectManager()
{
    if (!objectManager)
    {
        createSceneManager();
        objectManager = std::make_shared<ObjectManager>(sceneManager);
    }

    return objectManager;
}

std::shared_ptr<TransformManager> QtManagerFactory::createTransformManager()
{
    if (!transformManager)
    {
        transformManager = std::make_shared<TransformManager>();
    }

    return transformManager;
}

std::shared_ptr<CameraManager> QtManagerFactory::createCameraManager()
{
    if (!cameraManager)
    {
        createSceneManager();
        cameraManager = std::make_shared<CameraManager>(sceneManager);
    }

    return cameraManager;
}
