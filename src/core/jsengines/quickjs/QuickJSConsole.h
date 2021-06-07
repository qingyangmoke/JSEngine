#pragma once
#include "include/jsengine_bridge.h"
#include <quickjs/quickjs.h>

namespace CPlusDemo::quickjs
{
  class QuickJSConsole
  {
  public:
    static void initConsole(JSContext *jscContext);
  };
}