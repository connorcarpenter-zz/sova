//
// Created by connor on 7/8/18.
//

#include "Loader.h"
#include "Log.h"

namespace Sova
{
    Ref<Loader> Loader::onProgress(std::function<void(Ref<String>)> progressFunction) {
        this->progressFunction = progressFunction;
        return ThisRef<Loader>();
    }

    void Loader::onFinish(std::function<void()> finishFunction) {
        this->finishFunction = finishFunction;
        checkReadyToLoad();
    }

    void Loader::addResourcesToLoad(Ref<Array<Ref<String>>> resourcesToLoad) {
        //for (Ref<String> resource : resourcesToLoad){
        //    resourcesReadyToLoad->Add(resource);
        //}
    }

    void Loader::setAppLoaded() {
        this->appHasLoaded = true;
        checkReadyToLoad();
    }

    void Loader::checkReadyToLoad() {
        if (this->appHasLoaded && this->finishFunction != nullptr){
            loadAllResources();
        }
    }

    void Loader::loadAllResources(){
        //for (Ref<String> resourceString : resourcesReadyToLoad){
        //    loadResource(resourceString);
        //    if (this->progressFunction != nullptr){
        //        progressFunction(resourceString);
        //    }
        //}

        finishFunction();
    }

    void Loader::loadResource(Ref<String> resourcePath) {
        //Log::Info("loading resource: %s", resourcePath->AsCStr());
    }
}