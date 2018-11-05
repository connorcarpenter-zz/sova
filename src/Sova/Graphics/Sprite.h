#pragma once

//
// Created by connor on 7/8/18.
//

#include "Sova/Common/String.h"
#include "Container.h"
#include "AnimatedSpriteInfo.h"
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

        Color tint = Color::White;

        bool visible = false;

        virtual void setTexture(Ref <String> textureName);

        int getWidth();

        int getHeight();

        void useSpriteInfo(Ref<AnimatedSpriteInfo> animatedSpriteInfo);

    protected:
        InternalSprite* internalSprite;

        Ref<String> textureName = Null<String>();

        bool spriteInsideCameraBounds(Ref<Camera> camera, int xoffset, int yoffset);
    };
}