#include "IRenderer.hpp"

#if false
IRenderer::IRenderer()
{
    matrixStack.push(Matrix::identity());
}

void IRenderer::beginFrame(std::shared_ptr<ICamera> camera)
{
    this->camera = camera;
}

void IRenderer::endFrame()
{
    camera = nullptr;
}

void IRenderer::saveMatrix()
{
    matrixStack.push(matrixStack.top());
}

void IRenderer::restoreMatrix()
{
    if (matrixStack.size() > 1)
        matrixStack.pop();
}

void IRenderer::multiplyMatrix(const Matrix& mat)
{
    Matrix res = mat * matrixStack.top();
    matrixStack.pop();
    matrixStack.push(res);
}

std::shared_ptr<ICamera> IRenderer::getCamera() const
{
    return camera;
}

const Matrix& IRenderer::getMatrix() const
{
    return matrixStack.top();
}

#endif
