//
// Created by Connor Carpenter on 12/14/17.
//

//Oryol references
#include "Core/Log.h"

//Sova references
#include "Log.h"

using namespace Sova;
using namespace Oryol;

namespace Sova {
    void
    Sova::Log::Dbg(const char* msg, ...) {
        va_list args;
        Oryol::Log::Dbg(msg, args);
    }

    void
    Sova::Log::Info(const char* msg, ...) {
        va_list args;
        Oryol::Log::Dbg(msg, args);
    }

    void
    Sova::Log::Warn(const char* msg, ...) {
        va_list args;
        Oryol::Log::Dbg(msg, args);
    }

    void
    Sova::Log::Error(const char* msg, ...) {
        va_list args;
        Oryol::Log::Dbg(msg, args);
    }
}

