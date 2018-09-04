//
// Created by connor on 9/4/18.
//

#include <Modules/Resource/Id.h>
#include <Modules/Core/Containers/Buffer.h>
#include <Sova/References/Ref.h>
#include <Sova/Common/String.h>
#include "soloud_wav.h"

namespace Sova {
    class InternalSound {
    public:
        InternalSound();

        void updateAfterLoad();

        void play();

        bool loaded = false;
        SoLoud::Wav myWav;
        Oryol::Buffer myWavData;
    };
}