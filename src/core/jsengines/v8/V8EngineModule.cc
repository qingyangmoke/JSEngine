
#include "include/jsengine_bridge.h"
#include <iostream>
#include <string>
#include "V8EngineModule.h"
#include "V8Runtime.h"

using namespace JSEngineNS;

void invokeModuleCallback(const v8::FunctionCallbackInfo<v8::Value> &info)
{  
  auto isolate = info.GetIsolate();
  auto context = isolate->GetCurrentContext();
  auto argLen = info.Length();
  int contextId = V8Runtime::instance()->getContextId(context);
  EngineNativeMethods::instance()->log(contextId, "info", "V8JSEngineContext.invokeModule");
  try
  {
    if (argLen)
    {
      v8::Local<v8::String> moduleString;
      info[0]->ToDetailString(isolate->GetCurrentContext()).ToLocal(&moduleString);
      std::string moduleName = V8Runtime::instance()->ConvertToString(moduleString);

      v8::Local<v8::String> methodString;
      info[1]->ToDetailString(isolate->GetCurrentContext()).ToLocal(&methodString);
      std::string methodName = V8Runtime::instance()->ConvertToString(methodString);

      std::string args = "";
      if (argLen > 2 && info[2]->IsObject())
      {
        v8::Local<v8::String> argsString;
        v8::JSON::Stringify(isolate->GetCurrentContext(), info[2]).ToLocal(&argsString);
        args = V8Runtime::instance()->ConvertToString(argsString);
      }

      EngineInvokeModuleCallback callback = nullptr;
      if (argLen > 3 && info[3]->IsFunction())
      {
        auto this_val = context;
        // 回调
        auto func = info[3].As<v8::Function>();
        callback = [isolate, context, func, this_val, contextId](int errorCode, const char *result)
        {
          EngineNativeMethods::instance()->log(contextId, "info", "V8JSEngineContext.callback");
          v8::Local<v8::Number> errorCodeValue = v8::Number::New(isolate, errorCode);
          v8::Local<v8::String> resultString = v8::String::Empty(isolate);
          if(result != NULL) {
            std::string str(result);
            resultString = V8Runtime::instance()->ConvertToV8String(context->GetIsolate(), str);
          }
          v8::Local<v8::Value> args1[] = {errorCodeValue, resultString};
          func->Call(context->Global(), 2, args1);
        };
      }
      
      const char *result = EngineNativeMethods::instance()->invokeModule(contextId, moduleName, methodName, args, callback);
      info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, result));
    }
  }
  catch (...)
  {
  }
  info.GetReturnValue().Set(v8::String::Empty(isolate));
}

void V8EngineModule::initModule(v8::Local<v8::Context> context)
{
  v8::Local<v8::Object> engineModule = v8::Object::New(V8Runtime::instance()->getIsolate());
  V8Runtime::instance()->bindFunctionProperty(context, engineModule, "invokeModule", invokeModuleCallback);

  auto global = context->Global();
  const auto readOnlyFlags = static_cast<v8::PropertyAttribute>(v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly);
  global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), "__module__"), engineModule, readOnlyFlags);
}
