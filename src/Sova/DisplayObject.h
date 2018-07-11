#pragma once

//
// Created by connor on 7/8/18.
//

#include <Sova/References/Ref.h>
#include <Sova/References/Refable.h>
#include <Sova/References/RefTypes.h>

namespace Sova
{
    class Viewport;
    class Camera;
    class Point;
    class String;

    class DisplayObject : public Refable
    {
    private:
        //template <class T> class Ref;

    public:
        SovaBaseTypeDecl(DisplayObject);
        DisplayObject();
        void drawSelf(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera);

        Ref<Point> position = NullRef<Point>();
        Ref<String> textureName = NullRef<String>();
    };
}