#include "include/jsengine_bridge.h"
using namespace CPlusDemo;
EnginePlugin::EnginePlugin(const std::string &name)
{
  this->name = name;
}

void EnginePlugin::onScopeCreate(EngineScope *scope)
{
}

void EnginePlugin::onScopeDestroy(EngineScope *scope)
{
}


EnginePlugin::~EnginePlugin()
{
  std::cout << "~EnginePlugin" << std::endl;
}