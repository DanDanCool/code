#include <stdlib.h>
#include <string.h>

#include "memarena.h"

MemoryArena::MemoryArena()
    : BlockSize(0)
    , Count(0)
    , FreeList(nullptr)
    , Mem(nullptr)
{

}

void MemoryArena::Init(size_t blocksz, size_t count)
{
    size_t pad = blocksz % 8;
    pad = pad ? 8 - pad : 0;
    BlockSize = blocksz + pad;
    Count = count;

    Mem = (uint8_t*)malloc(BlockSize * Count);
    memset(Mem, 0, BlockSize * Count);

    uint64_t* ptr = (uint64_t*)Mem;
    FreeList = ptr;

    uint64_t* end = (uint64_t*)(Mem + BlockSize * Count);
    while (ptr != end)
    {
        uint64_t* next = (uint64_t*)((uint8_t*)ptr + BlockSize);
        *ptr = (uint64_t)next;
        ptr = next;
    }
}

void MemoryArena::Shutdown()
{
    free(Mem);

    BlockSize = 0;
    Count = 0;
    FreeList = nullptr;
    Mem = nullptr;
}

void MemoryArena::Resize(size_t count)
{
    size_t diff = Count - count;

    Count = count;
    Mem = (uint8_t*)realloc(Mem, BlockSize * Count);

    uint64_t* ptr = FreeList;
    while (*ptr)
        ptr = (uint64_t*)*ptr;

    for (size_t i = 0; i < diff; i++)
    {
        uint64_t* next = (uint64_t*)((uint8_t*)ptr + BlockSize);
        *ptr = (uint64_t)next;
        ptr = next;
    }
}

void* MemoryArena::Allocate()
{
    if (!FreeList)
        return nullptr;

    void* mem = FreeList;
    FreeList = (uint64_t*)*FreeList;

    return mem;
}

void MemoryArena::Free(void* mem)
{
    uint64_t* ptr = (uint64_t*)mem;
    *ptr = (uint64_t)FreeList;
    FreeList = ptr;
}
