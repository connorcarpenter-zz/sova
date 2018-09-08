#pragma once

//
// Created by connor on 7/9/18.
//
#include <Sova/References/Refable.h>

namespace Sova
{
    template<class T>
    class SortedListNode : public Refable
    {

    public:

        explicit SortedListNode(Ref<T> item, int sortKey)
        {
            this->item = item;
            this->sortKey = sortKey;
        }

        virtual const char* getClassName() { return "SortedListNode"; }

        Ref<T> item = Null<T>();
        Ref<SortedListNode<T>> next = Null<SortedListNode<T>>();
        int sortKey;
    };

    template<class T>
    class SortedListIterator : public Refable
    {
    public:

        explicit SortedListIterator(Ref<SortedListNode<T>> headNode)
        {
            this->currentNode = headNode;
        }

        virtual const char* getClassName() { return "SortedListIterator"; }

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

        Ref<SortedListNode<T>> currentNode = Null<SortedListNode<T>>();
    };

    template<class T>
    class SortedList : public Refable
    {
    public:

        SortedList() = default;
        virtual const char* getClassName() { return "SortedList"; }

        void Add(Ref<T> item, int sortKey)
        {
            Ref<SortedListNode<T>> newNode = New<SortedListNode<T>>(item, sortKey);

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
                size = 1;
            }
            else
            {
                //tail->next = newNode;
                //tail = newNode;

                if (head->sortKey < sortKey)
                {
                    auto lastHead = head;
                    head = newNode;
                    head->next = lastHead;
                    size += 1;
                    return;
                }


                auto previous = head;
                while (previous->next != nullptr && previous->next->sortKey >= sortKey)
                    previous = previous->next;

                if (previous->next == nullptr)
                {
                    // no sandwiching to be done here, add it to the end of the List
                    previous->next = newNode;
                    tail = newNode;
                    size += 1;

                    return;
                }

                auto nextNext = previous->next; //important that this is executed before the next line (idk why yet :/)
                previous->next = newNode;
                newNode->next = nextNext;
                size += 1;
                return;
            }
        }

        void Remove(Ref<T> removeItem)
        {
            if (head->item == removeItem)
            {
                if (head->next == nullptr)
                {
                    //there's only 1 node in this SortedList
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

            if (previous->next == nullptr)
            {
                // node is not in linked SortedList
                return;
            }

            //cut item out of the linked SortedList
            auto nextNext = previous->next->next; //important that this is executed before the next line (idk why yet :/)
            previous->next = nextNext;
            size -= 1;
        }

        void Resort(Ref<T> removeItem, int newDepth)
        {
            int previousSize = size;
            this->Remove(removeItem);
            this->Add(removeItem, newDepth);
            if(previousSize != size)
            {
                int i = 1/0;
            }
        }

        int Size() const
        {
            return size;
        }

        void Clear()
        {
            size = 0;
            head = Null<SortedListNode<T>>();
            tail = Null<SortedListNode<T>>();
            //GC should pick up abandoned SortedListNodes
        }

        Ref<SortedListIterator<T>> GetIterator()
        {
            return New<SortedListIterator<T>>(head);
        }

    private:

        Ref<SortedListNode<T>> head = Null<SortedListNode<T>>();
        Ref<SortedListNode<T>> tail = Null<SortedListNode<T>>();
        int size = 0;
    };
}