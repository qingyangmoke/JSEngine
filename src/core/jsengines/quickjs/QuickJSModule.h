#pragma once
#include "include/my_bridge.h"
#include <quickjs/quickjs.h>

namespace CPlusDemo::quickjs
{
  class QuickJSModule
  {
  public:
    static void initModule(JSContext *jscContext);
  };
}