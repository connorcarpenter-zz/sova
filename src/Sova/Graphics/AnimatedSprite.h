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
        void Update() override;
        void drawSelf(Ref<Camera> camera, int xoffset, int yoffset) override;

    private:
        int frameWidth = 0;
        int frameHeight = 0;
        int padding = 0;
        float imageSpeed = 0.1f;
        float imageIndex = 0;
        int imageNumber = -1;
    };
}