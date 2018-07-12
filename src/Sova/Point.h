#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Refable.h>

namespace Sova
{
    class Point : public Refable
    {
    public:
        Point();
        Point(int x, int y);
        void set(int x, int y);

        int x;
        int y;
    private:
    };
}