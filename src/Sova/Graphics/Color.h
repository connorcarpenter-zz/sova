#pragma once

//
// Created by connor on 7/29/18.
//

#include "Color.h"

namespace Sova
{
    class Color
    {
    public:
        static const Color Red = Color(255,0,0);
        static const Color Green = Color(0,255,0);
        static const Color Blue = Color(0,0,255);
        static const Color White = Color(255,255,255);
        static const Color Black = Color(0,0,0);
    private:
        Color(int red, int green, int blue);
        int red;
        int green;
        int blue;
    };
}
