//
// Created by connor on 7/29/18.
//

#include "Color.h"

namespace Sova
{
    Color::Color(int red, int green, int blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    Color Color::Red = Color(255, 0, 0);
    Color Color::Green = Color(0, 255, 0);
    Color Color::Blue = Color(0, 0, 255);
    Color Color::White = Color(255, 255, 255);
    Color Color::Black = Color(0, 0, 0);
}