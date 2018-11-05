#pragma once

//
// Created by connor on 8/29/18.
//

#include <Sova/References/Refable.h>
#include <Sova/Common/String.h>
#include "AnimatedSpriteInfo.h"

namespace Sova {
    class AnimatedSequenceInfo : public Refable {
    public:
        AnimatedSequenceInfo(Ref<Sova::AnimatedSpriteInfo> spriteInfo, int frameStart, int frameEnd);

        Ref<Sova::AnimatedSpriteInfo> spriteInfo = Null<Sova::AnimatedSpriteInfo>();
        int frameStart;
        int frameEnd;
    };
}