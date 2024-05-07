#include "CoreMemory.h"

#include "Logger.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct MemoryStats
{
    u64 totalAllocated;
    u64 taggedAllocations[MEMORY_TAG_MAX];
};

static const char* memoryTagStrings[MEMORY_TAG_MAX] = {
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

static struct MemoryStats memoryStats;

void InitializeMemoryStats()
{
    memset(&memoryStats, 0, sizeof(memoryStats));
}

void ShutdownMemoryStats()
{
    
}

void* CoreAllocate(u64 size, MemoryTag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        COREWARNING("CoreAllocate called using MEMORY_TAG_UNKNOWN");
    }
    
    memoryStats.totalAllocated += size;
    memoryStats.taggedAllocations[tag] += size;
    
    // TODO: Memory alignment
    void* block = malloc(size);
    CoreZeroMemory(block, size);
    return block;
}

void CoreFree(void* block, u64 size, MemoryTag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN)
    {
        COREWARNING("CoreFree called using MEMORY_TAG_UNKNOWN");
    }
    
    memoryStats.totalAllocated -= size;
    memoryStats.taggedAllocations[tag] -= size;
    
    // TODO: Memory alignment
    free(block);
}

void* CoreZeroMemory(void* block, u64 size)
{
    return memset(block, 0, size);
}

void* CoreCopyMemory(void* destination, const void* source, u64 size)
{
    return memcpy(destination, source, size);
}

void* CoreSetMemory(void* destination, i32 value, u64 size)
{
    return memset(destination, value, size);
}

char* GetMemoryUsage()
{
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;
    
    char buffer[8000] = "System memory use (tagged):\n";
    u64 offset = strlen(buffer);
    for (u32 i = 0; i < MEMORY_TAG_MAX; ++i)
    {
        char unit[4] = "XiB";
        float amount = 1.0f;
        if (memoryStats.taggedAllocations[i] >= gib)
        {
            unit[0] = 'G';
            amount = memoryStats.taggedAllocations[i] / (float)gib;
        }
        else if (memoryStats.taggedAllocations[i] >= mib)
        {
            unit[0] = 'M';
            amount = memoryStats.taggedAllocations[i] / (float)mib;
        }
        else if (memoryStats.taggedAllocations[i] >= kib)
        {
            unit[0] = 'K';
            amount = memoryStats.taggedAllocations[i] / (float)kib;
        }
        else
        {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)memoryStats.taggedAllocations[i];
        }
        
        i32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memoryTagStrings[i], amount, unit);
        offset += length;
    }
    
    char* outString = _strdup(buffer);
    return outString;
}