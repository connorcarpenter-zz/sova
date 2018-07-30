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
    public:
        SovaBaseTypeDecl(DisplayObject);
        DisplayObject();
        virtual const char* getClassName() { return "DisplayObject"; }
//        ~DisplayObject();
        virtual void drawSelf(Ref<Camera> camera, int xoffset, int yoffset);

        Ref<Point> position = Null<Point>();
        Ref<Point> scale = Null<Point>();
//        int getWidth();
//        int getHeight();
//        bool getVisible();
//        void setVisible(bool visible);

    protected:

    };
}