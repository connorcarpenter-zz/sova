#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>

namespace Sova
{
    class Loader
    {
    public:
        Loader& onProgress(std::function<void()> progressFunction);
        void onFinish(std::function<void()> finishFunction);
    private:
        std::function<void()> progressFunction = nullptr;
        std::function<void()> finishFunction = nullptr;
    };
}
