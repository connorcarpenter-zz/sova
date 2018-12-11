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
        static Color Yellow;
        static Color White;
        static Color Black;
        static Color Brown;
        static Color LightGray;
        static Color Gray;
        static Color DarkGray;

        bool operator!=(const Color& other) const;
        bool operator==(const Color& other) const;

        int red;
        int green;
        int blue;

        static Color MixColors(Color color1, Color color2);
    };
}
