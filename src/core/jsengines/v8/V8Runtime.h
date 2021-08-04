#pragma once
#include <iostream>
#include <string>
#include "v8.h"

#include "include/jsengine_bridge.h"

namespace JSEngineNS
{
  class V8Runtime
  {
  public:
    OBJECT_INSTANCE(V8Runtime);
    void Initialize();
    v8::Isolate *getIsolate();
    v8::Local<v8::String> ConvertToV8String(v8::Isolate *isolate, const char *data, int length);
    v8::Local<v8::String> ConvertToV8String(v8::Isolate *isolate, const std::string &s);
    std::string ConvertToString(const v8::Local<v8::String> &s);
    void bindFunctionProperty(v8::Local<v8::Context> context,
                              v8::Local<v8::Object> consoleInstance,
                              const std::string &functionName,
                              v8::FunctionCallback callback);
    int getContextId(v8::Local<v8::Context> context);
  protected:
    static V8Runtime *singletonInstance;
    v8::Platform *platform;
    v8::Isolate *isolate;
    V8Runtime();
    ~V8Runtime();
  };
}