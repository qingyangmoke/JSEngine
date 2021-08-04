#pragma once
#include "include/jsengine_bridge.h"
#include <quickjs/quickjs.h>

namespace JSEngineNS::quickjs
{
  class QuickJSModule
  {
  public:
    static void initModule(JSContext *jscContext);
  };
}