#pragma once

//
// Created by connor on 9/4/18.
//

#include <Sova/References/Refable.h>
#include <Sova/References/Ref.h>
#include <Sova/Common/String.h>

namespace Sova {

    class InternalSound;

    class Sound : public Refable {
    public:
        explicit Sound(Ref<Sova::String> soundName);
        void Play();
        void PlayAndDisable();
        void Enable();
        Ref<String> soundName = Null<String>();
    private:
        InternalSound* internalSound = nullptr;
        bool enabled = true;
    };
}