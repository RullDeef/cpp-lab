#include "Renderer.hpp"
#include "Objects/WireframeModel/WireframeModelAdapter.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Objects/ObjectGroup.hpp"
#include "RenderViewport.hpp"


Renderer::Renderer(RenderViewport* viewport)
    : viewport(viewport)
{
}

void Renderer::beginFrame(const Camera& camera)
{
    matrixStack.push(camera.getProjectionMatrix());
    viewport->clear();
}

void Renderer::endFrame()
{
    matrixStack = {};
}

void Renderer::visit(ObjectGroup& object)
{
    pushMatrix(object.getTransform());
    for (auto& child : object)
        child->accept(*this);
    popMatrix();
}

void Renderer::visit(WireframeModelAdapter& object)
{
    pushMatrix(object.getTransform());
    Matrix worldMatrix = getCurrMatrix();

    const WireframeModel& model = object.getModel();
    const auto& vertices = model.getVertices();

    for (const auto& [i, j] : model.getEdges())
    {
        const auto& v1 = vertices[i];
        const auto& v2 = vertices[j];

        const auto& p1 = v1.getPosition() * worldMatrix;
        const auto& p2 = v2.getPosition() * worldMatrix;

        viewport->drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }

    popMatrix();
}

void Renderer::visit(CameraAdapter& object)
{
}

const Matrix& Renderer::getCurrMatrix() const
{
    return matrixStack.top();
}

void Renderer::pushMatrix(const Matrix& mat)
{
    matrixStack.push(mat * matrixStack.top());
}

void Renderer::popMatrix()
{
    matrixStack.pop();
}
