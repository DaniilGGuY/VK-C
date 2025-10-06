#include "allocator.h"

Allocator* init_allocator(size_t maxSize) {
    if (maxSize == 0) return nullptr;

    Allocator *alloc = new Allocator;
    if (!alloc) return nullptr;

    alloc->data = new char[maxSize];
    if (!alloc->data) {
        delete alloc;
        return nullptr;
    }

    alloc->size = maxSize;
    alloc->offset = 0;

    return alloc;
}

char* alloc(Allocator *alloc, size_t size) {
    if (!alloc || !alloc->data || size == 0) return nullptr;

    if (alloc->offset + size > alloc->size) return nullptr;

    char *p = alloc->data + alloc->offset;
    alloc->offset += size;
    return p;
}

void reset(Allocator *alloc) {
    if (alloc) alloc->offset = 0;
}

void clear(Allocator *alloc) {
    if (alloc) {
        delete[] alloc->data;
        delete alloc;
    }
}
