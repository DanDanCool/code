#pragma once

#include <stdlib.h>

template<typename T>
struct Queue
{
    using Type = T;

    Type* Memory;
    size_t Size;
    size_t Begin;
    size_t End;

    Queue()
        : Memory(nullptr)
        , Size(0)
        , Begin(0)
        , End(0)
    {

    }

    void Init(size_t count)
    {
        Size = count;
        Memory = (Type*)malloc(sizeof(Type) * count);
        memset(Memory, 0, sizeof(Type) * count);
    }

    void Shutdown()
    {
        free(Memory);
        Memory = nullptr;
        Size = 0;
        Begin = 0;
        End = 0;
    }

    void Push(const Type& val)
    {
        Memory[End] = val;
        End = (End + 1) % Size;
    }

    Type Pop()
    {
        Type& val = Memory[Begin];
        Begin = (Begin + 1) % Size;
        return val;
    }
};
