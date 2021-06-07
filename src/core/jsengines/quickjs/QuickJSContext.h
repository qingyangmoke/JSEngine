#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "include/jsengine_bridge.h"

#include <quickjs/quickjs.h>

namespace CPlusDemo::quickjs
{
  class QuickJSEngineContext : public EngineContext
  {
  public:
    QuickJSEngineContext(int contextId);
    ~QuickJSEngineContext() override;
    bool evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine) override;
  protected:
    static JSRuntime *_runtime;
  private:
    JSContext *_context;
  };
}