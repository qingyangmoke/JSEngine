#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "include/jsengine_bridge.h"

#include "v8.h"
namespace JSEngineNS
{
  class V8EngineContext : public EngineContext
  {
  public:
    V8EngineContext(int contextId);
    ~V8EngineContext() override;
    v8::Local<v8::Context> getLocalContext();
    bool evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine) override;
    void invokeJSModule(const char *moduleName, const char *methodName, const char *args) override;
    void handleException(const v8::TryCatch * try_catch);
  protected:
    v8::Persistent<v8::Context> context;
    v8::Context *m_context;
  };
}