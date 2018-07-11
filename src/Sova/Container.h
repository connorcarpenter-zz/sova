#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>
#include <Sova/References/Ref.h>
#include <Sova/References/RefTypes.h>
#include "DisplayObject.h"
#include "Common/List.h"
#include "Viewport.h"
#include "Camera.h"

namespace Sova
{
    class Container : public DisplayObject
    {
    public:

        SovaTypeDecl(Container, DisplayObject);
        Container();
        void addChild(Ref<Container> container);
        void onUpdate(std::function<void()> updateFunction);
        void updateChildren();
        std::function<void()> updateFunction = nullptr;

        void draw(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera);

    private:

        Ref<List<Container>> children = NullRef<List<Container>>();
    };

}