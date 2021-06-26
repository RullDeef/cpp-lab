#pragma once

#include "Visitors/IObjectVisitor.hpp"

class Camera;
class RenderViewport;


class Renderer : public IObjectVisitor
{
public:
    explicit Renderer(RenderViewport* viewport);

    void beginFrame(const Camera& camera);
    void endFrame();

    virtual void visit(ObjectGroup& object) override;
    virtual void visit(WireframeModelAdapter& object) override;
    virtual void visit(CameraAdapter& object) override;

private:
    RenderViewport* viewport;
    const Camera* activeCamera = nullptr;
};
