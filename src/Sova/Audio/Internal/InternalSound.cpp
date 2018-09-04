//
// Created by connor on 9/4/18.
//

#include <Sova/Internal/InternalApp.h>
#include "InternalSound.h"
#include "soloud.h"

namespace Sova
{
    InternalSound::InternalSound()
    {

    }

    void InternalSound::updateAfterLoad()
    {
        this->loaded = true;
    }

    void InternalSound::play() {
        if (this->loaded) {
            InternalApp::getInternalApp()->soloud.play(this->myWav, 1.0);
        }
    }
}