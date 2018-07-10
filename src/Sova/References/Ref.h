#pragma once

//
// Created by connor on 7/9/18.
//

#include <cstddef>
#include <assert.h>

#include "RefCounter.h"
#include "Refable.h"
#include "IRef.h"
#include "GarbageCollector.h"

namespace Sova
{
    template<class T>
    class Ref : public IRef
    {
        //static_assert(std::is_base_of<Refable, T>{}, "T must inherit from Refable");
        struct __nat {int __for_bool_;};
    public:

        //Legit constructor
        explicit Ref(Refable* newParent){
            assert(newParent != nullptr);
            this->parent = newParent;
            this->parent->addChild(this);
        }

        template<typename... ARGS>
        void initObj(ARGS&&... args){
            assert(obj == nullptr); //We should only call this when the Ptr is being initialized
            this->obj = new T(std::forward<ARGS>(args)...);
            this->obj->Hold();
            Sova::GarbageCollector::getGC()->addToHeap(this->obj);
        }

        void thisObj(T* newObj){
            assert(obj == nullptr); //We should only call this when the Ptr is being initialized
            this->obj = newObj;
            this->obj->Hold();
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
            set(ref.obj);
        };

        // copy-construct from Ptr<OTHER>
        template<class U> Ref(const Ref<U>& ref, typename std::enable_if<std::is_convertible<U*, T*>::value, __nat>::type = __nat())
        {
            set(static_cast<T*>(ref.getObj()));
        };

        // move constructor, happens when a Ref is returned from a method
        Ref(Ref<T>&& ref)
        {
            set(ref.obj);
        };

        // move constructor from Ptr<OTHER>
        template<class U> Ref(Ref<U>&& ref, typename std::enable_if<std::is_convertible<U*, T*>::value, __nat>::type = __nat())
        {
            set(static_cast<T*>(ref.getObj()));
        };

        // copy assignment operator
        Ref<T>& operator = (const Ref<T>& ref)
        {
            if (this != &ref) // Avoid self assignment
            {
                release();
                set(ref.obj);
            }
            return *this;
        };

        // copy-assign from compatible Ptr<OTHER>
        template<class U> void operator = (const Ref<U>& ref) {
            T* ref_p = static_cast<T*>(ref.getObj());
            if (ref_p != obj) {
                release();
                set(static_cast<T*>(ref_p));
            }
        };

        // move assignment operator
        void operator = (Ref<T>&& ref)
        {
            if (ref.obj != obj)
            {
                release();
                set(ref.obj);
            }
        };

        // move-assign from compatible Ptr<OTHER>
        template<class U> void operator = (Ref<U>&& ref) {
            T* ref_p = static_cast<T*>(ref.getObj());
            if (ref_p != obj) {
                release();
                set(ref_p);
                ref.obj = nullptr;
            }
        };

        // assign nullptr operator
        Ref<T>& operator = (std::nullptr_t)
        {
            release();
            return *this;
        };

        // arrow operator
        T* operator -> () const
        {
            assert(this->obj != nullptr);
            return this->obj;
        };

        // operator==
        template<class U> bool operator==(const Ref<U>& ref) const {
            return obj == ref.getObj();
        };
        
        // operator!=
        template<class U> bool operator!=(const Ref<U>& ref) const {
            return obj != ref.getObj();
        };

        // test if invalid (contains nullptr)
        bool operator==(std::nullptr_t) const {
            return nullptr == obj;
        };
        
        // test if valid (contains valid ptr)
        bool operator!=(std::nullptr_t) const {
            return nullptr != obj;
        };

        // cast to bool
        explicit operator bool() const {
            return nullptr != obj;
        };

        // cast to compatible type
        template<class U, class=typename std::enable_if<std::is_convertible<T*,U*>::value>::type> operator const Ref<U>&() const {
            return *(const Ref<U>*)this;
        };
        // unsafe downcast, this would require RTTI to make it runtime-safe
        template<class U> const Ref<U>& unsafeCast() const {
            return *(const Ref<U>*)this;
        };

        Refable* getObj() const {
            return static_cast<Refable*>(obj);
        }

        T* obj = nullptr;
        
    private:
        
        Refable* parent = nullptr;

        void release()
        {
            if (this->obj == nullptr) return;
            // Decrement the old reference count
            // if reference become zero delete the old data
            if (this->obj->Release() == 0){
                //std::cout << "Object reference deleted:" << this->obj << "\n";
                Sova::GarbageCollector::getGC()->removeFromHeap(this->obj);
                delete this->obj;
            }

            this->obj = nullptr;
        }

        void set(T* obj){
            this->obj = obj;
            if (this->obj != nullptr){
                this->obj->Hold();
            }
        }
    };
}