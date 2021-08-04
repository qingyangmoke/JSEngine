#include <iostream>
#include <string>

#include "include/jsengine_bridge.h"

#include "timer/TimerManager.h"

using namespace CPlusDemo;

#if BRIDGE_JS_ENGINE == 1
#include "jsengines/jsc/JSCoreContext.h"
EngineContext *createContext(int contextId)
{
  return new jsc::JSCoreEngineContext(contextId);
}
#elif BRIDGE_JS_ENGINE == 2
#include "jsengines/v8/V8Context.h"
EngineContext *createContext(int contextId)
{
  return new V8EngineContext(contextId);
}
#elif BRIDGE_JS_ENGINE == 3
#include "jsengines/quickjs/QuickJSContext.h"
EngineContext *createContext(int contextId)
{
  return new quickjs::QuickJSEngineContext(contextId);
}
#else
EngineContext *createContext(int contextId)
{
  return NULL;
}
#endif

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

void EngineScope::invokeJSModule(const char *moduleName, const char *methodName, const char *args)
{
  if (_context == NULL)
  {
    return;
  }
  return _context->invokeJSModule(moduleName, methodName, args);
}

EngineScope::~EngineScope()
{
  std::cout << "EngineScope destoryed" << _contextId << std::endl;
  // TimerManager::instance()->clearAllTimer(this->getContextId());
  delete _context;
  _context = NULL;
}