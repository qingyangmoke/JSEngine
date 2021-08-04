#include "V8Runtime.h"
#include "libplatform/libplatform.h"
#include "V8EngineAllocator.h"
using namespace JSEngineNS;
using namespace v8;

V8Runtime *V8Runtime::singletonInstance = NULL;

V8Runtime::V8Runtime()
{
  this->platform = NULL;
  this->isolate = NULL;
  EngineNativeMethods::instance()->log(0, "info", "V8Runtime init");
}

void V8Runtime::Initialize()
{
  if (this->platform == NULL)
  {
    v8::Platform *platform = v8::platform::NewDefaultPlatform().release();
    v8::V8::InitializePlatform(platform);
    v8::V8::Initialize();
  }
  if (this->isolate == NULL)
  {
    v8::Isolate::CreateParams create_params;    
    create_params.array_buffer_allocator = new V8EngineAllocator();
    this->isolate = v8::Isolate::New(create_params);
  }
}

v8::Isolate *V8Runtime::getIsolate()
{
  return this->isolate;
}

v8::Local<v8::String> V8Runtime::ConvertToV8String(v8::Isolate *isolate, const char *data, int length)
{
  return v8::String::NewFromTwoByte(isolate, (const uint16_t *)data, v8::NewStringType::kNormal, length).ToLocalChecked();
}

v8::Local<v8::String> V8Runtime::ConvertToV8String(v8::Isolate *isolate, const std::string &s)
{
  // try
  // {
  // // return ConvertToV8String(isolate, s.c_str(), s.length());
  v8::Local<v8::String> str = v8::String::NewFromUtf8(isolate, s.c_str(), v8::NewStringType::kNormal, s.length()).ToLocalChecked();
  return str;
  // }
  // catch (...)
  // {
  // }
  // return v8::String::NewFromUtf8(isolate, "hello");
}

std::string V8Runtime::ConvertToString(const v8::Local<v8::String> &s)
{
  if (s.IsEmpty())
  {
    return std::string();
  }
  else
  {
    v8::String::Utf8Value str(getIsolate(), s);
    return std::string(*str);
  }
}

void V8Runtime::bindFunctionProperty(v8::Local<v8::Context> context,
                                     v8::Local<v8::Object> consoleInstance,
                                     const std::string &functionName,
                                     v8::FunctionCallback callback)
{
  v8::Local<v8::String> funcName = ConvertToV8String(context->GetIsolate(), functionName);

  v8::Local<v8::Function> func;
  if (!v8::Function::New(context, callback, consoleInstance, 0, v8::ConstructorBehavior::kThrow).ToLocal(&func))
  {
    return;
  }

  func->SetName(funcName);

  consoleInstance->CreateDataProperty(context, funcName, func);
}

int V8Runtime::getContextId(v8::Local<v8::Context> context)
{
  auto global = context->Global();
  int contextId = global->Get(context, ConvertToV8String(isolate, "contextId")).ToLocalChecked()->ToNumber(isolate)->IntegerValue(context).ToChecked();
  return contextId;
}

V8Runtime::~V8Runtime()
{
  EngineNativeMethods::instance()->log(0, "info", "~V8Runtime");
}
