#pragma once

//
// Created by connor on 7/9/18.
//

#include <cstddef>
#include "RefCounter.h"

namespace Sova
{
    template<class T> class Ref
    {
    public:

        //destructor
        ~Ref()
        {

        };

        // member variable declaration
        Ref()
        {

        };

        // copy constructor, happens when a method has a Ref as a parameter
        Ref(const Ref<T>& ref)
        {

        };;

        // move constructor, happens when a Ref is returned from a method
        Ref(Ref<T>&& ref)
        {

        };

        // null constructor
        Ref(std::nullptr_t)
        {

        };

        // copy assignment operator
        Ref<T>& operator = (const Ref<T>& ref)
        {

        };

        // move assignment operator
        void operator = (Ref<T>&& ref)
        {

        };

        // assign nullptr operator
        Ref<T>& operator = (std::nullptr_t)
        {

        };

        //arrow operator
        T* operator -> () const
        {

        };

    private:

        RefCounter* refCounter = nullptr;
        T* obj = nullptr;

        void release()
        {

        }
    };
}