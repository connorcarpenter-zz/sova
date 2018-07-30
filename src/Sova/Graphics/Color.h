#pragma once

//
// Created by connor on 7/29/18.
//

namespace Sova
{
    class Color
    {
    public:
        Color(int red, int green, int blue);
        static Color Red;
        static Color Green;
        static Color Blue;
        static Color White;
        static Color Black;

        int red;
        int green;
        int blue;
    };
}
