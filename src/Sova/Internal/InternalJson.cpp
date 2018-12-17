//
// Created by connor on 12/16/18.
//

#include <cstring>
#include "InternalJson.h"


namespace Sova {

    InternalJson::InternalJson() {

    }

    InternalJson::~InternalJson() {
        if (loaded)
            delete json;
    }

    void InternalJson::loadJson(const Oryol::Buffer &buffer) {
        loaded = true;
        this->json = cJSON_Parse((char*) buffer.Data());
    }

    cJSON *InternalJson::get(cJSON *jsonObj, const char *propStr) {
        if (jsonObj == nullptr) return nullptr;
        cJSON* curChild = jsonObj->child;
        while (true)
        {
            if (curChild == nullptr) break;
            if (strcmp(curChild->string, propStr) == 0)
                return curChild;

            curChild = curChild->next;
        }
        return nullptr;
    }
}