#pragma once
#ifdef __APPLE__
#include <JavaScriptCore/JavaScriptCore.h>
#else
#include <JavaScriptCore/JavaScript.h>
#endif

namespace CPlusDemo::jsc
{
  class JSConsole
  {
  public:
    static void initConsole(JSGlobalContextRef jscContext, JSObjectRef global);
  };
}