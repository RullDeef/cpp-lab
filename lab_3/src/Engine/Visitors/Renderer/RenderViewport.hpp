#pragma once

#include "Core/Math/Rect.hpp"


class RenderViewport
{
public:
    virtual ~RenderViewport() = default;

    virtual Rect getViewportRect() const = 0;

    virtual void clear() = 0;
    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
};
