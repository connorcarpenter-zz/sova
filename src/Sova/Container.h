#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>
#include <Sova/References/Ref.h>
#include <Sova/References/RefTypes.h>
#include "DisplayObject.h"

namespace Sova {

    class Container : public DisplayObject {
    public:
        SovaTypeDecl(Container, DisplayObject);
        Container();
        void addChild(Ref<Container> container);
        void onUpdate(std::function<void()> updateFunction);
        void updateChildren();
    private:
    };

}