#pragma once
#ifdef __APPLE__
#include <JavaScriptCore/JavaScriptCore.h>
#else
#include <JavaScriptCore/JavaScript.h>
#endif

namespace CPlusDemo::jsc
{
  class AlitaGlobalObject
  {
  public:
    static void initAlitaGlobalObject(JSGlobalContextRef jscContext, JSObjectRef global);
  };
}