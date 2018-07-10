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
        Ref<DerivedObj> NewRef(ARGS&&... args) {
            Ref<DerivedObj> ref = Ref<DerivedObj>(this);
            ref.initObj(std::forward<ARGS>(args)...);
            return ref;
        }

        template<typename DerivedObj>
        Ref<DerivedObj> NullRef() {
            return Ref<DerivedObj>(this);
        }

        template<typename Obj>
        void addChild(Ref<Obj>* obj) {

            static_assert(std::is_base_of<Refable, Obj>{}, "Obj should inherit from Refable");

            children.insert(obj);
        }

        template<typename Obj>
        void removeChild(Ref<Obj>* obj) {

            static_assert(std::is_base_of<Refable, Obj>{}, "Obj should inherit from Refable");

            children.erase(obj);
        }

        // Get number of children
        int getNumberChildren() {
            return (int) children.size();
        }

        void mark(); // Mark the object and all its children as live
        void Hold();
        int Release();

        ~Refable();

        bool marked = false;
    private:
        RefCounter* refCounter = new RefCounter();
        std::set<IRef*> children;
    };
}
