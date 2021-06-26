#include <stdexcept>
#include "RenderManager.hpp"
#include "Scene/Scene.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Utils/Logger.hpp"


RenderManager::RenderManager(std::shared_ptr<Renderer> renderer)
    : renderer(renderer)
{
    LOG_FUNC;
}

void RenderManager::changeRenderer(std::shared_ptr<Renderer> newRenderer)
{
    LOG_FUNC;
    if (!newRenderer)
        throw std::runtime_error("RenderManager::changeRenderer: bad new renderer");
    renderer = newRenderer;
}

void RenderManager::renderScene(const Scene& scene, const Camera& camera)
{
    renderer->beginFrame(camera);
    for (auto& object : scene)
        object->accept(*renderer);
    renderer->endFrame();
}
