#pragma once

//
// Created by connor on 7/8/18.
//

#include "Sova/Common/String.h"
#include "Container.h"
#include <Sova/References/RefTypes.h>

using namespace Sova;

namespace Sova
{
    class InternalSprite;

    class Sprite : public Container
    {
    public:
        SovaTypeDecl(Sprite, Container);
        Sprite();
        explicit Sprite(Ref<String> textureName);
        ~Sprite();
        virtual const char* getClassName() { return "Sprite"; }
        virtual void drawSelf(Ref<Camera> camera, int xoffset, int yoffset);

        Ref<Point> anchor = Null<Point>();

    protected:
        InternalSprite* internalSprite;

        virtual void setTexture(Ref <String> textureName);

        Ref<String> textureName = Null<String>();

        int getWidth();

        int getHeight();

        bool getVisible();

        void setVisible(bool visible);

        bool spriteInsideCameraBounds(Ref<Camera> camera, int xoffset, int yoffset);
    };
}