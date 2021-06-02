#pragma once
#include "JavaScriptCore.h"

namespace CPlusDemo::jsc
{
  class JSCoreConsole
  {
  public:
    static void initConsole(JSGlobalContextRef jscContext, JSObjectRef global);
  };
}