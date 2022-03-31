#pragma once

#include <stdlib.h>

template<typename T>
struct Queue
{
    using Type = T;

    Type* Data;
    size_t Size;
    size_t Begin;
    size_t End;

    Queue()
        : Data(nullptr)
        , Size(0)
        , Begin(0)
        , End(0)
    {

    }

    void Init(size_t count)
    {
        Size = count;
        Data = (Type*)malloc(sizeof(Type) * count);
        memset(Data, 0, sizeof(Type) * count);
    }

    void Shutdown()
    {
        free(Data);
        Data = nullptr;
        Size = 0;
        Begin = 0;
        End = 0;
    }

    void Push(const Type& val)
    {
        Data[End] = val;
        End = (End + 1) % Size;
    }

    Type Pop()
    {
        Type& val = Data[Begin];
        Begin = (Begin + 1) % Size;
        return val;
    }
};
