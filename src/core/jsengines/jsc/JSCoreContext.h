#pragma once
#include "JavaScriptCore.h"

#include <iostream>
#include <string>
#include <vector>

#include "include/my_bridge.h"

namespace CPlusDemo::jsc
{
  typedef std::function<void(int32_t contextId, const char *errmsg)> JSExceptionHandler;

  class JSCoreEngineContext : public EngineContext
  {
  public:
    static JSCoreEngineContext* getContext(JSContextRef context);
    JSCoreEngineContext(int contextId);
    ~JSCoreEngineContext() override;
    bool evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine) override;

  protected:
    JSObjectRef global();
    JSGlobalContextRef context();
    bool handleException(JSValueRef exc);

  private:
    JSGlobalContextRef _jscContext;
  };
}