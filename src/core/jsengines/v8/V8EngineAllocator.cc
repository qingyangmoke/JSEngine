#include "V8EngineAllocator.h"
#include <cstdlib>

using namespace CPlusDemo;

V8EngineAllocator::V8EngineAllocator() : v8::ArrayBuffer::Allocator()
{
}

V8EngineAllocator::~V8EngineAllocator()
{
}

void *V8EngineAllocator::Allocate(size_t length)
{
  void *data = calloc(length, 1);
  return data;
}

void *V8EngineAllocator::AllocateUninitialized(size_t length)
{
  void *data = malloc(length);
  return data;
}

void V8EngineAllocator::Free(void *data, size_t length)
{
  free(data);
}