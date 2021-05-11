#pragma once

#define COLOR_BYTE_RED 0
#define COLOR_BYTE_GREEN 1
#define COLOR_BYTE_BLUE 2
#define COLOR_BYTE_ALPHA 3

#define COLOR_HEX_FROM_RGBA(r, g, b, a) \
    (((r) << COLOR_BYTE_RED) | ((g) << COLOR_BYTE_GREEN) | ((b) << COLOR_BYTE_BLUE) | ((a) << COLOR_BYTE_ALPHA))

#define COLOR_RED_FROM_HEX(h)   (((h) >> COLOR_BYTE_RED)   & 0xFF)
#define COLOR_GREEN_FROM_HEX(h) (((h) >> COLOR_BYTE_GREEN) & 0xFF)
#define COLOR_BLUE_FROM_HEX(h)  (((h) >> COLOR_BYTE_BLUE)  & 0xFF)
#define COLOR_ALPHA_FROM_HEX(h) (((h) >> COLOR_BYTE_ALPHA) & 0xFF)

#define COLOR_SET_BYTE(h, byte, val) (((h) & ~(0xFF << (byte))) | ((val) << byte))

class Color
{
public:
    Color(int hex = COLOR_HEX_FROM_RGBA(0x0, 0x0, 0x0, 0x0)) noexcept;
    Color(int r, int g, int b, int a) noexcept;
    Color(const Color& color) noexcept;

    int getRed() const noexcept;
    int getGreen() const noexcept;
    int getBlue() const noexcept;
    int getAlpha() const noexcept;
    int getHex() const noexcept;

    void setRed(int value) noexcept;
    void setGreen(int value) noexcept;
    void setBlue(int value) noexcept;
    void setAlpha(int value) noexcept;
    void setHex(int value) noexcept;

private:
    int hex;
};
