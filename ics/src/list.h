#pragma once

#include "memarena.h"

template<typename T>
struct List
{
    using Type = T;

    struct Node
    {
        Node* Next;
        Type Val;
    };

    Node* First;
    Node* Last;
    Arena Data;

    List()
        : Data()
        , First(nullptr)
        , Last(nullptr)
    {

    }

    void Init(size_t count)
    {
        Data.Init(sizeof(Node), count + 1);
        First = (Node*)Data.Mem;
        Last = (Node*)Data.Alloc();
    }

    void Shutdown()
    {
        Data.Shutdown();
        First = nullptr;
        Last = nullptr;
    }

    void Add(const Type& val)
    {
        Last->Val = val;
        Last->Next = (Node*)Data.Allocate();
        Last = Last->Next;
    }

    void Resize(size_t count)
    {
        Data.Resize(count + 1);
    }
};
