#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Refable.h>

namespace Sova
{
    class FloatPoint : public Refable
    {
    public:
        FloatPoint();
        FloatPoint(float x, float y);
        virtual const char* getClassName() { return "FloatPoint"; }
        void set(float x, float y);
        bool Equals(Ref<FloatPoint> other);

        float x;
        float y;

        void set(Ref<FloatPoint> other);
    };
}