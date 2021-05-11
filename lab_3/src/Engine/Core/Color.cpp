#include "Color.hpp"

Color::Color(int r, int g, int b, int a) noexcept
    : hex(COLOR_HEX_FROM_RGBA(r, g, b, a))
{
}

Color::Color(const Color& color) noexcept
    : hex(color.hex)
{
}

Color::Color(int hex) noexcept
    : hex(hex)
{
}

int Color::getRed() const noexcept
{
    return COLOR_RED_FROM_HEX(hex);
}

int Color::getGreen() const noexcept
{
    return COLOR_GREEN_FROM_HEX(hex);
}

int Color::getBlue() const noexcept
{
    return COLOR_BLUE_FROM_HEX(hex);
}

int Color::getAlpha() const noexcept
{
    return COLOR_ALPHA_FROM_HEX(hex);
}

int Color::getHex() const noexcept
{
    return hex;
}

void Color::setRed(int value) noexcept
{
    hex = COLOR_SET_BYTE(hex, COLOR_BYTE_RED, value);
}

void Color::setGreen(int value) noexcept
{
    hex = COLOR_SET_BYTE(hex, COLOR_BYTE_GREEN, value);
}

void Color::setBlue(int value) noexcept
{
    hex = COLOR_SET_BYTE(hex, COLOR_BYTE_BLUE, value);
}

void Color::setAlpha(int value) noexcept
{
    hex = COLOR_SET_BYTE(hex, COLOR_BYTE_ALPHA, value);
}

void Color::setHex(int value) noexcept
{
    hex = value;
}
