#include "DomEnginePlugin.h"

#include "DomPolyfill.h"

using namespace CPlusDemo;

DomEnginePlugin::DomEnginePlugin() : EnginePlugin("dom") {}

void DomEnginePlugin::onScopeCreate(EngineScope *scope)
{
  injectDomPolyfill(scope);
  EngineNativeMethods::instance()->log(scope->getContextId(), "info", "injectDomPolyfill");
}

void DomEnginePlugin::onScopeDestroy(EngineScope *scope)
{
}

DomEnginePlugin::~DomEnginePlugin()
{
}