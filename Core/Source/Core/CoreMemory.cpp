#include "CoreMemory.h"

#include "Logger.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct MemoryStats
{
    u64 TotalAllocated;
    u64 TaggedAllocations[MEMORY_TAG_MAX];
};

static const char* MemoryTagStrings[MEMORY_TAG_MAX] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "
};

static struct MemoryStats _MemoryStats;

void InitializeMemoryStats()
{
    memset(&_MemoryStats, 0, sizeof(_MemoryStats));
}

void ShutdownMemoryStats()
{
    
}

void* CoreAllocate(u64 Size, MemoryTag Tag)
{
    if (Tag == MEMORY_TAG_UNKNOWN)
    {
        COREWARNING("CoreAllocate called using MEMORY_TAG_UNKNOWN");
    }
    
    _MemoryStats.TotalAllocated += Size;
    _MemoryStats.TaggedAllocations[Tag] += Size;
    
    // TODO: Memory alignment
    void* block = malloc(Size);
    CoreZeroMemory(block, Size);
    return block;
}

void CoreFree(void* Block, u64 Size, MemoryTag Tag)
{
    if (Tag == MEMORY_TAG_UNKNOWN)
    {
        COREWARNING("CoreFree called using MEMORY_TAG_UNKNOWN");
    }
    
    _MemoryStats.TotalAllocated -= Size;
    _MemoryStats.TaggedAllocations[Tag] -= Size;
    
    // TODO: Memory alignment
    free(Block);
}

void* CoreZeroMemory(void* Block, u64 Size)
{
    return memset(Block, 0, Size);
}

void* CoreCopyMemory(void* Destination, const void* Source, u64 Size)
{
    return memcpy(Destination, Source, Size);
}

void* CoreSetMemory(void* Destination, i32 Value, u64 Size)
{
    return memset(Destination, Value, Size);
}

char* GetMemoryUsage()
{
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;
    
    char Buffer[8000] = "System memory use (tagged):\n";
    u64 Offset = strlen(Buffer);
    for (u32 i = 0; i < MEMORY_TAG_MAX; ++i)
    {
        char Unit[4] = "XiB";
        float Amount = 1.0f;
        if (_MemoryStats.TaggedAllocations[i] >= gib)
        {
            Unit[0] = 'G';
            Amount = _MemoryStats.TaggedAllocations[i] / (float)gib;
        }
        else if (_MemoryStats.TaggedAllocations[i] >= mib)
        {
            Unit[0] = 'M';
            Amount = _MemoryStats.TaggedAllocations[i] / (float)mib;
        }
        else if (_MemoryStats.TaggedAllocations[i] >= kib)
        {
            Unit[0] = 'K';
            Amount = _MemoryStats.TaggedAllocations[i] / (float)kib;
        }
        else
        {
            Unit[0] = 'B';
            Unit[1] = 0;
            Amount = (float)_MemoryStats.TaggedAllocations[i];
        }
        
        i32 length = snprintf(Buffer + Offset, 8000, "  %s: %.2f%s\n", MemoryTagStrings[i], Amount, Unit);
        Offset += length;
    }
    
    char* OutString = _strdup(Buffer);
    return OutString;
}