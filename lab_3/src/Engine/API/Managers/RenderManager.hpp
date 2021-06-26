#pragma once

#include <memory>
#include "IManager.hpp"
#include "Visitors/Renderer/Renderer.hpp"

class Scene;


class RenderManager : public IManager
{
public:
    explicit RenderManager(std::shared_ptr<Renderer> renderer);

    void changeRenderer(std::shared_ptr<Renderer> newRenderer);

    void renderScene(const Scene& scene, const Camera& camera);

private:
    std::shared_ptr<Renderer> renderer;
};