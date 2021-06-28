#pragma once

#include <stack>
#include "Core/Math/Matrix.hpp"
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
    const Matrix& getCurrMatrix() const;
    void pushMatrix(const Matrix& mat);
    void popMatrix();

    RenderViewport* viewport;
    // const Camera* activeCamera = nullptr;

    std::stack<Matrix> matrixStack;
};
