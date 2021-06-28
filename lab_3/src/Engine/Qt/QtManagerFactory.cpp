#include "QtManagerFactory.hpp"
#include "Visitors/Renderer/Renderer.hpp"


QtManagerFactory::QtManagerFactory(RenderViewport* viewport)
    : viewport(viewport)
{
}

std::shared_ptr<SceneManager> QtManagerFactory::getSceneManager()
{
    if (!sceneManager)
    {
        sceneManager = std::make_shared<SceneManager>();
    }

    return sceneManager;
}

std::shared_ptr<CameraManager> QtManagerFactory::getCameraManager()
{
    if (!cameraManager)
    {
        cameraManager = std::make_shared<CameraManager>();
    }

    return cameraManager;
}

std::shared_ptr<RenderManager> QtManagerFactory::getRenderManager()
{
    if (!renderManager)
    {
        auto renderer = std::make_shared<Renderer>(viewport);
        renderManager = std::make_shared<RenderManager>(renderer);
    }

    return renderManager;
}

std::shared_ptr<LoadManager> QtManagerFactory::getLoadManager()
{
    if (!loadManager)
    {
        loadManager = std::make_shared<LoadManager>();
    }

    return loadManager;
}

std::shared_ptr<ObjectManager> QtManagerFactory::getObjectManager()
{
    if (!objectManager)
    {
        objectManager = std::make_shared<ObjectManager>();
    }

    return objectManager;
}

std::shared_ptr<TransformManager> QtManagerFactory::getTransformManager()
{
    if (!transformManager)
    {
        transformManager = std::make_shared<TransformManager>();
    }

    return transformManager;
}

std::shared_ptr<SelectionManager> QtManagerFactory::getSelectionManager()
{
    if (!selectionManager)
    {
        selectionManager = std::make_shared<SelectionManager>();
    }

    return selectionManager;
}
