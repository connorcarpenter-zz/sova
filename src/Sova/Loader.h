#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>
#include <Sova/References/Ref.h>
#include <Sova/Common/String.h>
#include <Sova/Common/Array.h>

namespace Sova
{
    class Loader : public Refable
    {
    public:
        Ref<Loader> onProgress(std::function<void(Ref<String>)> progressFunction);
        void onFinish(std::function<void()> finishFunction);

        void addResourcesToLoad(Ref<Array<Ref<String>>> resourcesToLoad);
        void setAppLoaded();

    private:
        void loadAllResources();
        void loadResource(Ref<String> resourcePath);
        void checkReadyToLoad();

        std::function<void(Ref<String>)> progressFunction = nullptr;
        std::function<void()> finishFunction = nullptr;
        bool appHasLoaded = false;
        Ref<Array<Ref<String>>> resourcesReadyToLoad = NullRef<Array<Ref<String>>>();
    };
}
