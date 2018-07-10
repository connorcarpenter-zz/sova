#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include <Sova/References/RefTypes.h>
#include "Point.h"

namespace Sova {

    class DisplayObject : public Refable
    {
    public:
        SovaBaseTypeDecl(DisplayObject);
        Ref<Point> position = NullRef<Point>();
    private:
    };
    
}