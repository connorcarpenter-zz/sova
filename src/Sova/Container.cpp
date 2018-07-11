//
// Created by connor on 7/8/18.
//

#include "Container.h"

namespace Sova
{
    Container::Container()
    {
        this->children = NewRef<List<Container>>();
    }

    void Container::addChild(Ref<Container> container)
    {
        this->children->Add(container);
    }

    void Container::onUpdate(std::function<void()> updateFunction)
    {
        this->updateFunction = updateFunction;
    }

    void Container::updateChildren()
    {
        for (Ref<ListIterator<Container>> iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            childContainer->updateFunction();
            childContainer->updateChildren();
        }
    }

    void Container::draw(int xoffset, int yoffset, Ref<Viewport> viewport, Ref<Camera> camera)
    {
        this->drawSelf(xoffset, yoffset, viewport, camera);

        //Draw children
        for (Ref<ListIterator<Container>> iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            childContainer->draw(xoffset, yoffset, viewport, camera);
        }
    }
}