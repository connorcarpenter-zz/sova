
//
// Created by connor on 7/13/18.
//

#include "glm/gtc/random.hpp"
#include "glm/trigonometric.hpp"

#include "Math.h"

namespace Sova
{
    float Math::Random()
    {
        return glm::linearRand(0.0f, 1.0f);
    }

    float Math::Random(float min, float max)
    {
        return glm::linearRand(min, max);
    }

    float Math::Cos(float degrees) {
        return glm::cos(glm::radians(degrees));
    }

    float Math::Sin(float degrees) {
        return glm::sin(glm::radians(degrees));
    }

    bool Math::PointInBox(int pointX, int pointY, int boxX1, int boxY1, int boxX2, int boxY2) {
        return (pointX >= boxX1 && pointX <= boxX2 && pointY >= boxY1 && pointY <= boxY2);
    }

    int Math::Abs(int value) {
        return value * Math::Sign(value);
    }

    int Math::Sign(int value) {
        if (value < 0)return -1;
        return 1;
    }

    float Math::Lerp(int value1, int value2, float between)
    {
        float range = (value2 - value1);
        return value1 + (range * between / 100);
    }

    int Math::SignOrZero(int value) {
        if (value == 0) return 0;
        return Math::Sign(value);
    }
}