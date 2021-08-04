#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "include/jsengine_bridge.h"

#include <quickjs/quickjs.h>

namespace JSEngineNS::quickjs
{
  class QuickJSEngineContext : public EngineContext
  {
  public:
    QuickJSEngineContext(int contextId);
    ~QuickJSEngineContext() override;
    bool evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine) override;
    void invokeJSModule(const char *moduleName, const char *methodName, const char *args) override;
    
  protected:
    static JSRuntime *_runtime;
  private:
    JSContext *_context;
  };
}