#include "Renderer.hpp"


Renderer::Renderer(RenderViewport* viewport)
    : viewport(viewport)
{
}

void Renderer::beginFrame(const Camera& camera)
{
    activeCamera = &camera;
}

void Renderer::endFrame()
{
    activeCamera = nullptr;
}

void Renderer::visit(ObjectGroup& object)
{
}

void Renderer::visit(WireframeModelAdapter& object)
{
}

void Renderer::visit(CameraAdapter& object)
{
}
