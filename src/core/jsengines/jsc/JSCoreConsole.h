#pragma once
#include "JavaScriptCore.h"

namespace JSEngineNS::jsc
{
  class JSCoreConsole
  {
  public:
    static void initConsole(JSGlobalContextRef jscContext, JSObjectRef global);
  };
}