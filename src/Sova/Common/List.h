#pragma once

//
// Created by connor on 7/9/18.
//
#include <Sova/References/Refable.h>
//#include <Modules/Core/Assertion.h>
#include <functional>

namespace Sova
{
    template<class T>
    class ListNode : public Refable
    {

    public:

        explicit ListNode(Ref<T> item)
        {
            this->item = item;
        }

        virtual const char* getClassName() { return "ListNode"; }

        Ref<T> item = Null<T>();
        Ref<ListNode<T>> next = Null<ListNode<T>>();
    };

    template<class T>
    class ListIterator : public Refable
    {
    public:

        explicit ListIterator(Ref<ListNode<T>> headNode)
        {
            this->currentNode = headNode;
        }

        virtual const char* getClassName() { return "ListIterator"; }

        Ref<T> Get()
        {
            return currentNode->item;
        }

        void Next()
        {
            this->currentNode = this->currentNode->next;
        }

        bool Valid()
        {
            return (this->currentNode != nullptr);
        }

    private:

        Ref<ListNode<T>> currentNode = Null<ListNode<T>>();
    };

    template<class T>
    class List : public Refable
    {
    public:

        virtual const char* getClassName() { return "List"; }

        List() = default;

        void Add(Ref<T> item)
        {
            Ref<ListNode<T>> newNode = New<ListNode<T>>(item);

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
                size = 1;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
                size += 1;
            }
        }

        void Remove(Ref<T> removeItem)
        {
            if (size <= 0) return;
            if (head != nullptr) {
                if (head->item == removeItem) {
                    if (head->next == nullptr) {
                        //there's only 1 node in this list
                        head = nullptr;
                        tail = nullptr;
                        size = 0;
                        return;
                    }

                    auto headNext = head->next; //important that this is executed before the next line (idk why yet :/)
                    head = headNext;
                    size -= 1;
                    return;
                }


                auto previous = head;
                while (previous->next != nullptr && previous->next->item != removeItem)
                    previous = previous->next;

                if (previous->next == nullptr) {
                    // node is not in linked list
                    return;
                }

                //cut item out of the linked list
                auto nextNext = previous->next->next; //important that this is executed before the next line (idk why yet :/)
                previous->next = nextNext;
                if (nextNext == nullptr) {
                    //we just cut out the tail, so reassign it
                    tail = previous;
                }
                size -= 1;
            }
        }

        int Size() const
        {
            return size;
        }

        void Clear()
        {
            size = 0;
            head = Null<ListNode<T>>();
            tail = Null<ListNode<T>>();
            //GC should pick up abandoned ListNodes
        }

        Ref<ListIterator<T>> GetIterator()
        {
            return New<ListIterator<T>>(head);
        }

        Ref<T> At(int index)
        {
            if(index >= size)return Null<T>();
            if (index == 0) return head->item;
            if (index == size-1) return tail->item;

            int count = 0;
            for (Ref<ListIterator<T>> iterator = this->GetIterator(); iterator->Valid(); iterator->Next())
            {
                if (count == index)
                    return iterator->Get();
                count += 1;
            }

            //Should never arrive here..
            //assert(false);
            int i = 1/0;
        }

        Ref<T> Find(std::function<bool(Sova::Ref<T>)> evalFunc)
        {
            for (Ref<ListIterator<T>> iterator = this->GetIterator(); iterator->Valid(); iterator->Next())
            {
                auto evaledObj = iterator->Get();
                if (evalFunc(evaledObj)) return evaledObj;
            }

            return Null<T>();
        }

        bool Contains(Ref<T> item)
        {
            auto foundItem = this->Find([&](Ref<T> inspectUnit) { //replace this with a Hash lookup someday!
                return (inspectUnit.obj == item.obj);
            });
            return foundItem != nullptr;
        }

        List(Ref<List<T>> otherList)
        {
            for (Ref<ListIterator<T>> iterator = otherList->GetIterator(); iterator->Valid(); iterator->Next())
            {
                auto otherItem = iterator->Get();
                this->Add(otherItem);
            }
        }

    private:

        Ref<ListNode<T>> head = Null<ListNode<T>>();
        Ref<ListNode<T>> tail = Null<ListNode<T>>();
        int size = 0;
    };
}