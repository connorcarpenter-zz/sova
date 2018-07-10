#pragma once

//
// Created by connor on 7/9/18.
//

#include <cstddef>
#include <assert.h>

#include "RefCounter.h"
#include "Refable.h"
#include "IRef.h"

namespace Sova
{
    template<class T>
    class Ref : public IRef
    {
        static_assert(std::is_base_of<Refable, T>::value, "T must inherit from Refable");
    public:

        //Legit constructor
        explicit Ref(Refable* newParent){
            assert(this->parent != nullptr);
            this->parent = newParent;
            this->parent->addChild(this);
        }

        template<typename... ARGS>
        void initObj(ARGS&&... args){
            assert(obj == nullptr && refCounter == nullptr); //We should only call this when the Ptr is being initialized
            this->obj = new T(std::forward<ARGS>(args)...);
            this->refCounter = new RefCounter();
            this->refCounter->Hold();
            GarbageCollector::getGC()->addToHeap(this->obj);
        }

        //destructor
        ~Ref()
        {
            release();
            //remove self from parent's list of children
            if (this->parent != nullptr)
                this->parent->removeChild(this);
        };

        // copy constructor, happens when a method has a Ref as a parameter
        Ref(const Ref<T>& ref)
        {
            set(ref.obj, ref.refCounter);
        };

        // move constructor, happens when a Ref is returned from a method
        Ref(Ref<T>&& ref)
        {
            set(ref.obj, ref.refCounter);
        };

        // copy assignment operator
        Ref<T>& operator = (const Ref<T>& ref)
        {
            if (this != &ref) // Avoid self assignment
            {
                release();
                set(ref.obj, ref.refCounter);
            }
            return *this;
        };

        // move assignment operator
        void operator = (Ref<T>&& ref)
        {
            if (ref.obj != obj)
            {
                release();
                set(ref.obj, ref.refCounter);
            }
        };

        // assign nullptr operator
        Ref<T>& operator = (std::nullptr_t)
        {
            release();
            this->obj = nullptr;
            this->refCounter = nullptr;
            return *this;
        };

        //arrow operator
        T* operator -> () const
        {
            assert(this->obj != nullptr);
            return this->obj;
        };

        Refable* getRefable(){
            return static_cast<Refable*>(obj);
        }

    private:

        T* obj = nullptr;
        Refable* parent = nullptr;
        RefCounter* refCounter = nullptr;

        void release()
        {
            if (this->obj == nullptr || this->refCounter == nullptr) return;
            // Decrement the old reference count
            // if reference become zero delete the old data
            if (this->refCounter->Release() == 0){
                //std::cout << "Object reference deleted:" << this->obj << "\n";
                Sova::GarbageCollector::getGC()->removeFromHeap(this->obj);
                delete this->obj;
                delete this->refCounter;
                this->obj = nullptr;
                this->refCounter = nullptr;
            }
        }

        void set(T* obj, RefCounter* rc){
            this->obj = obj;
            if (this->obj != nullptr){
                this->refCounter = rc;
                if (this->refCounter != nullptr)
                    this->refCounter->Hold();
            }
        }
    };
}