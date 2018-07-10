//
// Created by connor on 7/9/18.
//

#include "RefCounter.h"

namespace Sova {

    void RefCounter::Hold() {
        count++;
    }

    int RefCounter::Release() {
        return --count;
    }
}