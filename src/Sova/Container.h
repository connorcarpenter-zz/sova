#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>
#include "DisplayObject.h"

namespace Sova {

    class Container : public DisplayObject {
    public:
        Container();
        void addChild(const Container& container);
        void onUpdate(std::function<void()> updateFunction);
        void updateChildren();
    private:
    };

}