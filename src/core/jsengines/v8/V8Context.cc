#include <v8.h>
#include "V8Context.h"

using namespace CPlusDemo;
using namespace v8;

V8EngineContext::V8EngineContext(int contextId) : EngineContext(contextId)
{
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext init");
}

bool V8EngineContext::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  return false;
}

V8EngineContext::~V8EngineContext()
{
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext destroyed");
}