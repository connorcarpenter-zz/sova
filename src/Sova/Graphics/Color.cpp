//
// Created by connor on 7/29/18.
//

#include "Color.h"

namespace Sova
{
    Color::Color(int red, int green, int blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    Color Color::Red = Color(255, 0, 0);
    Color Color::Green = Color(0, 255, 0);
    Color Color::Blue = Color(0, 0, 255);
    Color Color::White = Color(255, 255, 255);
    Color Color::Black = Color(0, 0, 0);
    Color Color::LightGray = Color(192, 192, 192);
    Color Color::Gray = Color(128, 128, 128);
    Color Color::DarkGray = Color(64, 64, 64);
    Color Color::Brown = Color(128, 64, 0);

    bool Color::operator==(const Color &other) const
    {
        return (this->red == other.red && this->blue == other.blue && this->green == other.green);
    }

    bool Color::operator!=(const Color &other) const
    {
        return (this->red != other.red || this->blue != other.blue || this->green != other.green);
    }

    Color Color::MixColors(Color color1, Color color2) {
        int red = (color1.red*color2.red) / 255;
        int blue = (color1.blue*color2.blue) / 255;
        int green = (color1.green*color2.green) / 255;
        return Color(red,
                     blue,
                     green);
    }
}