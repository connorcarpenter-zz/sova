//
// Created by connor on 7/29/18.
//

#include "Rectangle.h"

namespace Sova
{

    Rectangle::Rectangle(int width, int height) {
        this->size = New<Point>(width, height);
    }
}