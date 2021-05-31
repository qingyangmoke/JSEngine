#include <iostream>
#include <string>

#include "include/my_bridge.h"

#include "jsengines/jsc/JSCoreContext.h"

using namespace CPlusDemo;

EngineContext *createContext(int contextId)
{
  return new jsc::JSCoreEngineContext(contextId);
}

EngineScope::EngineScope(int contextId)
{
  _contextId = contextId;
  this->_context = createContext(contextId);
}

int EngineScope::getContextId()
{
  return _contextId;
}

bool EngineScope::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  if (_context == NULL)
  {
    return false;
  }
  return _context->evaluateJavaScript(sourceCode, sourceURL, startLine);
}

EngineScope::~EngineScope()
{
  std::cout << "EngineScope destoryed" << _contextId << std::endl;
  delete _context;
  _context = NULL;
}