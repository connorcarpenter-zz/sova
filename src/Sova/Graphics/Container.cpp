//
// Created by connor on 7/8/18.
//

#include <Sova/Internal/InternalApp.h>
#include "Container.h"
#include "Sova/Math/Point.h"

namespace Sova
{
    Container::Container()
    {
        this->children = New<Sova::SortedVector<Container>>();
    }

    void Container::AddChild(Ref<Container> container)
    {
        this->children->Add(container);

        container->SetParent(ThisRef<Container>());
    }

    void Container::RemoveChild(Ref<Container> container)
    {
        this->children->Remove(container);

        container->SetParent(nullptr);
    }

    void Container::OnUpdate(std::function<void(float)> updateFunction)
    {
        this->UpdateFunction = updateFunction;
    }

    void Container::Update(float deltaFrameMs) {
        if (this->UpdateFunction != nullptr)
            this->UpdateFunction(deltaFrameMs);
    }

    void Container::UpdateChildren(float deltaFrameMs)
    {
        if (this->destroyed) return;

        for (auto iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            childContainer->Update(deltaFrameMs);
            childContainer->UpdateChildren(deltaFrameMs);
        }
    }

    bool sortFunction (Ref<Container>* a, Ref<Container>* b)
    {
        return (*a)->depth > (*b)->depth;
    }

    void Container::Draw(Ref<Camera> camera, int xoffset, int yoffset)
    {
        if (this->destroyed) return;

        this->drawSelf(camera, xoffset, yoffset);

        //Draw children
        this->children->resortIfNeeded(sortFunction);
        for (auto iterator = this->children->GetIterator(); iterator->Valid(); iterator->Next())
        {
            Ref<Container> childContainer = iterator->Get();
            childContainer->Draw(camera, xoffset + this->position->x, yoffset + this->position->y);
        }
    }

    void Container::SetParent(std::nullptr_t)
    {
        auto oldParent = this->parent;
        this->parent = nullptr;

        if (oldParent != nullptr)
        {
            oldParent->RemoveChild(ThisRef<Container>());
        }
    }

    void Container::SetParent(Ref<Container> newParent)
    {
        auto oldParent = this->parent;
        this->parent = newParent;

        if (oldParent != nullptr)
        {
            oldParent->RemoveChild(ThisRef<Container>());
        }
    }

    void Container::Destroy()
    {
        InternalApp::getInternalApp()->destructionManager.QueueForDestruction(this);
        this->UpdateFunction = nullptr;
        this->destroyed = true;
    }

    void Container::SetDepth(int newDepth) {
        if (newDepth != this->depth)
        {
            this->depth = newDepth;
            if (this->parent != nullptr) {
                this->parent->children->markForResort();
            }
        }
    }
}