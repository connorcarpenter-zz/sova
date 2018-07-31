
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

    int Math::Min(int value1, int value2) {
        return (value1 < value2) ? value1 : value2;
    }

    int Math::Max(int value1, int value2) {
        return (value1 > value2) ? value1 : value2;
    }

    bool Math::BoxesOverlap(int box1a, int box1b, int box1c, int box1d, int box2a, int box2b, int box2c, int box2d)
    {
        int box1topleftx = Math::Min(box1a, box1c);
        int box1toplefty = Math::Min(box1b, box1d);
        int box1bottomrightx = Math::Max(box1a, box1c);
        int box1bottomrighty = Math::Max(box1b, box1d);

        int box2topleftx = Math::Min(box2a, box2c);
        int box2toplefty = Math::Min(box2b, box2d);
        int box2bottomrightx = Math::Max(box2a, box2c);
        int box2bottomrighty = Math::Max(box2b, box2d);

        if (box1topleftx > box2bottomrightx || box2topleftx > box1bottomrightx) return false;
        if (box1toplefty > box2bottomrighty || box2toplefty > box1bottomrighty) return false;
        return true;
    }

    int Math::Ceiling(float value) {
        return (int) glm::ceil(value);
    }

    float Math::Sqrt(int value) {
        return (float) glm::sqrt(value);
    }
}