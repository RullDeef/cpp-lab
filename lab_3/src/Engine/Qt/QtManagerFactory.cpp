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

std::shared_ptr<RenderManager> QtManagerFactory::getRenderManager()
{
    if (!renderManager)
    {
        auto renderer = std::make_shared<Renderer>(viewport);
        renderManager = std::make_shared<RenderManager>(renderer);
    }

    return renderManager;
}
