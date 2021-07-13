#pragma once
#include "v8.h"
#include "include/jsengine_bridge.h"
namespace CPlusDemo
{
  class V8EngineModule
  {
  public:
    static void initModule(v8::Local<v8::Context> context);
  };
}