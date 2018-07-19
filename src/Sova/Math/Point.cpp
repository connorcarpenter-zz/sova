//
// Created by connor on 7/8/18.
//

#include "Point.h"

Sova::Point::Point() {
    this->x = 0;
    this->y = 0;
}

Sova::Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

void Sova::Point::set(int x, int y) {
    this->x = x;
    this->y = y;
}