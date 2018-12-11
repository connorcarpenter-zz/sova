//
// Created by connor on 8/29/18.
//

#include "AnimatedSequenceInfo.h"

namespace Sova
{
    AnimatedSequenceInfo::AnimatedSequenceInfo(Ref<Sova::AnimatedSpriteInfo> spriteInfo, int frameStart, int frameEnd) {
        this->spriteInfo = spriteInfo;
        this->frameStart = frameStart;
        this->frameEnd = frameEnd;
    }

    AnimatedSequenceInfo::AnimatedSequenceInfo(Ref<Sova::AnimatedSpriteInfo> spriteInfo, int frameStart, int frameEnd,
                                               int newAnchorX, int newAnchorY) {
        this->spriteInfo = spriteInfo;
        this->frameStart = frameStart;
        this->frameEnd = frameEnd;
        this->newAnchorSet = true;
        this->newAnchorX = newAnchorX;
        this->newAnchorY = newAnchorY;
    }
}
