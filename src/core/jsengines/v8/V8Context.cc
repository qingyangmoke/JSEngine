#include "V8Context.h"

using namespace CPlusDemo;
using namespace v8;

V8EngineContext::V8EngineContext(int contextId) : EngineContext(contextId)
{
  std::cout << "V8EngineContext init" << std::endl;
}

bool V8EngineContext::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  return false;
}

V8EngineContext::~V8EngineContext()
{
  std::cout << "JSCoreEngineContext destroyed" << std::endl;
}