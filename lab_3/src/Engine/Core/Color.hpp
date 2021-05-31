#pragma once


class Color
{
public:
    Color(int hex = 0x00000000) noexcept;
    Color(int r, int g, int b, int a) noexcept;
    Color(const Color& color) noexcept;

    unsigned char getRed() const noexcept;
    unsigned char getGreen() const noexcept;
    unsigned char getBlue() const noexcept;
    unsigned char getAlpha() const noexcept;
    unsigned int getHex() const noexcept;

    void setRed(unsigned char value) noexcept;
    void setGreen(unsigned char value) noexcept;
    void setBlue(unsigned char value) noexcept;
    void setAlpha(unsigned char value) noexcept;
    void setHex(unsigned int value) noexcept;

private:
    union
    {
        unsigned int hex;
        struct
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    };
};
