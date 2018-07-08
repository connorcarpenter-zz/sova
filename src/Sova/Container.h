#pragma once

//
// Created by connor on 7/8/18.
//

#include "DisplayObject.h"

namespace Sova {

    class Container : public DisplayObject {
    public:
        Container();
        void addChild(const Container& container);
        void onUpdate(void (*updateFunction)());
        void updateChildren();
    private:
    };

}