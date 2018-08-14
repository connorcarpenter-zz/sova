#pragma once

//
// Created by connor on 7/26/18.
//
#include "Sprite.h"

namespace Sova {
    class AnimatedSprite : public Sprite {
    public:
        SovaTypeDecl(AnimatedSprite, Sprite);
        virtual const char* getClassName() { return "AnimatedSprite"; }
        AnimatedSprite(Ref<String> textureName, int frameWidth, int frameHeight, int padding);

        AnimatedSprite();

        void Update(float deltaFrameMs) override;
        void drawSelf(Ref<Camera> camera, int xoffset, int yoffset) override;
        float imageSpeed = 0;
        float imageIndex = 0;
    private:
        int imageNumber = -1;

        bool getTextureLoaded();

    protected:
        int frameWidth = 0;
        int frameHeight = 0;
        int padding = 0;
    };
}