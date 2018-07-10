//
// Created by connor on 7/9/18.
//

#include "Refable.h"
#include "IRef.h"

namespace Sova
{
    void Refable::mark()
    {
        marked = true;
        for (auto it = children.begin();
             it != children.end();
             ++it) {
            Refable* obj = (*it)->getObj();
            if (obj != nullptr)
                obj->mark();
        }
    }
}