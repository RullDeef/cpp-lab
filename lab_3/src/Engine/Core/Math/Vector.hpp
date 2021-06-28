#pragma once


class Vector
{
public:
    constexpr Vector(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0)
        : x(x), y(y), z(z), w(w) {}

    constexpr Vector(double vec[3])
        : x(vec[0]), y(vec[1]), z(vec[2]), w(1.0) {}

    constexpr Vector(const Vector& v)
        : x(v.x), y(v.y), z(v.z), w(v.w) {}

    constexpr double getX() const { return x; }
    constexpr double getY() const { return y; }
    constexpr double getZ() const { return z; }
    constexpr double getW() const { return w; }

    constexpr void setX(double val) { x = val; }
    constexpr void setY(double val) { y = val; }
    constexpr void setZ(double val) { z = val; }
    constexpr void setW(double val) { w = val; }

    constexpr Vector dir() const { return Vector(x, y, z, 0.0); }
    constexpr Vector wnorm() const { return Vector(x / w, y / w, z / w, 1.0); }

    constexpr Vector operator-() const { return Vector(-x, -y, -z, w); }
    constexpr Vector operator+(const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z, w + v.w); }
    constexpr Vector operator-(const Vector& v) const { return Vector(x - v.x, y - v.y, z - v.z, w - v.w); }
    constexpr Vector operator*(double val) const { return Vector(x * val, y * val, z * val, w * val); }
    constexpr Vector operator/(double val) const { return Vector(x / val, y / val, z / val, w / val); }

    double getLength() const;

    constexpr static Vector zero()      { return Vector( 0.0,  0.0,  0.0,  0.0); }
    constexpr static Vector up()        { return Vector( 0.0,  1.0,  0.0,  0.0); }
    constexpr static Vector down()      { return Vector( 0.0, -1.0,  0.0,  0.0); }
    constexpr static Vector left()      { return Vector(-1.0,  0.0,  0.0,  0.0); }
    constexpr static Vector right()     { return Vector( 1.0,  0.0,  0.0,  0.0); }
    constexpr static Vector forward()   { return Vector( 0.0,  0.0, -1.0,  0.0); }
    constexpr static Vector backward()  { return Vector( 0.0,  0.0,  1.0,  0.0); }

private:
    double x;
    double y;
    double z;
    double w;
};
