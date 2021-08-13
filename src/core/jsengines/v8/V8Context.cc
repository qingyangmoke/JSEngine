#include "v8.h"
#include "V8Context.h"
#include "V8Runtime.h"
#include "V8Console.h"
#include "V8EngineModule.h"
#include "libplatform/libplatform.h"
using namespace JSEngineNS;

V8EngineContext::V8EngineContext(int contextId) : EngineContext(contextId)
{
  V8Runtime::instance()->Initialize();
  v8::Isolate *isolate = V8Runtime::instance()->getIsolate();
  if (isolate == NULL)
  {
    EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext NULL");
  }

  v8::Isolate::Scope isolate_scope(isolate);
  v8::HandleScope handle_scope(isolate);
  auto globalFunctionTemplate = v8::FunctionTemplate::New(isolate);
  globalFunctionTemplate->SetClassName(V8Runtime::instance()->ConvertToV8String(isolate, "JSEngineGlobalObject"));
  auto globalTemplate = v8::ObjectTemplate::New(isolate, globalFunctionTemplate);
  v8::Local<v8::Context> context = v8::Context::New(isolate, nullptr, globalTemplate);
  this->m_context = *context;
  this->context.Reset(isolate, context);
  v8::Context::Scope context_scope(context);
  auto global = context->Global();
  const auto readOnlyFlags = static_cast<v8::PropertyAttribute>(v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly);
  auto success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "globalThis"), global, readOnlyFlags);
  success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "global"), global, readOnlyFlags);
  success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "window"), global, readOnlyFlags);

  v8::Local<v8::Number> contextIdValue = v8::Number::New(isolate, contextId);
  success = global->DefineOwnProperty(context, V8Runtime::instance()->ConvertToV8String(isolate, "contextId"), contextIdValue, readOnlyFlags);

  V8Console::initConsole(context);
  V8EngineModule::initModule(context);

  isolate = NULL;
}

bool V8EngineContext::evaluateJavaScript(const char *sourceCode, const char *sourceURL, int startLine)
{
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext.evaluateJavaScript");
  v8::Isolate::Scope isolate_scope(V8Runtime::instance()->getIsolate());
  v8::HandleScope handle_scope(V8Runtime::instance()->getIsolate());
  v8::TryCatch tc(V8Runtime::instance()->getIsolate());
  v8::Local<v8::Context> context = getLocalContext();
  v8::Context::Scope context_scope(context);
  std::string strSourceCode(sourceCode);
  v8::Local<v8::String> source = V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), strSourceCode);
  v8::Local<v8::Script> script;
  std::string str(sourceURL);
  v8::ScriptOrigin origin(V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), str));
  v8::Script::Compile(context, source, &origin).ToLocal(&script);
  if (tc.HasCaught())
  {
    handleException(&tc);
    return false;
  }

  if (!script.IsEmpty())
  {
    script->Run(context);

    if (tc.HasCaught())
    {
      handleException(&tc);
    }
  }
  else
  {
    EngineNativeMethods::instance()->log(_contextId, "warn", ">>runScript maybeScript is empty");
  }
  return true;
}

v8::Local<v8::Context> V8EngineContext::getLocalContext()
{
  return this->context.Get(V8Runtime::instance()->getIsolate());
}

void V8EngineContext::invokeJSModule(const char *moduleName, const char *methodName, const char *args)
{
  EngineNativeMethods::instance()->log(_contextId, "warn", "v8 invokeJSModule");
  if (moduleName == NULL || methodName == NULL)
  {
    return;
  }
  v8::Isolate::Scope isolate_scope(V8Runtime::instance()->getIsolate());
  v8::HandleScope handle_scope(V8Runtime::instance()->getIsolate());
  v8::TryCatch tc(V8Runtime::instance()->getIsolate());
  v8::Local<v8::Context> context = getLocalContext();
  v8::Context::Scope context_scope(context);

  std::string _moduleName(moduleName);
  std::string _methodName(methodName);
  v8::Handle<v8::Object> global = context->Global();
  v8::Handle<v8::Value> moduleValueRef = global->Get(V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), _moduleName));
  if (moduleValueRef->IsObject())
  {
    v8::Handle<v8::Object> moduleRef = v8::Handle<v8::Object>::Cast(moduleValueRef);
    v8::Handle<v8::Value> methodValueRef = moduleRef->Get(V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), _methodName));
    if (methodValueRef->IsFunction())
    {
      std::string _args(args == NULL ? "" : args);
      v8::Handle<v8::Function> methodRef = v8::Handle<v8::Function>::Cast(methodValueRef);
      v8::Handle<v8::Value> args[1];
      args[0] = V8Runtime::instance()->ConvertToV8String(V8Runtime::instance()->getIsolate(), _args);
      methodRef->Call(global, 1, args);
    }
  }
}

void V8EngineContext::handleException(const v8::TryCatch * try_catch) {
    // const char * sourceURL = *v8::String::Utf8Value(V8Runtime::instance()->getIsolate(), try_catch.Message()->GetScriptResourceName();
    // int lineNumber = try_catch.Message()->GetLineNumber(context).FromJust();
    // int columNumber = try_catch.Message()->GetStartColumn(context).FromJust();
    char * message = *v8::String::Utf8Value(V8Runtime::instance()->getIsolate(), try_catch->Exception());
    EngineNativeMethods::instance()->log(_contextId, "error", message);
    message = NULL;
}

V8EngineContext::~V8EngineContext()
{
  this->context.Reset();
  EngineNativeMethods::instance()->log(_contextId, "info", "V8EngineContext destroyed");
}