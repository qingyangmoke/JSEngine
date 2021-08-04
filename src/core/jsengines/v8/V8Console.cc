#include "v8.h"
#include <iostream>
#include <string>
#include "V8Console.h"
#include "V8RunTime.h"
#include "include/jsengine_bridge.h"
using namespace JSEngineNS;

void _logCallback(std::string type, const v8::FunctionCallbackInfo<v8::Value> &info)
{
  int contextId = -1;
  v8::Isolate *isolate = info.GetIsolate();
  try
  {
    // auto isolate = V8Runtime::instance()->getIsolate();
    int argLen = info.Length();
    contextId = V8Runtime::instance()->getContextId(isolate->GetCurrentContext());
    if (argLen >= 2)
    {
      std::string message = "";
      for (int i = 0; i < argLen; i++)
      {
        v8::Local<v8::String> objectString;
        info[i]->ToDetailString(isolate->GetCurrentContext()).ToLocal(&objectString);
        message.append(V8Runtime::instance()->ConvertToString(objectString));
        if (i < argLen)
        {
          message.append(" ");
        }
      }
      EngineNativeMethods::instance()->log(contextId, type, message);
    }
  }
  catch (...)
  {
    EngineNativeMethods::instance()->log(contextId, type, "_logCallback error");
  }
  isolate = NULL;
}

void infoCallback(const v8::FunctionCallbackInfo<v8::Value> &info)
{
  _logCallback("log", info);
}

void errorCallback(const v8::FunctionCallbackInfo<v8::Value> &info)
{
  _logCallback("error", info);
}

void warnCallback(const v8::FunctionCallbackInfo<v8::Value> &info)
{
  _logCallback("warn", info);
}

void debugCallback(const v8::FunctionCallbackInfo<v8::Value> &info)
{
  _logCallback("debug", info);
}

void V8Console::initConsole(v8::Local<v8::Context> context)
{
  v8::Isolate *isolate = V8Runtime::instance()->getIsolate();
  v8::Context::Scope contextScope(context);

  v8::Local<v8::Object> console = v8::Object::New(isolate);
  bool success = console->SetPrototype(context, v8::Object::New(isolate)).FromMaybe(false);
  V8Runtime::instance()->bindFunctionProperty(context, console, "assert", infoCallback);
  V8Runtime::instance()->bindFunctionProperty(context, console, "debug", debugCallback);
  V8Runtime::instance()->bindFunctionProperty(context, console, "error", errorCallback);
  V8Runtime::instance()->bindFunctionProperty(context, console, "info", infoCallback);
  V8Runtime::instance()->bindFunctionProperty(context, console, "log", infoCallback);
  V8Runtime::instance()->bindFunctionProperty(context, console, "warn", warnCallback);

  auto global = context->Global();
  const auto readOnlyFlags = static_cast<v8::PropertyAttribute>(v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly);
  global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "console"), console, readOnlyFlags);

  isolate = NULL;
}
