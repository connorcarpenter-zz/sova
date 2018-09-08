//
// Created by connor on 7/8/18.
//

#include <Sova/References/Ref.h>
#include "FloatPoint.h"

namespace Sova {
    FloatPoint::FloatPoint() {
        this->x = 0;
        this->y = 0;
    }

    FloatPoint::FloatPoint(float x, float y) {
        this->x = x;
        this->y = y;
    }

    void FloatPoint::set(float x, float y) {
        this->x = x;
        this->y = y;
    }

    bool FloatPoint::Equals(Ref<Sova::FloatPoint> other) {
        return (this->x == other->x && this->y == other->y);
    }

    void FloatPoint::set(Ref<FloatPoint> other) {
        this->x = other->x;
        this->y = other->y;

    }
}