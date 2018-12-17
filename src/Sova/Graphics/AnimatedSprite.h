#pragma once

//
// Created by connor on 7/26/18.
//
#include "Sprite.h"

namespace Sova {
    class AnimatedSpriteInfo;
    class AnimatedSequenceInfo;

    enum AnimationEndBehavior { Loop, Stop };

    class AnimatedSprite : public Sprite {
    public:
        SovaTypeDecl(AnimatedSprite, Sprite);
        virtual const char* getClassName() { return "AnimatedSprite"; }
        AnimatedSprite(Ref<String> textureName, int frameWidth, int frameHeight, int padding);
        AnimatedSprite(Ref<SpriteAtlas> spriteAtlas, Ref<String> textureName, int frameWidth, int frameHeight, int padding);
        AnimatedSprite();

        void Update(float deltaFrameMs) override;
        void drawSelf(Ref<Camera> camera, int xoffset, int yoffset) override;
        void useAnimatedSpriteInfo(Ref<AnimatedSpriteInfo> animatedSpriteInfo);
        void useAnimatedSequenceInfo(Ref<Sova::AnimatedSequenceInfo> animatedSequenceInfo);
        float imageSpeed = 0;
        float imageIndex = 0;
        int frameWidth = 0;
        int frameHeight = 0;
        int padding = 0;
        int frameStartIndex = 0;
        AnimationEndBehavior animationEndBehavior = Loop;
        int imageNumber = -1;
    private:

        bool getTextureLoaded();

        int frameEndIndex = 0;
    };
}