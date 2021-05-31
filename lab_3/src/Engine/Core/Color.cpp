#include "Color.hpp"


Color::Color(int hex) noexcept
    : hex(hex)
{
}

Color::Color(int r, int g, int b, int a) noexcept
    : r(r), g(g), b(b), a(a)
{
}

Color::Color(const Color& color) noexcept
    : hex(color.hex)
{
}

unsigned char Color::getRed() const noexcept
{
    return r;
}

unsigned char Color::getGreen() const noexcept
{
    return g;
}

unsigned char Color::getBlue() const noexcept
{
    return b;
}

unsigned char Color::getAlpha() const noexcept
{
    return a;
}

unsigned int Color::getHex() const noexcept
{
    return hex;
}

void Color::setRed(unsigned char value) noexcept
{
    r = value;
}

void Color::setGreen(unsigned char value) noexcept
{
    g = value;
}

void Color::setBlue(unsigned char value) noexcept
{
    b = value;
}

void Color::setAlpha(unsigned char value) noexcept
{
    a = value;
}

void Color::setHex(unsigned int value) noexcept
{
    hex = value;
}
