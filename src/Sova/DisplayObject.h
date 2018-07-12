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
    class OryolDisplayObject;

    class DisplayObject : public Refable
    {
    public:
        SovaBaseTypeDecl(DisplayObject);
        DisplayObject();
        ~DisplayObject();
        void drawSelf(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera);

        Ref<Point> position = NullRef<Point>();
        Ref<String> textureName = NullRef<String>();
    private:

        OryolDisplayObject* oryolDisplayObject;
    };
}