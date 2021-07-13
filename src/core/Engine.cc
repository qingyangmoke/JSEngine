#include "include/jsengine_bridge.h"
#include "plugins/dom/DomEnginePlugin.h"

using namespace CPlusDemo;

Engine *Engine::singletonInstance = NULL;

Engine::Engine() {
  EngineNativeMethods::instance()->log(0, "info", "Engine create");
  DomEnginePlugin *plugin = new DomEnginePlugin();
  registerPlugin(plugin);
  plugin = NULL;
}

EngineScope *Engine::createScope(int contextId)
{
  if (_scopeMap.count(contextId) == 1)
  {
    return _scopeMap[contextId];
  }
  EngineScope *scope = new EngineScope(contextId);
  _scopeMap[contextId] = scope;
  // notify plugins
  for (auto iter = _plugins.begin(); iter != _plugins.end(); ++iter) {
    iter->second->onScopeCreate(scope);
  }
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
    // notify plugins
    for (auto iter = _plugins.begin(); iter != _plugins.end(); ++iter) {
      iter->second->onScopeDestroy(scope);
    }
    delete scope;
  }
}

void Engine::registerPlugin(EnginePlugin *plugin)
{
  if (_plugins.count(plugin->name) == 0)
  {
    _plugins[plugin->name] = plugin;
  }
}

Engine::~Engine()
{
}