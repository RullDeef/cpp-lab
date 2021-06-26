#pragma once

#include "Core/Math/Vector.hpp"


class Vertex
{
public:
    constexpr Vertex() noexcept {}
    constexpr Vertex(double x, double y, double z)
        : x(x), y(y), z(z) {}

    inline constexpr double getX() const noexcept { return x; }
    inline constexpr double getY() const noexcept { return y; }
    inline constexpr double getZ() const noexcept { return z; }
    inline constexpr double getW() const noexcept { return w; }

    inline constexpr void setX(double value) noexcept { x = value; }
    inline constexpr void setY(double value) noexcept { y = value; }
    inline constexpr void setZ(double value) noexcept { z = value; }
    inline constexpr void setW(double value) noexcept { w = value; }

    inline operator Vector() const { return Vector(x, y, z); }

private:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double w = 1.0;
};
