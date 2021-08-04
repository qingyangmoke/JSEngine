#pragma once
#include <iostream>
#include <string>

#include "v8.h"

namespace JSEngineNS
{
  class V8EngineAllocator : public v8::ArrayBuffer::Allocator
  {
  public:
    V8EngineAllocator();

    ~V8EngineAllocator() override;

    void *Allocate(size_t length) override;

    void *AllocateUninitialized(size_t length) override;

    void Free(void *data, size_t length) override;
  };
}
