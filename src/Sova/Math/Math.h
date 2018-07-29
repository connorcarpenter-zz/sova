#pragma once

//
// Created by connor on 7/13/18.
//

namespace Sova
{
    class Math
    {
    public:
        static float Random();
        static float Random(float min, float max);
        static float Cos(float degrees);
        static float Sin(float degrees);
        static bool PointInBox(int pointX, int pointY, int boxX1, int boxY1, int boxX2, int boxY2);

        static int Abs(int value);

        static int Sign(int value);
        static int SignOrZero(int value);

        static float Lerp(int value1, int value2, float between);
    };
}