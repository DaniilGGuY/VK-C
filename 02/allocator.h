#ifndef ALLOCATOR_H__
#define ALLOCATOR_H__

#include <cstddef>

struct Allocator {
    char* data;
    size_t size;
    size_t offset;
};

// При вызове init_allocator аллоцируется динамическая память указанного размера
Allocator* init_allocator(size_t maxSize);

// При вызове alloc возвращает указатель на блок запрошенного размера или nullptr, если места недостаточно
char* alloc(Allocator *alloc, size_t size);

// После вызова reset аллокатор позволяет использовать свою память снова. То есть память, ранее выделенная при помощи 
// alloc становится "невалидной", её пользователь может переиспользовать, вызвав опять alloc. offset при методе reset снова указывает на начало
void reset(Allocator *alloc);

// delete вызывается в clear 
void clear(Allocator *alloc);

#endif