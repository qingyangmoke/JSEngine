#include "include/jsengine_bridge.h"

using namespace CPlusDemo;

EngineContext::EngineContext(int contextId)
{
  _contextId = contextId;
}

int EngineContext::getContextId()
{
  return _contextId;
}

bool EngineContext::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  std::cout << "evaluateJavaScript未实现" << std::endl;
  return false;
}

void EngineContext::invokeJSModule(const char *moduleName, const char *methodName, const char *args)
{
  std::cout << "evaluateJavaScript未实现" << std::endl;
}

EngineContext::~EngineContext()
{
   std::cout << "EngineContext destroyed" << std::endl;
}