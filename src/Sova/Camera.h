#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Refable.h>

namespace Sova
{
    template <class T> class Ref;
    class Viewport;
    class Container;

    class Camera : public Refable
    {
    public:
        Camera(int width, int height, Ref<Container> target);
        void draw(Ref<Viewport> viewport);
    private:
        int width;
        int height;
        Ref<Container> target = NullRef<Container>();
    };
}