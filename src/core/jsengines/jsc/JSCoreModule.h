#pragma once
#include "JavaScriptCore.h"

namespace JSEngineNS::jsc
{
  class JSCoreModule
  {
  public:
    static void initModule(JSGlobalContextRef jscContext, JSObjectRef global);
  };
}