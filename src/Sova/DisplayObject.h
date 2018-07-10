#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include "Point.h"

namespace Sova {

    class DisplayObject : public virtual Refable
    {
    public:
        Ref<Point> position;
    private:
    };
    
}