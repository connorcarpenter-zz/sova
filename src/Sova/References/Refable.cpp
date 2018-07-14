//
// Created by connor on 7/9/18.
//

#include "Refable.h"
#include "IRef.h"

namespace Sova
{
    void Refable::Mark()
    {
        if (!marked)
        {
            marked = true;
            for (auto it = refs.begin();
                 it != refs.end();
                 ++it) {
                Refable *obj = (*it)->getObj();
                if (obj != nullptr)
                    obj->Mark();
            }
        }
        else
        {
            //how is this happening?
            auto i = 0;
        }
    }

    void Refable::Hold() {
        refCounter->Hold();
    }

    int Refable::Release() {
        return refCounter->Release();
    }

    Refable::~Refable() {
        delete refCounter;
    }
}