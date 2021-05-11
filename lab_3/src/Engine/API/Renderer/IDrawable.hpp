#pragma once

#include <memory>
#include "IRenderer.hpp"

class IDrawable
{
public:
    virtual void draw(std::shared_ptr<IRenderer> renderer) const = 0;
};
