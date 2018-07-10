#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Refable.h>

namespace Sova
{
    class Point : public virtual Refable
    {
    public:
        void set(int x, int y);

        int x;
        int y;
    private:
    };
}