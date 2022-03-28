#include <stdlib.h>
#include <string.h>

#include "memarena.h"

Handle::Handle()
    : Index(UINT32_MAX)
{

}

Handle& Handle::operator=(uint32_t handle)
{
    Index = handle;
    return *this;
}

Handle& Handle::operator+=(const Handle& handle)
{
    Index += handle.Index;
    return *this;
}

Handle& Handle::operator+=(uint32_t handle)
{
    Index += handle;
    return *this;
}

Handle& Handle::operator-=(const Handle& handle)
{
    Index -= handle.Index;
    return *this;
}

Handle& Handle::operator-=(uint32_t handle)
{
    Index -= handle;
    return *this;
}

operator Handle::bool()
{
    return Index != UINT32_MAX;
}

Handle operator+(const Handle& h1, const Handle& h2)
{
    return Handle{ h1.Index + h2.Index };
}

Handle operator+(uint32_t h1, const Handle& h2)
{
    return Handle{ h1 + h2.Index };
}

Handle operator+(const Handle& h1, uint32_t h2)
{
    return Handle{ h1.Index + h2 };
}

Handle operator-(const Handle& h1, const Handle& h2)
{
    return Handle{ h1.Index - h2.Index };
}

Handle operator-(uint32_t h1, const Handle& h2)
{
    return Handle{ h1 - h2.Index };
}

Handle operator-(const Handle& h1, uint32_t h2)
{
    return Handle{ h1.Index - h2 };
}

Arena::Arena()
    : BlockSz(0)
    , Count(0)
    , FreeList(nullptr)
    , Memory(nullptr)
{

}

void Arena::Init(size_t blocksz, size_t count)
{
    size_t pad = blocksz % 8;
    pad = pad ? 8 - pad : 0;
    BlockSz = blocksz + pad;
    Count = count;

    Memory = (uint8_t*)malloc(BlockSz * Count);
    memset(Memory, 0, BlockSz * Count);

    size_t* ptr = (size_t*)Memory;
    FreeList = ptr;

    size_t* end = (size_t*)(Memory + BlockSz * Count);
    while (ptr != end)
    {
        size_t* next = (size_t*)((uint8_t*)ptr + BlockSz);
        *ptr = (size_t)next;
        ptr = next;
    }
}

void Arena::Shutdown()
{
    free(Memory);

    BlockSz = 0;
    Count = 0;
    FreeList = nullptr;
    Memory = nullptr;
}

void Arena::Resize(size_t count)
{
    size_t diff = Count - count;

    Count = count;
    Memory = (uint8_t*)realloc(Memory, BlockSz * Count);

    size_t* ptr = FreeList;
    while (*ptr)
        ptr = (size_t*)*ptr;

    for (size_t i = 0; i < diff; i++)
    {
        size_t* next = (size_t*)((uint8_t*)ptr + BlockSz);
        *ptr = (size_t)next;
        ptr = next;
    }
}

void* Arena::Alloc()
{
    if (!FreeList)
        return nullptr;

    void* mem = FreeList;
    FreeList = (size_t*)*FreeList;

    return mem;
}

void Arena::Alloc(Handle& handle)
{
    if (!FreeList)
        handle = UINT32_MAX;

    uint8_t* mem = (uint8_t*)FreeList;
    FreeList = (size_t*)*FreeList;

    handle = mem - Memory;
}

void Arena::Free(void* mem)
{
    size_t* ptr = (size_t*)mem;
    *ptr = (size_t)FreeList;
    FreeList = ptr;
}

void Arena::Free(Handle handle)
{
    size_t* ptr = (size_t*)&Memory[handle.Index];
    *ptr = (size_t)Freelist;
    Freelist = ptr;
}

uint8_t* Arena::operator[](Handle handle)
{
    return &Memory[handle.Index];
}
