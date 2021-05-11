#include "IRenderer.hpp"

IRenderer::IRenderer()
{
    matrixStack.push(Matrix::identity());
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

const Matrix& IRenderer::getMatrix() const
{
    return matrixStack.top();
}
