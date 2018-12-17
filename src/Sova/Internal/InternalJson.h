#pragma once

//
// Created by connor on 12/16/18.
//

#include <cJSON.h>
#include <Modules/Core/Containers/Buffer.h>

namespace Sova {
    class InternalJson {
    public:
        InternalJson();
        ~InternalJson();
        void loadJson(const Oryol::Buffer& buffer);

        cJSON* json = nullptr;

        static cJSON *get(cJSON *jsonObj, const char *propStr);

        bool loaded = false;
    };
}
