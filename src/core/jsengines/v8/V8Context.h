#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "include/jsengine_bridge.h"

namespace CPlusDemo::v8
{
  class V8EngineContext : public EngineContext
  {
  public:
    V8EngineContext(int contextId);
    ~V8EngineContext() override;
    bool evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine) override;
  };
}