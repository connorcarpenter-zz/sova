#pragma once

//
// Created by connor on 8/29/18.
//

#include <Sova/References/Refable.h>
#include <Sova/Common/String.h>

namespace Sova {
    class InternalTexture;

    class AnimatedSpriteInfo : public Refable {
    public:
        AnimatedSpriteInfo(Ref<Sova::String> fileName, bool autoSize, int anchorX, int anchorY);
        AnimatedSpriteInfo(Ref<Sova::String> fileName, int frameWidth, int frameHeight, int padding, int anchorX, int anchorY);

        Ref<Sova::String> filename = Null<Sova::String>();
        int frameWidth = frameWidth;
        int frameHeight = frameHeight;
        int padding = padding;
        int anchorX = anchorX;
        int anchorY = anchorY;
        bool autoSize = false;
        InternalTexture* internalTexture = nullptr;
    };
}