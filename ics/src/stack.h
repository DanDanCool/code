#pragma once

#include <stdlib.h>

template<typename T>
struct Stack
{
    using Type = T;

    Type* Data;
    size_t Size;
    size_t Index;

    Stack()
        : Data(nullptr)
        , Size(0)
        , Index(0)
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
        Index = 0;
    }

    void Push(const Type& val)
    {
        Data[Index] = val;
        Index++;
    }

    Type Pop(const Type& val)
    {
        return Data[--Index];
    }

    Type& Peek()
    {
        return Data[Index - 1];
    }
}
