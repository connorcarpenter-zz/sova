//
// Created by connor on 7/8/18.
//

#include <Sova/References/Ref.h>
#include "Point.h"

namespace Sova {
    Point::Point() {
        this->x = 0;
        this->y = 0;
    }

    Point::Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void Point::set(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool Point::Equals(Ref<Sova::Point> other) {
        return (this->x == other->x && this->y == other->y);
    }
}