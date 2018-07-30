//
// Created by connor on 7/8/18.
//

#include <Sova/Internal/InternalApp.h>
#include "Loader.h"
#include "Log.h"

namespace Sova
{
    Ref<Loader> Loader::onProgress(std::function<void(Ref<String>)> progressFunction)
    {
        this->progressFunction = progressFunction;
        return ThisRef<Loader>();
    }

    void Loader::onFinish(std::function<void()> finishFunction)
    {
        this->finishFunction = finishFunction;
        checkReadyToLoad();
    }

    void Loader::addResourcesToLoad(Ref<List<String>> resourcesToLoad)
    {
        for (Ref<ListIterator<String>> iterator = resourcesToLoad->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<String> resource = iterator->Get();
            this->resourcesReadyToLoad->Add(resource);
        }
    }

    void Loader::setAppLoaded()
    {
        this->appHasLoaded = true;
        checkReadyToLoad();
    }

    void Loader::checkReadyToLoad()
    {
        if (this->appHasLoaded && this->finishFunction != nullptr)
        {
            loadAllResources();
        }
    }

    void Loader::loadAllResources()
    {
        for (Ref<ListIterator<String>> iterator = this->resourcesReadyToLoad->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<String> resourceString = iterator->Get();
            loadResource(resourceString);
            if (this->progressFunction != nullptr)
            {
                progressFunction(resourceString);
            }
        }

        this->resourcesReadyToLoad = Null<List<String>>();
        this->finishFunction();
    }

    void Loader::loadResource(Ref<String> resourcePath)
    {
        InternalApp::getInternalApp()->resourceManager.loadResource(resourcePath);
    }
}