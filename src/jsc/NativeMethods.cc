#ifdef __APPLE__
#include <JavaScriptCore/JavaScriptCore.h>
#else
#include <JavaScriptCore/JavaScript.h>
#endif

#include "include/my_bridge.h"

using namespace CPlusDemo;

EngineNativeMethods *EngineNativeMethods::singletonInstance = NULL;

EngineNativeMethods::EngineNativeMethods()
{
  invokeModulePointer = NULL;
  logPointer = NULL;
}

const char* EngineNativeMethods::invokeModule(int contextId, const std::string moduleName, std::string methodName, std::string args, EngineInvokeModuleCallback callback)
{
  if (invokeModulePointer != NULL)
  {
    int callId = ++_callId;
    if (callback)
    {
      _callbackMap[callId] = callback;
    }
    return invokeModulePointer(contextId, callId, moduleName.c_str(), methodName.c_str(), args.c_str());
  }
  else
  {
    if (callback)
    {
      callback(404, "{\"msg\": \"invokeModulePointer not implemented\"}");
    }
    return NULL;
  }
}

void EngineNativeMethods::invokeModuleEvent(int contextId, int callId, int errorCode, const char *result)
{
  if (_callbackMap.count(callId) == 1)
  {
    EngineInvokeModuleCallback callback = _callbackMap[callId];
    callback(errorCode, result);
    _callbackMap.erase(callId);
  }
  // callback(0, "{\"moduleName\": \"" + moduleName + "\", \"methodName\": \"" + methodName + "\"}");
}

void EngineNativeMethods::log(int contextId, const std::string tagName, std::string message)
{
  if (logPointer != NULL)
  {
    logPointer(contextId, tagName.c_str(), message.c_str());
  }
}

EngineNativeMethods::~EngineNativeMethods()
{
  _callbackMap.clear();
}
