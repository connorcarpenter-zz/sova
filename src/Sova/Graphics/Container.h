#pragma once

//
// Created by connor on 7/8/18.
//

#include <functional>
#include <Sova/References/Ref.h>
#include <Sova/References/RefTypes.h>
#include "DisplayObject.h"
#include "Sova/Common/SortedList.h"
#include "Viewport.h"
#include "Camera.h"

namespace Sova
{
    class Container : public DisplayObject
    {
    public:

        SovaTypeDecl(Container, DisplayObject);
        Container();
        virtual const char* getClassName() { return "Container"; }
        void AddChild(Ref<Container> container);
        void RemoveChild(Ref<Container> container);

        void OnUpdate(std::function<void()> updateFunction);
        void UpdateChildren();
        std::function<void()> UpdateFunction = nullptr;

        virtual void Draw(Ref<Camera> camera, int xoffset, int yoffset);

        void Destroy();

        void SetParent(Ref<Container> newParent);
        void SetParent(std::nullptr_t);

        void SetDepth(int depth);

    private:
        int depth = 0;
        Ref<Container> parent = Null<Container>();
        Ref<SortedList<Container>> children = Null<SortedList<Container>>();
    protected:
        bool destroyed = false;

        virtual void Update();
    };

}