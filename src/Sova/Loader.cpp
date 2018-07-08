//
// Created by connor on 7/8/18.
//

#include "Loader.h"

namespace Sova
{
    Loader& Loader::onProgress(std::function<void()> progressFunction) {
        this->progressFunction = progressFunction;
        return *this;
    }

    void Loader::onFinish(std::function<void()> finishFunction) {
        this->finishFunction = finishFunction;
    }
}