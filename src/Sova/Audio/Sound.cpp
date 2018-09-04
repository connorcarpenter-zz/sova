//
// Created by connor on 9/4/18.
//

#include <Modules/Core/String/String.h>
#include <Sova/Internal/InternalApp.h>
#include "Sound.h"
#include "Internal/InternalSound.h"

namespace Sova {
    Sound::Sound(Ref<Sova::String> soundName){

        this->soundName = soundName;

        Oryol::String soundString = Oryol::String(soundName->AsCStr());
        this->internalSound = InternalApp::getInternalApp()->resourceManager.sounds[soundString];
    }

    void Sound::Play(){
        this->internalSound->play();
    }
}