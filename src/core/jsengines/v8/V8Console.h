#pragma once
#include "v8.h"
#include "include/jsengine_bridge.h"
namespace JSEngineNS
{
  class V8Console
  {
  public:
    static void initConsole(v8::Local<v8::Context> context);
  };
}