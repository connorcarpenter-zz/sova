//
// Created by connor on 7/8/18.
//

#include "Loader.h"

namespace Sova
{
    Loader& Loader::onProgress(void (*progressFunction)()) {
        this->progressFunction = progressFunction;
        return *this;
    }

    void Loader::onFinish(void (*finishFunction)()) {
        this->finishFunction = finishFunction;
    }
}