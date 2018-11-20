#pragma once

//
// Created by connor on 7/9/18.
//

#include <set>
#include <utility>
#include "RefCounter.h"

namespace Sova
{
    class IRef;
    template<class T> class Ref;

    class Refable
    {
    public:
        template<typename DerivedObj, typename... ARGS>
        Ref<DerivedObj> New(ARGS &&... args) {
            Ref<DerivedObj> ref = Ref<DerivedObj>(this);
            ref.initObj(std::forward<ARGS>(args)...);
            return ref;
        }

        template<typename DerivedObj>
        Ref<DerivedObj> Null() {
            return Ref<DerivedObj>(this);
        }

        template<typename DerivedObj>
        Ref<DerivedObj>* NullPtr() {
            return new Ref<DerivedObj>(this);
        }

        template<typename DerivedObj>
        Ref<DerivedObj> ThisRef() {

            if(this->refCounter->count == 0){
                //if this triggers, it means you used a ThisRef<>() call inside a constructor, for complicated reasons, let's just not do this
                int i = 1/0;
            }

            Ref<DerivedObj> ref = Ref<DerivedObj>(this);
            ref.thisObj(static_cast<DerivedObj*>(this));

            return ref;
        }

        template<typename Obj>
        void addRef(Ref<Obj>* obj) {

            //static_assert(std::is_base_of<Refable, Obj>{}, "Obj should inherit from Refable");

            refs.insert(obj);
        }

        template<typename Obj>
        void removeRef(Ref<Obj>* obj) {

            //static_assert(std::is_base_of<Refable, Obj>{}, "Obj should inherit from Refable");
            refs.erase(obj);
        }

        // Get number of children
        int getNumberRefs() {
            return (int) refs.size();
        }

        virtual void Mark(); // Mark the object and all its children as live
        void Hold();
        int Release();
        virtual const char* getClassName();

        virtual ~Refable();

        bool marked = false;
    private:
        RefCounter* refCounter = new RefCounter();
        std::set<IRef*> refs;
    };
}
