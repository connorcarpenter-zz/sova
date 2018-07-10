#pragma once

//
// Created by Connor Carpenter on 12/14/17.
//

namespace Sova {

    class Log {
    public:
        static void Dbg(const char* msg, ...) __attribute__((format(printf, 1, 2)));
        static void Info(const char* msg, ...) __attribute__((format(printf, 1, 2)));
        static void Warn(const char* msg, ...) __attribute__((format(printf, 1, 2)));
        static void Error(const char* msg, ...) __attribute__((format(printf, 1, 2)));
    };
}