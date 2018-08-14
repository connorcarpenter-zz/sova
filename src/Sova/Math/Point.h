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
        virtual const char* getClassName() { return "Point"; }
        void set(int x, int y);
        bool Equals(Ref<Point> other);

        int x;
        int y;

        void set(Ref<Point> other);
    };
}