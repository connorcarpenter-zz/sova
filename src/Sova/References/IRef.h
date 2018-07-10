#pragma once

//
// Created by connor on 7/9/18.
//

class Refable;
namespace Sova
{
    class IRef
    {
    public:
        virtual Refable* getRefable() = 0;
    };
}