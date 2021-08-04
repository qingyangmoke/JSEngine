#pragma once
#include "include/jsengine_bridge.h"
namespace JSEngineNS
{
  class DomEnginePlugin : public EnginePlugin
  {
  public:
    DomEnginePlugin();
    void onScopeCreate(EngineScope *scope) override;
    void onScopeDestroy(EngineScope *scope) override;
    ~DomEnginePlugin() override;
  };
}