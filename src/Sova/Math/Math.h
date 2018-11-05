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

        static int Min(int value1, int value2);
        static int Max(int value1, int value2);
        static int Ceiling(float value);
        static int Floor(float value);
        static float Sqrt(int value);

        static bool BoxesOverlap(int box1a, int box1b, int box1c, int box1d, int box2a, int box2b, int box2c, int box2d);

        static int Power(int value, int power);

        static float Distance(float x1, float y1, float x2, float y2);
        static float Direction(float x1, float y1, float x2, float y2);

        static float PowerFloat(float value, float power);

        static float SqrtFloat(float value);
    };
}