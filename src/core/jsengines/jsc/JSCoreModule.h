#pragma once
#include "JavaScriptCore.h"

namespace CPlusDemo::jsc
{
  class JSCoreModule
  {
  public:
    static void initModule(JSGlobalContextRef jscContext, JSObjectRef global);
  };
}