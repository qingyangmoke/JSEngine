#ifdef __APPLE__
#include <JavaScriptCore/JavaScriptCore.h>
#else
#include <JavaScriptCore/JavaScript.h>
#endif

#include "include/my_bridge.h"

using namespace CPlusDemo;

Engine *Engine::singletonInstance = NULL;

Engine::Engine() {}
EngineScope *Engine::createScope(int contextId)
{
  if (_scopeMap.count(contextId) == 1)
  {
    return _scopeMap[contextId];
  }
  EngineScope *scope = new EngineScope(contextId);
  _scopeMap[contextId] = scope;
  return scope;
}

EngineScope *Engine::getScope(int contextId)
{
  if (_scopeMap.count(contextId) == 1)
  {
    return _scopeMap[contextId];
  }
  return NULL;
}

void Engine::removeScope(int contextId)
{
  if (_scopeMap.count(contextId) == 1)
  {
    EngineScope *scope = _scopeMap[contextId];
    _scopeMap.erase(contextId);
    delete scope;
  }
}

Engine::~Engine()
{
}