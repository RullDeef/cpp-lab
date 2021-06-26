#pragma once

#include <memory>
#include "Core/Color.hpp"
#include "API/Objects/IObjectVisitor.hpp"


class IRenderer : public IObjectVisitor
{
public:
    virtual ~IRenderer() = default;

    virtual Rect getViewport() = 0;

    virtual void beginFrame(ICamera* camera) = 0;
    virtual void endFrame() = 0;

    virtual void clear(const Color& color) = 0;
};
